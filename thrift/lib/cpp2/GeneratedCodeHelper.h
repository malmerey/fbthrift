/*
 * Copyright 2004-present Facebook, Inc.
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

#include <type_traits>
#include <utility>

#include <fmt/core.h>
#include <folly/Traits.h>
#include <folly/futures/Future.h>
#include <folly/io/Cursor.h>
#include <thrift/lib/cpp2/FrozenTApplicationException.h>
#include <thrift/lib/cpp2/GeneratedHeaderHelper.h>
#include <thrift/lib/cpp2/SerializationSwitch.h>
#include <thrift/lib/cpp2/Thrift.h>
#include <thrift/lib/cpp2/async/AsyncProcessor.h>
#include <thrift/lib/cpp2/async/RequestChannel.h>
#include <thrift/lib/cpp2/async/Stream.h>
#include <thrift/lib/cpp2/frozen/Frozen.h>
#include <thrift/lib/cpp2/util/Frozen2ViewHelpers.h>

#include <thrift/lib/cpp2/protocol/Cpp2Ops.tcc>

namespace apache {
namespace thrift {

namespace detail {

// For streaming, the default 16KB Protocol growth can be memory aggressive.
constexpr size_t kStreamingQueueAppenderGrowth = 4096;

template <int N, int Size, class F, class Tuple>
struct ForEachImpl {
  static uint32_t forEach(Tuple&& tuple, F&& f) {
    uint32_t res = f(std::get<N>(tuple), N);
    res += ForEachImpl<N + 1, Size, F, Tuple>::forEach(
        std::forward<Tuple>(tuple), std::forward<F>(f));
    return res;
  }
};
template <int Size, class F, class Tuple>
struct ForEachImpl<Size, Size, F, Tuple> {
  static uint32_t forEach(Tuple&& /*tuple*/, F&& /*f*/) {
    return 0;
  }
};

template <int N = 0, class F, class Tuple>
uint32_t forEach(Tuple&& tuple, F&& f) {
  return ForEachImpl<
      N,
      std::tuple_size<typename std::remove_reference<Tuple>::type>::value,
      F,
      Tuple>::forEach(std::forward<Tuple>(tuple), std::forward<F>(f));
}

template <int N, int Size, class F, class Tuple>
struct ForEachVoidImpl {
  static void forEach(Tuple&& tuple, F&& f) {
    f(std::get<N>(tuple), N);
    ForEachVoidImpl<N + 1, Size, F, Tuple>::forEach(
        std::forward<Tuple>(tuple), std::forward<F>(f));
  }
};
template <int Size, class F, class Tuple>
struct ForEachVoidImpl<Size, Size, F, Tuple> {
  static void forEach(Tuple&& /*tuple*/, F&& /*f*/) {}
};

template <int N = 0, class F, class Tuple>
void forEachVoid(Tuple&& tuple, F&& f) {
  ForEachVoidImpl<
      N,
      std::tuple_size<typename std::remove_reference<Tuple>::type>::value,
      F,
      Tuple>::forEach(std::forward<Tuple>(tuple), std::forward<F>(f));
}

template <typename Protocol, typename IsSet>
struct Writer {
  Writer(Protocol* prot, const IsSet& isset) : prot_(prot), isset_(isset) {}
  template <typename FieldData>
  uint32_t operator()(const FieldData& fieldData, int index) {
    using Ops = Cpp2Ops<typename FieldData::ref_type>;

    if (!isset_.getIsSet(index)) {
      return 0;
    }

    int16_t fid = FieldData::fid;
    const auto& ex = fieldData.ref();

    uint32_t xfer = 0;
    xfer += prot_->writeFieldBegin("", Ops::thriftType(), fid);
    xfer += Ops::write(prot_, &ex);
    xfer += prot_->writeFieldEnd();
    return xfer;
  }

 private:
  Protocol* prot_;
  const IsSet& isset_;
};

template <typename Protocol, typename IsSet>
struct Sizer {
  Sizer(Protocol* prot, const IsSet& isset) : prot_(prot), isset_(isset) {}
  template <typename FieldData>
  uint32_t operator()(const FieldData& fieldData, int index) {
    using Ops = Cpp2Ops<typename FieldData::ref_type>;

    if (!isset_.getIsSet(index)) {
      return 0;
    }

    int16_t fid = FieldData::fid;
    const auto& ex = fieldData.ref();

    uint32_t xfer = 0;
    xfer += prot_->serializedFieldSize("", Ops::thriftType(), fid);
    xfer += Ops::serializedSize(prot_, &ex);
    return xfer;
  }

 private:
  Protocol* prot_;
  const IsSet& isset_;
};

template <typename Protocol, typename IsSet>
struct SizerZC {
  SizerZC(Protocol* prot, const IsSet& isset) : prot_(prot), isset_(isset) {}
  template <typename FieldData>
  uint32_t operator()(const FieldData& fieldData, int index) {
    using Ops = Cpp2Ops<typename FieldData::ref_type>;

    if (!isset_.getIsSet(index)) {
      return 0;
    }

    int16_t fid = FieldData::fid;
    const auto& ex = fieldData.ref();

    uint32_t xfer = 0;
    xfer += prot_->serializedFieldSize("", Ops::thriftType(), fid);
    xfer += Ops::serializedSizeZC(prot_, &ex);
    return xfer;
  }

 private:
  Protocol* prot_;
  const IsSet& isset_;
};

template <typename Protocol, typename IsSet>
struct Reader {
  Reader(
      Protocol* prot,
      IsSet& isset,
      int16_t fid,
      protocol::TType ftype,
      bool& success)
      : prot_(prot),
        isset_(isset),
        fid_(fid),
        ftype_(ftype),
        success_(success) {}
  template <typename FieldData>
  void operator()(FieldData& fieldData, int index) {
    using Ops = Cpp2Ops<typename FieldData::ref_type>;

    if (ftype_ != Ops::thriftType()) {
      return;
    }

    int16_t myfid = FieldData::fid;
    auto& ex = fieldData.ref();
    if (myfid != fid_) {
      return;
    }

    success_ = true;
    isset_.setIsSet(index);
    Ops::read(prot_, &ex);
  }

 private:
  Protocol* prot_;
  IsSet& isset_;
  int16_t fid_;
  protocol::TType ftype_;
  bool& success_;
};

template <typename T>
T& maybe_remove_pointer(T& x) {
  return x;
}

template <typename T>
T& maybe_remove_pointer(T* x) {
  return *x;
}

template <bool hasIsSet, size_t count>
struct IsSetHelper {
  void setIsSet(size_t /*index*/, bool /*value*/ = true) {}
  bool getIsSet(size_t /*index*/) const {
    return true;
  }
};

template <size_t count>
struct IsSetHelper<true, count> {
  void setIsSet(size_t index, bool value = true) {
    isset_[index] = value;
  }
  bool getIsSet(size_t index) const {
    return isset_[index];
  }

 private:
  std::array<bool, count> isset_ = {};
};

} // namespace detail

template <int16_t Fid, protocol::TType Ttype, typename T>
struct FieldData {
  static const constexpr int16_t fid = Fid;
  static const constexpr protocol::TType ttype = Ttype;
  typedef T type;
  typedef typename std::remove_pointer<T>::type ref_type;
  T value;
  ref_type& ref() {
    return detail::maybe_remove_pointer(value);
  }
  const ref_type& ref() const {
    return detail::maybe_remove_pointer(value);
  }
};

template <bool hasIsSet, typename... Field>
class ThriftPresult : private std::tuple<Field...>,
                      public detail::IsSetHelper<hasIsSet, sizeof...(Field)> {
  // The fields tuple and IsSetHelper are base classes (rather than members)
  // to employ the empty base class optimization when they are empty
  typedef std::tuple<Field...> Fields;
  typedef detail::IsSetHelper<hasIsSet, sizeof...(Field)> CurIsSetHelper;

 public:
  using size = std::tuple_size<Fields>;

  CurIsSetHelper& isSet() {
    return *this;
  }
  const CurIsSetHelper& isSet() const {
    return *this;
  }
  Fields& fields() {
    return *this;
  }
  const Fields& fields() const {
    return *this;
  }

  // returns lvalue ref to the appropriate FieldData
  template <size_t index>
  auto get() -> decltype(std::get<index>(this->fields())) {
    return std::get<index>(this->fields());
  }

  template <size_t index>
  auto get() const -> decltype(std::get<index>(this->fields())) {
    return std::get<index>(this->fields());
  }

  template <class Protocol>
  uint32_t read(Protocol* prot) {
    auto xfer = prot->getCursorPosition();
    std::string fname;
    apache::thrift::protocol::TType ftype;
    int16_t fid;

    prot->readStructBegin(fname);

    while (true) {
      prot->readFieldBegin(fname, ftype, fid);
      if (ftype == apache::thrift::protocol::T_STOP) {
        break;
      }
      bool readSomething = false;
      detail::forEachVoid(
          fields(),
          detail::Reader<Protocol, CurIsSetHelper>(
              prot, isSet(), fid, ftype, readSomething));
      if (!readSomething) {
        prot->skip(ftype);
      }
      prot->readFieldEnd();
    }
    prot->readStructEnd();

    return prot->getCursorPosition() - xfer;
  }

  template <class Protocol>
  uint32_t serializedSize(Protocol* prot) const {
    uint32_t xfer = 0;
    xfer += prot->serializedStructSize("");
    xfer += detail::forEach(
        fields(), detail::Sizer<Protocol, CurIsSetHelper>(prot, isSet()));
    xfer += prot->serializedSizeStop();
    return xfer;
  }

  template <class Protocol>
  uint32_t serializedSizeZC(Protocol* prot) const {
    uint32_t xfer = 0;
    xfer += prot->serializedStructSize("");
    xfer += detail::forEach(
        fields(), detail::SizerZC<Protocol, CurIsSetHelper>(prot, isSet()));
    xfer += prot->serializedSizeStop();
    return xfer;
  }

  template <class Protocol>
  uint32_t write(Protocol* prot) const {
    uint32_t xfer = 0;
    xfer += prot->writeStructBegin("");
    xfer += detail::forEach(
        fields(), detail::Writer<Protocol, CurIsSetHelper>(prot, isSet()));
    xfer += prot->writeFieldStop();
    xfer += prot->writeStructEnd();
    return xfer;
  }
};

template <typename PResults, typename StreamPresult>
struct ThriftPResultStream {
  using StreamPResultType = StreamPresult;
  using FieldsType = PResults;

  PResults fields;
  StreamPresult stream;
};

template <bool hasIsSet, class... Args>
class Cpp2Ops<ThriftPresult<hasIsSet, Args...>> {
 public:
  typedef ThriftPresult<hasIsSet, Args...> Presult;
  static constexpr protocol::TType thriftType() {
    return protocol::T_STRUCT;
  }
  template <class Protocol>
  static uint32_t write(Protocol* prot, const Presult* value) {
    return value->write(prot);
  }
  template <class Protocol>
  static uint32_t read(Protocol* prot, Presult* value) {
    return value->read(prot);
  }
  template <class Protocol>
  static uint32_t serializedSize(Protocol* prot, const Presult* value) {
    return value->serializedSize(prot);
  }
  template <class Protocol>
  static uint32_t serializedSizeZC(Protocol* prot, const Presult* value) {
    return value->serializedSizeZC(prot);
  }
};

// Forward declaration
namespace detail {
namespace ap {

template <typename Protocol, typename PResult, typename T>
apache::thrift::SemiStream<T> decode_stream(
    apache::thrift::SemiStream<std::unique_ptr<folly::IOBuf>>&& stream);

} // namespace ap
} // namespace detail

//  AsyncClient helpers
namespace detail {
namespace ac {

template <typename IntegerSequence>
struct foreach_;

template <std::size_t... I>
struct foreach_<std::index_sequence<I...>> {
  template <typename F, typename... O>
  FOLLY_ALWAYS_INLINE FOLLY_ATTR_VISIBILITY_HIDDEN static void go(
      F&& f,
      O&&... o) {
    using _ = int[];
    void(_{
        (void(f(std::integral_constant<std::size_t, I>{}, std::forward<O>(o))),
         0)...,
        0});
  }
};

template <typename F, typename... O>
FOLLY_ALWAYS_INLINE FOLLY_ATTR_VISIBILITY_HIDDEN void foreach(F&& f, O&&... o) {
  using seq = std::make_index_sequence<sizeof...(O)>;
  foreach_<seq>::go(std::forward<F>(f), std::forward<O>(o)...);
}

template <typename F, std::size_t... I>
FOLLY_ALWAYS_INLINE FOLLY_ATTR_VISIBILITY_HIDDEN void foreach_index_(
    F&& f,
    std::index_sequence<I...>) {
  foreach_<std::index_sequence<I...>>::go(std::forward<F>(f), I...);
}

template <std::size_t Size, typename F>
FOLLY_ALWAYS_INLINE FOLLY_ATTR_VISIBILITY_HIDDEN void foreach_index(F&& f) {
  using seq = std::make_index_sequence<Size>;
  foreach_index_([&](auto _, auto) { f(_); }, seq{});
}

template <bool HasReturnType, typename PResult>
folly::exception_wrapper extract_exn(PResult& result) {
  using base = std::integral_constant<std::size_t, HasReturnType ? 1 : 0>;
  auto ew = folly::exception_wrapper();
  if (HasReturnType && result.getIsSet(0)) {
    return ew;
  }
  foreach_index<PResult::size::value - base::value>([&](auto index) {
    if (!ew && result.getIsSet(index.value + base::value)) {
      auto& fdata = result.template get<index.value + base::value>();
      ew = folly::exception_wrapper(std::move(fdata.ref()));
    }
  });
  if (!ew && HasReturnType) {
    ew = folly::make_exception_wrapper<TApplicationException>(
        TApplicationException::TApplicationExceptionType::MISSING_RESULT,
        "failed: unknown result");
  }
  return ew;
}

template <typename Protocol, typename PResult>
folly::exception_wrapper recv_wrapped_helper(
    const char* method,
    Protocol* prot,
    ClientReceiveState& state,
    PResult& result) {
  ContextStack* ctx = state.ctx();
  std::string fname;
  int32_t protoSeqId = 0;
  MessageType mtype;
  ctx->preRead();
  try {
    if (state.header() && state.header()->getCrc32c().has_value() &&
        checksum::crc32c(*state.buf()) != *state.header()->getCrc32c()) {
      return folly::make_exception_wrapper<TApplicationException>(
          TApplicationException::TApplicationExceptionType::CHECKSUM_MISMATCH,
          "corrupted response");
    }
    prot->readMessageBegin(fname, mtype, protoSeqId);
    if (mtype == T_EXCEPTION) {
      TApplicationException x;
      detail::deserializeExceptionBody(prot, &x);
      prot->readMessageEnd();
      return folly::exception_wrapper(std::move(x));
    }
    if (mtype != T_REPLY) {
      prot->skip(protocol::T_STRUCT);
      prot->readMessageEnd();
      return folly::make_exception_wrapper<TApplicationException>(
          TApplicationException::TApplicationExceptionType::
              INVALID_MESSAGE_TYPE);
    }
    if (fname.compare(method) != 0) {
      prot->skip(protocol::T_STRUCT);
      prot->readMessageEnd();
      return folly::make_exception_wrapper<TApplicationException>(
          TApplicationException::TApplicationExceptionType::WRONG_METHOD_NAME);
    }
    SerializedMessage smsg;
    smsg.protocolType = prot->protocolType();
    smsg.buffer = state.buf();
    ctx->onReadData(smsg);
    detail::deserializeRequestBody(prot, &result);
    prot->readMessageEnd();
    ctx->postRead(state.header(), state.buf()->length());
    return folly::exception_wrapper();
  } catch (std::exception const& e) {
    return folly::exception_wrapper(std::current_exception(), e);
  } catch (...) {
    return folly::exception_wrapper(std::current_exception());
  }
}

template <typename PResult, typename Protocol, typename... ReturnTs>
folly::exception_wrapper recv_wrapped(
    const char* method,
    Protocol* prot,
    ClientReceiveState& state,
    ReturnTs&... _returns) {
  prot->setInput(state.buf());
  auto guard = folly::makeGuard([&] { prot->setInput(nullptr); });
  apache::thrift::ContextStack* ctx = state.ctx();
  PResult result;
  foreach(
      [&](auto index, auto& obj) {
        result.template get<index.value>().value = &obj;
      },
      _returns...);
  auto ew = recv_wrapped_helper(method, prot, state, result);
  if (!ew) {
    constexpr auto const kHasReturnType = sizeof...(_returns) != 0;
    ew = apache::thrift::detail::ac::extract_exn<kHasReturnType>(result);
  }
  if (ew) {
    ctx->handlerErrorWrapped(ew);
  }
  return ew;
}

template <typename PResult, typename Protocol, typename Response, typename Item>
folly::exception_wrapper recv_wrapped(
    const char* method,
    Protocol* prot,
    ClientReceiveState& state,
    apache::thrift::ResponseAndSemiStream<Response, Item>& _return) {
  prot->setInput(state.buf());
  auto guard = folly::makeGuard([&] { prot->setInput(nullptr); });
  apache::thrift::ContextStack* ctx = state.ctx();

  typename PResult::FieldsType result;
  result.template get<0>().value = &_return.response;

  auto ew = recv_wrapped_helper(method, prot, state, result);
  if (!ew) {
    ew = apache::thrift::detail::ac::extract_exn<true>(result);
  }
  if (ew) {
    ctx->handlerErrorWrapped(ew);
  }

  if (!ew) {
    _return.stream = detail::ap::
        decode_stream<Protocol, typename PResult::StreamPResultType, Item>(
            state.extractStream());
  }
  return ew;
}

template <typename PResult, typename Protocol, typename Item>
folly::exception_wrapper recv_wrapped(
    const char* method,
    Protocol* prot,
    ClientReceiveState& state,
    apache::thrift::SemiStream<Item>& _return) {
  prot->setInput(state.buf());
  auto guard = folly::makeGuard([&] { prot->setInput(nullptr); });
  apache::thrift::ContextStack* ctx = state.ctx();

  typename PResult::FieldsType result;

  auto ew = recv_wrapped_helper(method, prot, state, result);
  if (!ew) {
    ew = apache::thrift::detail::ac::extract_exn<false>(result);
  }
  if (ew) {
    ctx->handlerErrorWrapped(ew);
  }

  if (!ew) {
    _return = detail::ap::
        decode_stream<Protocol, typename PResult::StreamPResultType, Item>(
            state.extractStream());
  }
  return ew;
}

[[noreturn]] void throw_app_exn(char const* msg);
} // namespace ac
} // namespace detail

//  AsyncProcessor helpers
namespace detail {
namespace ap {

//  Everything templated on only protocol goes here. The corresponding .cpp file
//  explicitly instantiates this struct for each supported protocol.
template <typename ProtocolReader, typename ProtocolWriter>
struct helper {
  static folly::IOBufQueue write_exn(
      const char* method,
      ProtocolWriter* prot,
      int32_t protoSeqId,
      ContextStack* ctx,
      const TApplicationException& x);

  static void process_exn(
      const char* func,
      const TApplicationException::TApplicationExceptionType type,
      const std::string& msg,
      std::unique_ptr<ResponseChannelRequest> req,
      Cpp2RequestContext* ctx,
      folly::EventBase* eb,
      int32_t protoSeqId);
};

template <typename ProtocolReader>
using writer_of = typename ProtocolReader::ProtocolWriter;
template <typename ProtocolWriter>
using reader_of = typename ProtocolWriter::ProtocolReader;

template <typename ProtocolReader>
using helper_r = helper<ProtocolReader, writer_of<ProtocolReader>>;
template <typename ProtocolWriter>
using helper_w = helper<reader_of<ProtocolWriter>, ProtocolWriter>;

template <typename T>
using is_root_async_processor = std::is_void<typename T::BaseAsyncProcessor>;

template <class ProtocolReader, class Processor>
typename std::enable_if<is_root_async_processor<Processor>::value>::type
process_missing(
    Processor*,
    const std::string& fname,
    std::unique_ptr<ResponseChannelRequest> req,
    std::unique_ptr<folly::IOBuf>,
    Cpp2RequestContext* ctx,
    folly::EventBase* eb,
    concurrency::ThreadManager*,
    int32_t protoSeqId) {
  using h = helper_r<ProtocolReader>;
  const char* fn = "process";
  auto type = TApplicationException::TApplicationExceptionType::UNKNOWN_METHOD;
  const auto msg = fmt::format("Method name {} not found", fname);
  return h::process_exn(fn, type, msg, std::move(req), ctx, eb, protoSeqId);
}

template <class ProtocolReader, class Processor>
typename std::enable_if<!is_root_async_processor<Processor>::value>::type
process_missing(
    Processor* processor,
    const std::string& /*fname*/,
    std::unique_ptr<ResponseChannelRequest> req,
    std::unique_ptr<folly::IOBuf> buf,
    Cpp2RequestContext* ctx,
    folly::EventBase* eb,
    concurrency::ThreadManager* tm,
    int32_t /*protoSeqId*/) {
  auto protType = ProtocolReader::protocolType();
  processor->Processor::BaseAsyncProcessor::process(
      std::move(req), std::move(buf), protType, ctx, eb, tm);
}

bool deserializeMessageBegin(
    protocol::PROTOCOL_TYPES protType,
    std::unique_ptr<ResponseChannelRequest>& req,
    folly::IOBuf* buf,
    Cpp2RequestContext* ctx,
    folly::EventBase* eb);

std::string deserializeMethodName(
    std::unique_ptr<ResponseChannelRequest>& req,
    protocol::PROTOCOL_TYPES protType);

template <class ProtocolReader, class Processor>
void process_pmap(
    Processor* proc,
    const typename GeneratedAsyncProcessor::ProcessMap<
        GeneratedAsyncProcessor::ProcessFunc<Processor>>& pmap,
    std::unique_ptr<ResponseChannelRequest> req,
    std::unique_ptr<folly::IOBuf> buf,
    Cpp2RequestContext* ctx,
    folly::EventBase* eb,
    concurrency::ThreadManager* tm) {
  const auto& fname = ctx->getMethodName();
  auto pfn = pmap.find(fname);
  if (pfn == pmap.end()) {
    process_missing<ProtocolReader>(
        proc,
        fname,
        std::move(req),
        std::move(buf),
        ctx,
        eb,
        tm,
        ctx->getProtoSeqId());
    return;
  }

  (proc->*(pfn->second))(std::move(req), std::move(buf), ctx, eb, tm);
}

//  Generated AsyncProcessor::process just calls this.
template <class Processor>
void process(
    Processor* processor,
    std::unique_ptr<ResponseChannelRequest> req,
    std::unique_ptr<folly::IOBuf> buf,
    protocol::PROTOCOL_TYPES protType,
    Cpp2RequestContext* ctx,
    folly::EventBase* eb,
    concurrency::ThreadManager* tm) {
  switch (protType) {
    case protocol::T_BINARY_PROTOCOL: {
      const auto& pmap = processor->getBinaryProtocolProcessMap();
      return process_pmap<BinaryProtocolReader>(
          processor, pmap, std::move(req), std::move(buf), ctx, eb, tm);
    }
    case protocol::T_COMPACT_PROTOCOL: {
      const auto& pmap = processor->getCompactProtocolProcessMap();
      return process_pmap<CompactProtocolReader>(
          processor, pmap, std::move(req), std::move(buf), ctx, eb, tm);
    }
    default:
      LOG(ERROR) << "invalid protType: " << protType;
      return;
  }
}

//  Generated AsyncProcessor::getCacheKey just calls this.
folly::Optional<std::string> get_cache_key(
    const folly::IOBuf* buf,
    const protocol::PROTOCOL_TYPES protType,
    const std::unordered_map<std::string, int16_t>& cache_key_map);

//  Generated AsyncProcessor::isOnewayMethod just calls this.
bool is_oneway_method(
    const folly::IOBuf* buf,
    const transport::THeader* header,
    const std::unordered_set<std::string>& oneways);

template <
    typename Protocol,
    typename PResult,
    typename T,
    typename ErrorMapFunc>
apache::thrift::Stream<folly::IOBufQueue> encode_stream(
    apache::thrift::Stream<T>&& stream,
    ErrorMapFunc exceptionMap) {
  if (!stream) {
    return {};
  }

  return std::move(stream).map(
      [](T&& _item) mutable {
        PResult res;
        res.template get<0>().value = const_cast<T*>(&_item);
        res.setIsSet(0);

        folly::IOBufQueue queue(folly::IOBufQueue::cacheChainLength());
        Protocol prot;
        prot.setOutput(&queue, kStreamingQueueAppenderGrowth);

        res.write(&prot);
        return queue;
      },
      [map = std::move(exceptionMap)](folly::exception_wrapper&& ew) mutable {
        Protocol prot;
        folly::IOBufQueue queue(folly::IOBufQueue::cacheChainLength());
        prot.setOutput(&queue, kStreamingQueueAppenderGrowth);
        PResult res;
        if (map(res, ew)) {
          res.write(&prot);
        } else {
          TApplicationException ex(ew.what().toStdString());
          detail::serializeExceptionBody(&prot, &ex);
        }

        auto result = queue.move();
        return apache::thrift::detail::EncodedError(std::move(result));
      });
}

template <typename Protocol, typename PResult, typename T>
apache::thrift::SemiStream<T> decode_stream(
    apache::thrift::SemiStream<std::unique_ptr<folly::IOBuf>>&& stream) {
  return std::move(stream).map(
      [](std::unique_ptr<folly::IOBuf>&& buf) mutable {
        PResult args;
        T res{};
        args.template get<0>().value = &res;

        Protocol prot;
        prot.setInput(buf.get());
        args.read(&prot);
        return res;
      },
      [](folly::exception_wrapper&& ew) {
        Protocol prot;
        folly::exception_wrapper hijacked;
        ew.with_exception(
            [&hijacked, &prot](apache::thrift::detail::EncodedError& err) {
              PResult result;
              T res{};
              result.template get<0>().value = &res;

              prot.setInput(err.encoded.get());
              result.read(&prot);

              CHECK(!result.getIsSet(0));

              ac::foreach_index<PResult::size::value - 1>([&](auto index) {
                if (!hijacked && result.getIsSet(index.value + 1)) {
                  auto& fdata = result.template get<index.value + 1>();
                  hijacked = folly::exception_wrapper(std::move(fdata.ref()));
                }
              });

              if (!hijacked) {
                // Could not decode the error. It may be a TApplicationException
                TApplicationException x;
                prot.setInput(err.encoded.get());
                deserializeExceptionBody(&prot, &x);
                hijacked = folly::exception_wrapper(std::move(x));
              }
            });

        if (hijacked) {
          return hijacked;
        }

        if (ew.is_compatible_with<transport::TTransportException>()) {
          return std::move(ew);
        }

        return folly::exception_wrapper(
            transport::TTransportException(ew.what().toStdString()));
      });
}

} // namespace ap
} // namespace detail

//  ServerInterface helpers
namespace detail {
namespace si {

template <typename F>
using ret = typename std::result_of<F()>::type;
template <typename F>
using ret_lift = typename folly::lift_unit<ret<F>>::type;
template <typename F>
using fut_ret = typename ret<F>::value_type;
template <typename F>
using fut_ret_drop = typename folly::drop_unit<fut_ret<F>>::type;
template <typename T>
struct action_traits_impl;
template <typename C, typename A>
struct action_traits_impl<void (C::*)(A&) const> {
  using arg_type = A;
};
template <typename C, typename A>
struct action_traits_impl<void (C::*)(A&)> {
  using arg_type = A;
};
template <typename F>
using action_traits = action_traits_impl<decltype(&F::operator())>;
template <typename F>
using arg = typename action_traits<F>::arg_type;

template <typename T>
folly::Future<T> future(
    folly::SemiFuture<T>&& future,
    folly::Executor* executor) {
  if (future.isReady()) {
    return std::move(future).toUnsafeFuture();
  }
  return std::move(future).via(executor);
}

template <class F>
folly::SemiFuture<ret_lift<F>> semifuture(F&& f) {
  return folly::makeSemiFutureWith(std::forward<F>(f));
}

template <class F>
arg<F> returning(F&& f) {
  arg<F> ret;
  f(ret);
  return ret;
}

template <class F>
folly::SemiFuture<arg<F>> semifuture_returning(F&& f) {
  return semifuture([&]() { return returning(std::forward<F>(f)); });
}

template <class F>
std::unique_ptr<arg<F>> returning_uptr(F&& f) {
  auto ret = std::make_unique<arg<F>>();
  f(*ret);
  return ret;
}

template <class F>
folly::SemiFuture<std::unique_ptr<arg<F>>> semifuture_returning_uptr(F&& f) {
  return semifuture([&]() { return returning_uptr(std::forward<F>(f)); });
}

using CallbackBase = HandlerCallbackBase;
using CallbackBasePtr = std::unique_ptr<CallbackBase>;
template <class R>
using Callback = HandlerCallback<fut_ret_drop<R>>;
template <class R>
using CallbackPtr = std::unique_ptr<Callback<R>>;

inline void async_tm_prep(ServerInterface* si, CallbackBase* callback) {
  si->setEventBase(callback->getEventBase());
  si->setThreadManager(callback->getThreadManager());
  si->setConnectionContext(callback->getConnectionContext());
}

template <class F>
void async_tm_oneway(ServerInterface* si, CallbackBasePtr callback, F&& f) {
  async_tm_prep(si, callback.get());
  folly::makeFutureWith(std::forward<F>(f))
      .thenValue([cb = std::move(callback)](auto&&) {});
}

template <class F>
void async_tm(ServerInterface* si, CallbackPtr<F> callback, F&& f) {
  async_tm_prep(si, callback.get());
  folly::makeFutureWith(std::forward<F>(f))
      .thenTry(
          [cb = std::move(callback)](folly::Try<fut_ret<F>>&& _ret) mutable {
            Callback<F>::completeInThread(std::move(cb), std::move(_ret));
          });
}

template <class F>
void async_eb_oneway(ServerInterface* si, CallbackBasePtr callback, F&& f) {
  auto callbackp = callback.get();
  callbackp->runFuncInQueue(
      [si, callback = std::move(callback), f = std::forward<F>(f)]() mutable {
        async_tm_oneway(si, std::move(callback), std::move(f));
      },
      true);
}

template <class F>
void async_eb(ServerInterface* si, CallbackPtr<F> callback, F&& f) {
  auto callbackp = callback.get();
  callbackp->runFuncInQueue(
      [si, callback = std::move(callback), f = std::forward<F>(f)]() mutable {
        async_tm(si, std::move(callback), std::move(f));
      });
}

[[noreturn]] void throw_app_exn_unimplemented(char const* name);
} // namespace si
} // namespace detail

} // namespace thrift
} // namespace apache
