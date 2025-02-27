/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#include "thrift/compiler/test/fixtures/doctext/gen-cpp2/CAsyncClient.h"

#include <folly/io/IOBuf.h>
#include <folly/io/IOBufQueue.h>
#include <thrift/lib/cpp/TApplicationException.h>
#include <thrift/lib/cpp/transport/THeader.h>
#include <thrift/lib/cpp2/gen/client_cpp.h>
#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/server/Cpp2ConnContext.h>
#include <thrift/lib/cpp2/GeneratedCodeHelper.h>
#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>

namespace cpp2 {
typedef apache::thrift::ThriftPresult<false> C_f_pargs;
typedef apache::thrift::ThriftPresult<true> C_f_presult;

template <typename Protocol_>
void CAsyncClient::fT(Protocol_* prot, apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback) {
  std::shared_ptr<apache::thrift::transport::THeader> header(ctx, &ctx->header);
  C_f_pargs args;
  auto sizer = [&](Protocol_* p) { return args.serializedSizeZC(p); };
  auto writer = [&](Protocol_* p) { args.write(p); };
  apache::thrift::clientSendT<Protocol_>(prot, rpcOptions, std::move(callback), ctx->ctx, std::move(header), channel_.get(), "f", writer, sizer, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE);
  ctx->reqContext.setRequestHeader(nullptr);
}



void CAsyncClient::f(std::unique_ptr<apache::thrift::RequestCallback> callback) {
  ::apache::thrift::RpcOptions rpcOptions;
  f(rpcOptions, std::move(callback));
}

void CAsyncClient::f(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback) {
  auto ctx = std::make_shared<apache::thrift::detail::ac::ClientRequestContext>(getChannel()->getProtocolId(), rpcOptions.releaseWriteHeaders(), this->handlers_, this->getServiceName(), "C.f");
  apache::thrift::RequestCallback::Context callbackContext;
  callbackContext.protocolId = getChannel()->getProtocolId();
  callbackContext.ctx = std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx);
  fImpl(rpcOptions, std::move(ctx), apache::thrift::toRequestClientCallbackPtr(std::move(callback), std::move(callbackContext)));
}

void CAsyncClient::fImpl(apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback) {
  switch(getChannel()->getProtocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolWriter writer;
      fT(&writer, rpcOptions, std::move(ctx), std::move(callback));
      break;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolWriter writer;
      fT(&writer, rpcOptions, std::move(ctx), std::move(callback));
      break;
    }
    default:
    {
      apache::thrift::detail::ac::throw_app_exn("Could not find Protocol");
    }
  }
}

void CAsyncClient::sync_f() {
  ::apache::thrift::RpcOptions rpcOptions;
  sync_f(rpcOptions);
}

void CAsyncClient::sync_f(apache::thrift::RpcOptions& rpcOptions) {
  apache::thrift::ClientReceiveState _returnState;
  apache::thrift::ClientSyncCallback<false> callback(&_returnState);
  auto protocolId = getChannel()->getProtocolId();
  auto evb = getChannel()->getEventBase();
  auto ctx = std::make_shared<apache::thrift::detail::ac::ClientRequestContext>(protocolId, rpcOptions.releaseWriteHeaders(), this->handlers_, this->getServiceName(), "C.f");
  fImpl(rpcOptions, ctx, apache::thrift::RequestClientCallback::Ptr(&callback));
  callback.waitUntilDone(evb);
  _returnState.resetProtocolId(protocolId);
  _returnState.resetCtx(std::shared_ptr<apache::thrift::ContextStack>(ctx, &ctx->ctx));
  SCOPE_EXIT {
    if (_returnState.header() && !_returnState.header()->getHeaders().empty()) {
      rpcOptions.setReadHeaders(_returnState.header()->releaseHeaders());
    }
  };
  if (!_returnState.buf()) {
    assert(!!_returnState.exception());
    _returnState.exception().throw_exception();
  }
  recv_f(_returnState);
}

folly::Future<folly::Unit> CAsyncClient::future_f() {
  ::apache::thrift::RpcOptions rpcOptions;
  return future_f(rpcOptions);
}

folly::SemiFuture<folly::Unit> CAsyncClient::semifuture_f() {
  ::apache::thrift::RpcOptions rpcOptions;
  return semifuture_f(rpcOptions);
}

folly::Future<folly::Unit> CAsyncClient::future_f(apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise<folly::Unit> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<apache::thrift::FutureCallback<folly::Unit>>(std::move(_promise), recv_wrapped_f, channel_);
  f(rpcOptions, std::move(callback));
  return _future;
}

folly::SemiFuture<folly::Unit> CAsyncClient::semifuture_f(apache::thrift::RpcOptions& rpcOptions) {
  auto callbackAndFuture = makeSemiFutureCallback(recv_wrapped_f, channel_);
  auto callback = std::move(callbackAndFuture.first);
  f(rpcOptions, std::move(callback));
  return std::move(callbackAndFuture.second);
}

folly::Future<std::pair<folly::Unit, std::unique_ptr<apache::thrift::transport::THeader>>> CAsyncClient::header_future_f(apache::thrift::RpcOptions& rpcOptions) {
  folly::Promise<std::pair<folly::Unit, std::unique_ptr<apache::thrift::transport::THeader>>> _promise;
  auto _future = _promise.getFuture();
  auto callback = std::make_unique<apache::thrift::HeaderFutureCallback<folly::Unit>>(std::move(_promise), recv_wrapped_f, channel_);
  f(rpcOptions, std::move(callback));
  return _future;
}

folly::SemiFuture<std::pair<folly::Unit, std::unique_ptr<apache::thrift::transport::THeader>>> CAsyncClient::header_semifuture_f(apache::thrift::RpcOptions& rpcOptions) {
  auto callbackAndFuture = makeHeaderSemiFutureCallback(recv_wrapped_f, channel_);
  auto callback = std::move(callbackAndFuture.first);
  f(rpcOptions, std::move(callback));
  return std::move(callbackAndFuture.second);
}

void CAsyncClient::f(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback) {
  f(std::make_unique<apache::thrift::FunctionReplyCallback>(std::move(callback)));
}

folly::exception_wrapper CAsyncClient::recv_wrapped_f(::apache::thrift::ClientReceiveState& state) {
  if (state.isException()) {
    return std::move(state.exception());
  }
  if (!state.buf()) {
    return folly::make_exception_wrapper<apache::thrift::TApplicationException>("recv_ called without result");
  }

  using result = C_f_presult;
  constexpr auto const fname = "f";
  switch (state.protocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state);
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader reader;
      return apache::thrift::detail::ac::recv_wrapped<result>(
          fname, &reader, state);
    }
    default:
    {
    }
  }
  return folly::make_exception_wrapper<apache::thrift::TApplicationException>("Could not find Protocol");
}

void CAsyncClient::recv_f(::apache::thrift::ClientReceiveState& state) {
  auto ew = recv_wrapped_f(state);
  if (ew) {
    ew.throw_exception();
  }
}

void CAsyncClient::recv_instance_f(::apache::thrift::ClientReceiveState& state) {
  recv_f(state);
}

folly::exception_wrapper CAsyncClient::recv_instance_wrapped_f(::apache::thrift::ClientReceiveState& state) {
  return recv_wrapped_f(state);
}

} // cpp2
namespace apache { namespace thrift {

}} // apache::thrift
