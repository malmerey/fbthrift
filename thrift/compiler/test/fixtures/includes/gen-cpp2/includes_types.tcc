/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "thrift/compiler/test/fixtures/includes/gen-cpp2/includes_types.h"

#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>
#include <thrift/lib/cpp2/gen/module_types_tcc.h>

#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/protocol/ProtocolReaderStructReadState.h>


namespace apache {
namespace thrift {
namespace detail {

template <>
struct TccStructTraits<::cpp2::Included> {
  static void translateFieldName(
      folly::StringPiece _fname,
      int16_t& fid,
      apache::thrift::protocol::TType& _ftype);
};

} // namespace detail
} // namespace thrift
} // namespace apache

namespace cpp2 {

template <class Protocol_>
void Included::readNoXfer(Protocol_* iprot) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol_> _readState;

  _readState.readStructBegin(iprot);

  using apache::thrift::TProtocolException;


  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          0,
          1,
          apache::thrift::protocol::T_I64))) {
    goto _loop;
  }
_readField_MyIntField:
  {
    ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int64_t>::read(*iprot, this->MyIntField);
    this->__isset.MyIntField = true;
  }

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          1,
          2,
          apache::thrift::protocol::T_STRUCT))) {
    goto _loop;
  }
_readField_MyTransitiveField:
  {
    ::apache::thrift::Cpp2Ops<  ::cpp2::Foo>::read(iprot, &this->MyTransitiveField);
    this->__isset.MyTransitiveField = true;
  }

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          2,
          0,
          apache::thrift::protocol::T_STOP))) {
    goto _loop;
  }

_end:
  _readState.readStructEnd(iprot);

  return;

_loop:
  if (_readState.fieldType == apache::thrift::protocol::T_STOP) {
    goto _end;
  }
  if (iprot->kUsesFieldNames()) {
    apache::thrift::detail::TccStructTraits<Included>::translateFieldName(_readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_I64))) {
        goto _readField_MyIntField;
      } else {
        goto _skip;
      }
    }
    case 2:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_STRUCT))) {
        goto _readField_MyTransitiveField;
      } else {
        goto _skip;
      }
    }
    default:
    {
_skip:
      _readState.skip(iprot);
      _readState.readFieldEnd(iprot);
      _readState.readFieldBeginNoInline(iprot);
      goto _loop;
    }
  }
}

template <class Protocol_>
uint32_t Included::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Included");
  xfer += prot_->serializedFieldSize("MyIntField", apache::thrift::protocol::T_I64, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int64_t>::serializedSize<false>(*prot_, this->MyIntField);
  xfer += prot_->serializedFieldSize("MyTransitiveField", apache::thrift::protocol::T_STRUCT, 2);
  xfer += ::apache::thrift::Cpp2Ops<  ::cpp2::Foo>::serializedSize(prot_, &this->MyTransitiveField);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Included::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Included");
  xfer += prot_->serializedFieldSize("MyIntField", apache::thrift::protocol::T_I64, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int64_t>::serializedSize<false>(*prot_, this->MyIntField);
  xfer += prot_->serializedFieldSize("MyTransitiveField", apache::thrift::protocol::T_STRUCT, 2);
  xfer += ::apache::thrift::Cpp2Ops<  ::cpp2::Foo>::serializedSizeZC(prot_, &this->MyTransitiveField);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Included::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("Included");
  xfer += prot_->writeFieldBegin("MyIntField", apache::thrift::protocol::T_I64, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int64_t>::write(*prot_, this->MyIntField);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("MyTransitiveField", apache::thrift::protocol::T_STRUCT, 2);
  xfer += ::apache::thrift::Cpp2Ops<  ::cpp2::Foo>::write(prot_, &this->MyTransitiveField);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

extern template void Included::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t Included::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t Included::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t Included::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void Included::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t Included::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t Included::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t Included::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

} // cpp2
