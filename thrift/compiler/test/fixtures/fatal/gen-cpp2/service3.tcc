/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "thrift/compiler/test/fixtures/fatal/gen-cpp2/service3.h"

#include <folly/io/IOBuf.h>
#include <folly/io/IOBufQueue.h>
#include <thrift/lib/cpp/TApplicationException.h>
#include <thrift/lib/cpp/transport/THeader.h>
#include <thrift/lib/cpp2/GeneratedCodeHelper.h>
#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>
#include <thrift/lib/cpp2/gen/service_tcc.h>
#include <thrift/lib/cpp2/server/Cpp2ConnContext.h>

namespace test_cpp2 { namespace cpp_reflection {
typedef apache::thrift::ThriftPresult<false> service3_methodA_pargs;
typedef apache::thrift::ThriftPresult<true> service3_methodA_presult;
typedef apache::thrift::ThriftPresult<false, apache::thrift::FieldData<1, apache::thrift::protocol::T_I32, int32_t*>, apache::thrift::FieldData<2, apache::thrift::protocol::T_STRUCT,  ::test_cpp2::cpp_reflection::struct1*>, apache::thrift::FieldData<3, apache::thrift::protocol::T_DOUBLE, double*>> service3_methodB_pargs;
typedef apache::thrift::ThriftPresult<true> service3_methodB_presult;
typedef apache::thrift::ThriftPresult<false> service3_methodC_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, apache::thrift::protocol::T_I32, int32_t*>> service3_methodC_presult;
typedef apache::thrift::ThriftPresult<false, apache::thrift::FieldData<1, apache::thrift::protocol::T_I32, int32_t*>, apache::thrift::FieldData<2, apache::thrift::protocol::T_STRUCT,  ::test_cpp2::cpp_reflection::struct1*>, apache::thrift::FieldData<3, apache::thrift::protocol::T_DOUBLE, double*>> service3_methodD_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, apache::thrift::protocol::T_I32, int32_t*>> service3_methodD_presult;
typedef apache::thrift::ThriftPresult<false> service3_methodE_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, apache::thrift::protocol::T_STRUCT,  ::test_cpp2::cpp_reflection::struct2*>> service3_methodE_presult;
typedef apache::thrift::ThriftPresult<false, apache::thrift::FieldData<1, apache::thrift::protocol::T_I32, int32_t*>, apache::thrift::FieldData<2, apache::thrift::protocol::T_STRUCT,  ::test_cpp2::cpp_reflection::struct1*>, apache::thrift::FieldData<3, apache::thrift::protocol::T_DOUBLE, double*>> service3_methodF_pargs;
typedef apache::thrift::ThriftPresult<true, apache::thrift::FieldData<0, apache::thrift::protocol::T_STRUCT,  ::test_cpp2::cpp_reflection::struct3*>> service3_methodF_presult;
template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::_processInThread_methodA(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  auto pri = iface_->getRequestPriority(ctx, apache::thrift::concurrency::NORMAL);
  processInThread<ProtocolIn_, ProtocolOut_>(std::move(req), std::move(buf), ctx, eb, tm, pri, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &service3AsyncProcessor::process_methodA<ProtocolIn_, ProtocolOut_>, this);
}
template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::process_methodA(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  // make sure getConnectionContext is null
  // so async calls don't accidentally use it
  iface_->setConnectionContext(nullptr);
  service3_methodA_pargs args;
  std::unique_ptr<apache::thrift::ContextStack> ctxStack(this->getContextStack(this->getServiceName(), "service3.methodA", ctx));
  try {
    folly::io::Cursor cursor(buf.get());
    cursor.skip(ctx->getMessageBeginSize());
    ProtocolIn_ iprot;
    iprot.setInput(cursor);
    deserializeRequest(args, buf.get(), &iprot, ctxStack.get());
  }
  catch (const std::exception& ex) {
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ex, std::move(req), ctx, eb, "methodA");
    return;
  }
  req->setStartedProcessing();
  auto callback = std::make_unique<apache::thrift::HandlerCallback<void>>(std::move(req), std::move(ctxStack), return_methodA<ProtocolIn_,ProtocolOut_>, throw_wrapped_methodA<ProtocolIn_, ProtocolOut_>, ctx->getProtoSeqId(), eb, tm, ctx);
  if (!callback->isRequestActive()) {
    callback.release()->deleteInThread();
    return;
  }
  ctx->setStartedProcessing();
  iface_->async_tm_methodA(std::move(callback));
}

template <class ProtocolIn_, class ProtocolOut_>
folly::IOBufQueue service3AsyncProcessor::return_methodA(int32_t protoSeqId, apache::thrift::ContextStack* ctx) {
  ProtocolOut_ prot;
  service3_methodA_presult result;
  return serializeResponse("methodA", &prot, protoSeqId, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void service3AsyncProcessor::throw_wrapped_methodA(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    (void)protoSeqId;
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "methodA");
    return;
  }
}

template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::_processInThread_methodB(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  auto pri = iface_->getRequestPriority(ctx, apache::thrift::concurrency::NORMAL);
  processInThread<ProtocolIn_, ProtocolOut_>(std::move(req), std::move(buf), ctx, eb, tm, pri, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &service3AsyncProcessor::process_methodB<ProtocolIn_, ProtocolOut_>, this);
}
template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::process_methodB(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  // make sure getConnectionContext is null
  // so async calls don't accidentally use it
  iface_->setConnectionContext(nullptr);
  service3_methodB_pargs args;
  int32_t uarg_x{0};
  args.get<0>().value = &uarg_x;
  auto uarg_y = std::make_unique< ::test_cpp2::cpp_reflection::struct1>();
  args.get<1>().value = uarg_y.get();
  double uarg_z{0};
  args.get<2>().value = &uarg_z;
  std::unique_ptr<apache::thrift::ContextStack> ctxStack(this->getContextStack(this->getServiceName(), "service3.methodB", ctx));
  try {
    folly::io::Cursor cursor(buf.get());
    cursor.skip(ctx->getMessageBeginSize());
    ProtocolIn_ iprot;
    iprot.setInput(cursor);
    deserializeRequest(args, buf.get(), &iprot, ctxStack.get());
  }
  catch (const std::exception& ex) {
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ex, std::move(req), ctx, eb, "methodB");
    return;
  }
  req->setStartedProcessing();
  auto callback = std::make_unique<apache::thrift::HandlerCallback<void>>(std::move(req), std::move(ctxStack), return_methodB<ProtocolIn_,ProtocolOut_>, throw_wrapped_methodB<ProtocolIn_, ProtocolOut_>, ctx->getProtoSeqId(), eb, tm, ctx);
  if (!callback->isRequestActive()) {
    callback.release()->deleteInThread();
    return;
  }
  ctx->setStartedProcessing();
  iface_->async_tm_methodB(std::move(callback), args.get<0>().ref(), std::move(uarg_y), args.get<2>().ref());
}

template <class ProtocolIn_, class ProtocolOut_>
folly::IOBufQueue service3AsyncProcessor::return_methodB(int32_t protoSeqId, apache::thrift::ContextStack* ctx) {
  ProtocolOut_ prot;
  service3_methodB_presult result;
  return serializeResponse("methodB", &prot, protoSeqId, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void service3AsyncProcessor::throw_wrapped_methodB(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    (void)protoSeqId;
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "methodB");
    return;
  }
}

template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::_processInThread_methodC(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  auto pri = iface_->getRequestPriority(ctx, apache::thrift::concurrency::NORMAL);
  processInThread<ProtocolIn_, ProtocolOut_>(std::move(req), std::move(buf), ctx, eb, tm, pri, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &service3AsyncProcessor::process_methodC<ProtocolIn_, ProtocolOut_>, this);
}
template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::process_methodC(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  // make sure getConnectionContext is null
  // so async calls don't accidentally use it
  iface_->setConnectionContext(nullptr);
  service3_methodC_pargs args;
  std::unique_ptr<apache::thrift::ContextStack> ctxStack(this->getContextStack(this->getServiceName(), "service3.methodC", ctx));
  try {
    folly::io::Cursor cursor(buf.get());
    cursor.skip(ctx->getMessageBeginSize());
    ProtocolIn_ iprot;
    iprot.setInput(cursor);
    deserializeRequest(args, buf.get(), &iprot, ctxStack.get());
  }
  catch (const std::exception& ex) {
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ex, std::move(req), ctx, eb, "methodC");
    return;
  }
  req->setStartedProcessing();
  auto callback = std::make_unique<apache::thrift::HandlerCallback<int32_t>>(std::move(req), std::move(ctxStack), return_methodC<ProtocolIn_,ProtocolOut_>, throw_wrapped_methodC<ProtocolIn_, ProtocolOut_>, ctx->getProtoSeqId(), eb, tm, ctx);
  if (!callback->isRequestActive()) {
    callback.release()->deleteInThread();
    return;
  }
  ctx->setStartedProcessing();
  iface_->async_tm_methodC(std::move(callback));
}

template <class ProtocolIn_, class ProtocolOut_>
folly::IOBufQueue service3AsyncProcessor::return_methodC(int32_t protoSeqId, apache::thrift::ContextStack* ctx, int32_t const& _return) {
  ProtocolOut_ prot;
  service3_methodC_presult result;
  result.get<0>().value = const_cast<int32_t*>(&_return);
  result.setIsSet(0, true);
  return serializeResponse("methodC", &prot, protoSeqId, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void service3AsyncProcessor::throw_wrapped_methodC(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    (void)protoSeqId;
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "methodC");
    return;
  }
}

template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::_processInThread_methodD(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  auto pri = iface_->getRequestPriority(ctx, apache::thrift::concurrency::NORMAL);
  processInThread<ProtocolIn_, ProtocolOut_>(std::move(req), std::move(buf), ctx, eb, tm, pri, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &service3AsyncProcessor::process_methodD<ProtocolIn_, ProtocolOut_>, this);
}
template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::process_methodD(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  // make sure getConnectionContext is null
  // so async calls don't accidentally use it
  iface_->setConnectionContext(nullptr);
  service3_methodD_pargs args;
  int32_t uarg_i{0};
  args.get<0>().value = &uarg_i;
  auto uarg_j = std::make_unique< ::test_cpp2::cpp_reflection::struct1>();
  args.get<1>().value = uarg_j.get();
  double uarg_k{0};
  args.get<2>().value = &uarg_k;
  std::unique_ptr<apache::thrift::ContextStack> ctxStack(this->getContextStack(this->getServiceName(), "service3.methodD", ctx));
  try {
    folly::io::Cursor cursor(buf.get());
    cursor.skip(ctx->getMessageBeginSize());
    ProtocolIn_ iprot;
    iprot.setInput(cursor);
    deserializeRequest(args, buf.get(), &iprot, ctxStack.get());
  }
  catch (const std::exception& ex) {
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ex, std::move(req), ctx, eb, "methodD");
    return;
  }
  req->setStartedProcessing();
  auto callback = std::make_unique<apache::thrift::HandlerCallback<int32_t>>(std::move(req), std::move(ctxStack), return_methodD<ProtocolIn_,ProtocolOut_>, throw_wrapped_methodD<ProtocolIn_, ProtocolOut_>, ctx->getProtoSeqId(), eb, tm, ctx);
  if (!callback->isRequestActive()) {
    callback.release()->deleteInThread();
    return;
  }
  ctx->setStartedProcessing();
  iface_->async_tm_methodD(std::move(callback), args.get<0>().ref(), std::move(uarg_j), args.get<2>().ref());
}

template <class ProtocolIn_, class ProtocolOut_>
folly::IOBufQueue service3AsyncProcessor::return_methodD(int32_t protoSeqId, apache::thrift::ContextStack* ctx, int32_t const& _return) {
  ProtocolOut_ prot;
  service3_methodD_presult result;
  result.get<0>().value = const_cast<int32_t*>(&_return);
  result.setIsSet(0, true);
  return serializeResponse("methodD", &prot, protoSeqId, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void service3AsyncProcessor::throw_wrapped_methodD(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    (void)protoSeqId;
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "methodD");
    return;
  }
}

template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::_processInThread_methodE(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  auto pri = iface_->getRequestPriority(ctx, apache::thrift::concurrency::NORMAL);
  processInThread<ProtocolIn_, ProtocolOut_>(std::move(req), std::move(buf), ctx, eb, tm, pri, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &service3AsyncProcessor::process_methodE<ProtocolIn_, ProtocolOut_>, this);
}
template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::process_methodE(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  // make sure getConnectionContext is null
  // so async calls don't accidentally use it
  iface_->setConnectionContext(nullptr);
  service3_methodE_pargs args;
  std::unique_ptr<apache::thrift::ContextStack> ctxStack(this->getContextStack(this->getServiceName(), "service3.methodE", ctx));
  try {
    folly::io::Cursor cursor(buf.get());
    cursor.skip(ctx->getMessageBeginSize());
    ProtocolIn_ iprot;
    iprot.setInput(cursor);
    deserializeRequest(args, buf.get(), &iprot, ctxStack.get());
  }
  catch (const std::exception& ex) {
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ex, std::move(req), ctx, eb, "methodE");
    return;
  }
  req->setStartedProcessing();
  auto callback = std::make_unique<apache::thrift::HandlerCallback<std::unique_ptr< ::test_cpp2::cpp_reflection::struct2>>>(std::move(req), std::move(ctxStack), return_methodE<ProtocolIn_,ProtocolOut_>, throw_wrapped_methodE<ProtocolIn_, ProtocolOut_>, ctx->getProtoSeqId(), eb, tm, ctx);
  if (!callback->isRequestActive()) {
    callback.release()->deleteInThread();
    return;
  }
  ctx->setStartedProcessing();
  iface_->async_tm_methodE(std::move(callback));
}

template <class ProtocolIn_, class ProtocolOut_>
folly::IOBufQueue service3AsyncProcessor::return_methodE(int32_t protoSeqId, apache::thrift::ContextStack* ctx,  ::test_cpp2::cpp_reflection::struct2 const& _return) {
  ProtocolOut_ prot;
  service3_methodE_presult result;
  result.get<0>().value = const_cast< ::test_cpp2::cpp_reflection::struct2*>(&_return);
  result.setIsSet(0, true);
  return serializeResponse("methodE", &prot, protoSeqId, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void service3AsyncProcessor::throw_wrapped_methodE(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    (void)protoSeqId;
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "methodE");
    return;
  }
}

template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::_processInThread_methodF(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  auto pri = iface_->getRequestPriority(ctx, apache::thrift::concurrency::NORMAL);
  processInThread<ProtocolIn_, ProtocolOut_>(std::move(req), std::move(buf), ctx, eb, tm, pri, apache::thrift::RpcKind::SINGLE_REQUEST_SINGLE_RESPONSE, &service3AsyncProcessor::process_methodF<ProtocolIn_, ProtocolOut_>, this);
}
template <typename ProtocolIn_, typename ProtocolOut_>
void service3AsyncProcessor::process_methodF(std::unique_ptr<apache::thrift::ResponseChannelRequest> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  // make sure getConnectionContext is null
  // so async calls don't accidentally use it
  iface_->setConnectionContext(nullptr);
  service3_methodF_pargs args;
  int32_t uarg_l{0};
  args.get<0>().value = &uarg_l;
  auto uarg_m = std::make_unique< ::test_cpp2::cpp_reflection::struct1>();
  args.get<1>().value = uarg_m.get();
  double uarg_n{0};
  args.get<2>().value = &uarg_n;
  std::unique_ptr<apache::thrift::ContextStack> ctxStack(this->getContextStack(this->getServiceName(), "service3.methodF", ctx));
  try {
    folly::io::Cursor cursor(buf.get());
    cursor.skip(ctx->getMessageBeginSize());
    ProtocolIn_ iprot;
    iprot.setInput(cursor);
    deserializeRequest(args, buf.get(), &iprot, ctxStack.get());
  }
  catch (const std::exception& ex) {
    apache::thrift::detail::ap::process_handle_exn_deserialization<ProtocolOut_>(
        ex, std::move(req), ctx, eb, "methodF");
    return;
  }
  req->setStartedProcessing();
  auto callback = std::make_unique<apache::thrift::HandlerCallback<std::unique_ptr< ::test_cpp2::cpp_reflection::struct3>>>(std::move(req), std::move(ctxStack), return_methodF<ProtocolIn_,ProtocolOut_>, throw_wrapped_methodF<ProtocolIn_, ProtocolOut_>, ctx->getProtoSeqId(), eb, tm, ctx);
  if (!callback->isRequestActive()) {
    callback.release()->deleteInThread();
    return;
  }
  ctx->setStartedProcessing();
  iface_->async_tm_methodF(std::move(callback), args.get<0>().ref(), std::move(uarg_m), args.get<2>().ref());
}

template <class ProtocolIn_, class ProtocolOut_>
folly::IOBufQueue service3AsyncProcessor::return_methodF(int32_t protoSeqId, apache::thrift::ContextStack* ctx,  ::test_cpp2::cpp_reflection::struct3 const& _return) {
  ProtocolOut_ prot;
  service3_methodF_presult result;
  result.get<0>().value = const_cast< ::test_cpp2::cpp_reflection::struct3*>(&_return);
  result.setIsSet(0, true);
  return serializeResponse("methodF", &prot, protoSeqId, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void service3AsyncProcessor::throw_wrapped_methodF(std::unique_ptr<apache::thrift::ResponseChannelRequest> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  {
    (void)protoSeqId;
    apache::thrift::detail::ap::process_throw_wrapped_handler_error<ProtocolOut_>(
        ew, std::move(req), reqCtx, ctx, "methodF");
    return;
  }
}

}} // test_cpp2::cpp_reflection
namespace apache { namespace thrift {

}} // apache::thrift
