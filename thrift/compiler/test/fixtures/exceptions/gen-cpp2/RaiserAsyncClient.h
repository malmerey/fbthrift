/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <folly/futures/Future.h>
#include <thrift/lib/cpp/TApplicationException.h>
#include <thrift/lib/cpp2/async/AsyncClient.h>
#include <thrift/lib/cpp2/async/FutureRequest.h>
#include "thrift/compiler/test/fixtures/exceptions/gen-cpp2/module_types.h"

namespace folly {
  class IOBuf;
  class IOBufQueue;
}
namespace apache { namespace thrift {
  class Cpp2RequestContext;
  class BinaryProtocolReader;
  class CompactProtocolReader;
  namespace detail { namespace ac { struct ClientRequestContext; }}
  namespace transport { class THeader; }
}}

namespace cpp2 {

class RaiserAsyncClient : public apache::thrift::GeneratedAsyncClient {
 public:
  using apache::thrift::GeneratedAsyncClient::GeneratedAsyncClient;

  char const* getServiceName() const noexcept override {
    return "Raiser";
  }

  virtual void doBland(std::unique_ptr<apache::thrift::RequestCallback> callback);
  virtual void doBland(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback);
 private:
  void doBlandImpl(apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
  virtual void sync_doBland();
  virtual void sync_doBland(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::Future<folly::Unit> future_doBland();
  virtual folly::SemiFuture<folly::Unit> semifuture_doBland();
  virtual folly::Future<folly::Unit> future_doBland(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<folly::Unit> semifuture_doBland(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::Future<std::pair<folly::Unit, std::unique_ptr<apache::thrift::transport::THeader>>> header_future_doBland(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<std::pair<folly::Unit, std::unique_ptr<apache::thrift::transport::THeader>>> header_semifuture_doBland(apache::thrift::RpcOptions& rpcOptions);
  virtual void doBland(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback);
  static folly::exception_wrapper recv_wrapped_doBland(::apache::thrift::ClientReceiveState& state);
  static void recv_doBland(::apache::thrift::ClientReceiveState& state);
  // Mock friendly virtual instance method
  virtual void recv_instance_doBland(::apache::thrift::ClientReceiveState& state);
  virtual folly::exception_wrapper recv_instance_wrapped_doBland(::apache::thrift::ClientReceiveState& state);
 private:
  template <typename Protocol_>
  void doBlandT(Protocol_* prot, apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
  virtual void doRaise(std::unique_ptr<apache::thrift::RequestCallback> callback);
  virtual void doRaise(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback);
 private:
  void doRaiseImpl(apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
  virtual void sync_doRaise();
  virtual void sync_doRaise(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::Future<folly::Unit> future_doRaise();
  virtual folly::SemiFuture<folly::Unit> semifuture_doRaise();
  virtual folly::Future<folly::Unit> future_doRaise(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<folly::Unit> semifuture_doRaise(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::Future<std::pair<folly::Unit, std::unique_ptr<apache::thrift::transport::THeader>>> header_future_doRaise(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<std::pair<folly::Unit, std::unique_ptr<apache::thrift::transport::THeader>>> header_semifuture_doRaise(apache::thrift::RpcOptions& rpcOptions);
  virtual void doRaise(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback);
  static folly::exception_wrapper recv_wrapped_doRaise(::apache::thrift::ClientReceiveState& state);
  static void recv_doRaise(::apache::thrift::ClientReceiveState& state);
  // Mock friendly virtual instance method
  virtual void recv_instance_doRaise(::apache::thrift::ClientReceiveState& state);
  virtual folly::exception_wrapper recv_instance_wrapped_doRaise(::apache::thrift::ClientReceiveState& state);
 private:
  template <typename Protocol_>
  void doRaiseT(Protocol_* prot, apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
  virtual void get200(std::unique_ptr<apache::thrift::RequestCallback> callback);
  virtual void get200(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback);
 private:
  void get200Impl(apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
  virtual void sync_get200(std::string& _return);
  virtual void sync_get200(apache::thrift::RpcOptions& rpcOptions, std::string& _return);
  virtual folly::Future<std::string> future_get200();
  virtual folly::SemiFuture<std::string> semifuture_get200();
  virtual folly::Future<std::string> future_get200(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<std::string> semifuture_get200(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::Future<std::pair<std::string, std::unique_ptr<apache::thrift::transport::THeader>>> header_future_get200(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<std::pair<std::string, std::unique_ptr<apache::thrift::transport::THeader>>> header_semifuture_get200(apache::thrift::RpcOptions& rpcOptions);
  virtual void get200(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback);
  static folly::exception_wrapper recv_wrapped_get200(std::string& _return, ::apache::thrift::ClientReceiveState& state);
  static void recv_get200(std::string& _return, ::apache::thrift::ClientReceiveState& state);
  // Mock friendly virtual instance method
  virtual void recv_instance_get200(std::string& _return, ::apache::thrift::ClientReceiveState& state);
  virtual folly::exception_wrapper recv_instance_wrapped_get200(std::string& _return, ::apache::thrift::ClientReceiveState& state);
 private:
  template <typename Protocol_>
  void get200T(Protocol_* prot, apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
  virtual void get500(std::unique_ptr<apache::thrift::RequestCallback> callback);
  virtual void get500(apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback);
 private:
  void get500Impl(apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
  virtual void sync_get500(std::string& _return);
  virtual void sync_get500(apache::thrift::RpcOptions& rpcOptions, std::string& _return);
  virtual folly::Future<std::string> future_get500();
  virtual folly::SemiFuture<std::string> semifuture_get500();
  virtual folly::Future<std::string> future_get500(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<std::string> semifuture_get500(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::Future<std::pair<std::string, std::unique_ptr<apache::thrift::transport::THeader>>> header_future_get500(apache::thrift::RpcOptions& rpcOptions);
  virtual folly::SemiFuture<std::pair<std::string, std::unique_ptr<apache::thrift::transport::THeader>>> header_semifuture_get500(apache::thrift::RpcOptions& rpcOptions);
  virtual void get500(folly::Function<void (::apache::thrift::ClientReceiveState&&)> callback);
  static folly::exception_wrapper recv_wrapped_get500(std::string& _return, ::apache::thrift::ClientReceiveState& state);
  static void recv_get500(std::string& _return, ::apache::thrift::ClientReceiveState& state);
  // Mock friendly virtual instance method
  virtual void recv_instance_get500(std::string& _return, ::apache::thrift::ClientReceiveState& state);
  virtual folly::exception_wrapper recv_instance_wrapped_get500(std::string& _return, ::apache::thrift::ClientReceiveState& state);
 private:
  template <typename Protocol_>
  void get500T(Protocol_* prot, apache::thrift::RpcOptions& rpcOptions, std::shared_ptr<apache::thrift::detail::ac::ClientRequestContext> ctx, apache::thrift::RequestClientCallback::Ptr callback);
 public:
};

} // cpp2
