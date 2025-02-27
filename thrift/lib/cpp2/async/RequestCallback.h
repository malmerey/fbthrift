/*
 * Copyright 2019-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <chrono>
#include <map>
#include <string>

#include <folly/io/IOBuf.h>

#include <thrift/lib/cpp/ContextStack.h>
#include <thrift/lib/cpp/concurrency/Thread.h>
#include <thrift/lib/cpp/transport/THeader.h>
#include <thrift/lib/cpp2/async/SemiStream.h>
#include <thrift/lib/cpp2/async/Stream.h>

namespace apache {
namespace thrift {
class ClientReceiveState {
 public:
  ClientReceiveState() : protocolId_(-1), isStreamEnd_(true) {}

  ClientReceiveState(
      uint16_t _protocolId,
      std::unique_ptr<folly::IOBuf> _buf,
      std::unique_ptr<apache::thrift::transport::THeader> _header,
      std::shared_ptr<apache::thrift::ContextStack> _ctx,
      bool _isStreamEnd = true)
      : protocolId_(_protocolId),
        ctx_(std::move(_ctx)),
        buf_(std::move(_buf)),
        header_(std::move(_header)),
        isStreamEnd_(_isStreamEnd) {}
  ClientReceiveState(
      uint16_t _protocolId,
      ResponseAndSemiStream<
          std::unique_ptr<folly::IOBuf>,
          std::unique_ptr<folly::IOBuf>> bufAndStream,
      std::unique_ptr<apache::thrift::transport::THeader> _header,
      std::shared_ptr<apache::thrift::ContextStack> _ctx,
      bool _isStreamEnd = true)
      : protocolId_(_protocolId),
        ctx_(std::move(_ctx)),
        buf_(std::move(bufAndStream.response)),
        header_(std::move(_header)),
        isStreamEnd_(_isStreamEnd),
        stream_(std::move(bufAndStream.stream)) {}
  ClientReceiveState(
      folly::exception_wrapper _excw,
      std::shared_ptr<apache::thrift::ContextStack> _ctx)
      : protocolId_(-1),
        ctx_(std::move(_ctx)),
        header_(std::make_unique<apache::thrift::transport::THeader>()),
        excw_(std::move(_excw)),
        isStreamEnd_(true) {}

  bool isException() const {
    return excw_ ? true : false;
  }

  folly::exception_wrapper const& exception() const {
    return excw_;
  }

  folly::exception_wrapper& exception() {
    return excw_;
  }

  uint16_t protocolId() const {
    return protocolId_;
  }

  folly::IOBuf* buf() const {
    return buf_.get();
  }

  std::unique_ptr<folly::IOBuf> extractBuf() {
    return std::move(buf_);
  }

  SemiStream<std::unique_ptr<folly::IOBuf>> extractStream() {
    return std::move(stream_);
  }

  apache::thrift::transport::THeader* header() const {
    return header_.get();
  }

  std::unique_ptr<apache::thrift::transport::THeader> extractHeader() {
    return std::move(header_);
  }

  void resetHeader(std::unique_ptr<apache::thrift::transport::THeader> h) {
    header_ = std::move(h);
  }

  apache::thrift::ContextStack* ctx() const {
    return ctx_.get();
  }

  void resetProtocolId(uint16_t protocolId) {
    protocolId_ = protocolId;
  }

  void resetCtx(std::shared_ptr<apache::thrift::ContextStack> _ctx) {
    ctx_ = std::move(_ctx);
  }

  bool isStreamEnd() const {
    return isStreamEnd_;
  }

 private:
  uint16_t protocolId_;
  std::shared_ptr<apache::thrift::ContextStack> ctx_;
  std::unique_ptr<folly::IOBuf> buf_;
  std::unique_ptr<apache::thrift::transport::THeader> header_;
  folly::exception_wrapper excw_;
  bool isStreamEnd_;
  SemiStream<std::unique_ptr<folly::IOBuf>> stream_;
};

class RequestClientCallback {
 public:
  struct RequestClientCallbackDeleter {
    void operator()(RequestClientCallback* callback) const {
      callback->onResponseError(folly::exception_wrapper(
          std::logic_error("Request callback detached")));
    }
  };
  using Ptr =
      std::unique_ptr<RequestClientCallback, RequestClientCallbackDeleter>;

  virtual ~RequestClientCallback() {}
  virtual void onRequestSent() noexcept = 0;
  virtual void onResponse(ClientReceiveState&&) noexcept = 0;
  virtual void onResponseError(folly::exception_wrapper) noexcept = 0;

  // If true, the transport can block current thread/fiber until the request is
  // complete.
  virtual bool isSync() const {
    return false;
  }

  // If true, the transport can safely run this callback on its internal thread.
  // Should only be used for Thrift internal callbacks.
  virtual bool isInlineSafe() const {
    return false;
  }
};

class RequestCallback : public RequestClientCallback {
 public:
  virtual void requestSent() = 0;
  virtual void replyReceived(ClientReceiveState&&) = 0;
  virtual void requestError(ClientReceiveState&&) = 0;

  void onRequestSent() noexcept override {
    CHECK(thriftContext_);
    {
      auto work = [&]() noexcept {
        try {
          requestSent();
        } catch (...) {
          LOG(DFATAL)
              << "Exception thrown while executing requestSent() callback. "
              << "Exception: " << folly::exceptionStr(std::current_exception());
        }
      };
      if (thriftContext_->oneWay) {
        folly::RequestContextScopeGuard rctx(std::move(context_));
        work();
      } else {
        folly::RequestContextScopeGuard rctx(context_);
        work();
      }
    }
    if (unmanaged_ && thriftContext_->oneWay) {
      delete this;
    }
  }

  void onResponse(ClientReceiveState&& state) noexcept override {
    CHECK(thriftContext_);
    state.resetProtocolId(thriftContext_->protocolId);
    bool lastResponse = state.isStreamEnd();
    state.resetCtx(
        lastResponse ? std::move(thriftContext_->ctx) : thriftContext_->ctx);
    {
      auto work = [&]() noexcept {
        try {
          replyReceived(std::move(state));
        } catch (...) {
          LOG(DFATAL)
              << "Exception thrown while executing replyReceived() callback. "
              << "Exception: " << folly::exceptionStr(std::current_exception());
        }
      };
      if (lastResponse) {
        folly::RequestContextScopeGuard rctx(std::move(context_));
        work();
      } else {
        folly::RequestContextScopeGuard rctx(context_);
        work();
      }
    }
    if (unmanaged_ && lastResponse) {
      delete this;
    }
  }

  void onResponseError(folly::exception_wrapper ex) noexcept override {
    CHECK(thriftContext_);
    {
      folly::RequestContextScopeGuard rctx(std::move(context_));
      try {
        requestError(
            ClientReceiveState(std::move(ex), std::move(thriftContext_->ctx)));
      } catch (...) {
        LOG(DFATAL)
            << "Exception thrown while executing requestError() callback. "
            << "Exception: " << folly::exceptionStr(std::current_exception());
      }
    }
    if (unmanaged_) {
      delete this;
    }
  }

  std::shared_ptr<folly::RequestContext> context_;

  struct Context {
    bool oneWay{false};
    uint16_t protocolId;
    std::shared_ptr<apache::thrift::ContextStack> ctx;
  };

 private:
  friend RequestClientCallback::Ptr toRequestClientCallbackPtr(
      std::unique_ptr<RequestCallback>,
      RequestCallback::Context);

  void setContext(Context context) {
    context_ = folly::RequestContext::saveContext();
    thriftContext_ = std::move(context);
  }

  void setUnmanaged() {
    unmanaged_ = true;
  }

  bool unmanaged_{false};
  folly::Optional<Context> thriftContext_;
};

inline RequestClientCallback::Ptr toRequestClientCallbackPtr(
    std::unique_ptr<RequestCallback> cb,
    RequestCallback::Context context) {
  if (!cb) {
    return RequestClientCallback::Ptr();
  }
  cb->setContext(std::move(context));
  cb->setUnmanaged();
  return RequestClientCallback::Ptr(cb.release());
}

/***
 *  Like RequestCallback, a base class to be derived, but with a different set
 *  of overridable member functions which may be better suited to some cases.
 */
class SendRecvRequestCallback : public RequestCallback {
 public:
  virtual void send(folly::exception_wrapper&& ex) = 0;
  virtual void recv(ClientReceiveState&& state) = 0;

 private:
  enum struct Phase { Send, Recv };

  void requestSent() final {
    send({});
    phase_ = Phase::Recv;
  }
  void requestError(ClientReceiveState&& state) final {
    switch (phase_) {
      case Phase::Send:
        send(std::move(state.exception()));
        phase_ = Phase::Recv;
        break;
      case Phase::Recv:
        recv(std::move(state));
        break;
    }
  }
  void replyReceived(ClientReceiveState&& state) final {
    recv(std::move(state));
  }

  Phase phase_{Phase::Send};
};

class FunctionSendRecvRequestCallback final : public SendRecvRequestCallback {
 public:
  using Send = folly::Function<void(folly::exception_wrapper&&)>;
  using Recv = folly::Function<void(ClientReceiveState&&)>;
  FunctionSendRecvRequestCallback(Send sendf, Recv recvf)
      : sendf_(std::move(sendf)), recvf_(std::move(recvf)) {}
  void send(folly::exception_wrapper&& ew) override {
    sendf_(std::move(ew));
  }
  void recv(ClientReceiveState&& state) override {
    recvf_(std::move(state));
  }

 private:
  Send sendf_;
  Recv recvf_;
};

/* FunctionReplyCallback is meant to make RequestCallback easy to use
 * with folly::Function objects.  It is slower than implementing
 * RequestCallback directly.  It also throws the specific error
 * away, since there is no place to save it in a backwards
 * compatible way to thrift1.  It is still logged, though.
 *
 * Recommend upgrading to RequestCallback if possible
 */
class FunctionReplyCallback : public RequestCallback {
 public:
  explicit FunctionReplyCallback(
      folly::Function<void(ClientReceiveState&&)> callback)
      : callback_(std::move(callback)) {}
  void replyReceived(ClientReceiveState&& state) override {
    callback_(std::move(state));
  }
  void requestError(ClientReceiveState&& state) override {
    VLOG(1) << "Got an exception in FunctionReplyCallback replyReceiveError: "
            << state.exception();
    callback_(std::move(state));
  }
  void requestSent() override {}

 private:
  folly::Function<void(ClientReceiveState&&)> callback_;
};

/* Useful for oneway methods. */
class FunctionSendCallback : public RequestCallback {
 public:
  explicit FunctionSendCallback(
      folly::Function<void(ClientReceiveState&&)>&& callback)
      : callback_(std::move(callback)) {}
  void requestSent() override {
    auto cb = std::move(callback_);
    cb(ClientReceiveState(folly::exception_wrapper(), nullptr));
  }
  void requestError(ClientReceiveState&& state) override {
    auto cb = std::move(callback_);
    cb(std::move(state));
  }
  void replyReceived(ClientReceiveState&& /*state*/) override {}

 private:
  folly::Function<void(ClientReceiveState&&)> callback_;
};

class CloseCallback {
 public:
  /**
   * When the channel is closed, replyError() will be invoked on all of the
   * outstanding replies, then channelClosed() on the CloseCallback.
   */
  virtual void channelClosed() = 0;

  virtual ~CloseCallback() {}
};

/**
 * RpcOptions class to set per-RPC options (such as request timeout).
 */
class RpcOptions {
 public:
  typedef apache::thrift::concurrency::PRIORITY PRIORITY;
  RpcOptions() {}

  /**
   * NOTE: This only sets the receive timeout, and not the send timeout on
   * transport. Probably you want to use HeaderClientChannel::setTimeout()
   */
  RpcOptions& setTimeout(std::chrono::milliseconds timeout) {
    timeout_ = timeout;
    return *this;
  }

  std::chrono::milliseconds getTimeout() const {
    return timeout_;
  }

  RpcOptions& setPriority(PRIORITY priority) {
    priority_ = static_cast<uint8_t>(priority);
    return *this;
  }

  PRIORITY getPriority() const {
    return static_cast<PRIORITY>(priority_);
  }

  // Do timeouts apply only on the client side?
  RpcOptions& setClientOnlyTimeouts(bool val) {
    clientOnlyTimeouts_ = val;
    return *this;
  }

  bool getClientOnlyTimeouts() const {
    return clientOnlyTimeouts_;
  }

  RpcOptions& setChunkTimeout(std::chrono::milliseconds chunkTimeout) {
    chunkTimeout_ = chunkTimeout;
    return *this;
  }

  std::chrono::milliseconds getChunkTimeout() const {
    return chunkTimeout_;
  }

  RpcOptions& setQueueTimeout(std::chrono::milliseconds queueTimeout) {
    queueTimeout_ = queueTimeout;
    return *this;
  }

  std::chrono::milliseconds getQueueTimeout() const {
    return queueTimeout_;
  }

  void setWriteHeader(const std::string& key, const std::string& value) {
    writeHeaders_[key] = value;
  }

  void setReadHeaders(std::map<std::string, std::string>&& readHeaders) {
    readHeaders_ = std::move(readHeaders);
  }

  const std::map<std::string, std::string>& getReadHeaders() const {
    return readHeaders_;
  }

  const std::map<std::string, std::string>& getWriteHeaders() const {
    return writeHeaders_;
  }

  std::map<std::string, std::string> releaseWriteHeaders() {
    std::map<std::string, std::string> headers;
    writeHeaders_.swap(headers);
    return headers;
  }

 private:
  std::chrono::milliseconds timeout_{0};
  std::chrono::milliseconds chunkTimeout_{0};
  std::chrono::milliseconds queueTimeout_{0};
  uint8_t priority_{apache::thrift::concurrency::N_PRIORITIES};
  bool clientOnlyTimeouts_{false};

  // For sending and receiving headers.
  std::map<std::string, std::string> writeHeaders_;
  std::map<std::string, std::string> readHeaders_;
};
} // namespace thrift
} // namespace apache
