/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "thrift/compiler/test/fixtures/mcpp2-compare/gen-cpp2/includes_types.h"

#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>
#include <thrift/lib/cpp2/gen/module_types_tcc.h>

#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/protocol/ProtocolReaderStructReadState.h>
#include <thrift/lib/cpp2/protocol/SimpleJSONProtocol.h>

namespace a { namespace different { namespace ns {

}}} // a::different::ns
namespace std {

} // std
namespace apache { namespace thrift {

}} // apache::thrift

namespace apache {
namespace thrift {
namespace detail {

template <>
struct TccStructTraits<::a::different::ns::AStruct> {
  static void translateFieldName(
      folly::StringPiece _fname,
      int16_t& fid,
      apache::thrift::protocol::TType& _ftype);
};
template <>
struct TccStructTraits<::a::different::ns::AStructB> {
  static void translateFieldName(
      folly::StringPiece _fname,
      int16_t& fid,
      apache::thrift::protocol::TType& _ftype);
};

} // namespace detail
} // namespace thrift
} // namespace apache

namespace a { namespace different { namespace ns {

template <class Protocol_>
void AStruct::readNoXfer(Protocol_* iprot) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol_> _readState;

  _readState.readStructBegin(iprot);

  using apache::thrift::TProtocolException;


  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          0,
          1,
          apache::thrift::protocol::T_I32))) {
    goto _loop;
  }
_readField_FieldA:
  {
    ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int32_t>::read(*iprot, this->FieldA);
    this->__isset.FieldA = true;
  }

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          1,
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
    apache::thrift::detail::TccStructTraits<AStruct>::translateFieldName(_readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_I32))) {
        goto _readField_FieldA;
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
uint32_t AStruct::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("AStruct");
  xfer += prot_->serializedFieldSize("FieldA", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int32_t>::serializedSize<false>(*prot_, this->FieldA);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t AStruct::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("AStruct");
  xfer += prot_->serializedFieldSize("FieldA", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int32_t>::serializedSize<false>(*prot_, this->FieldA);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t AStruct::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("AStruct");
  xfer += prot_->writeFieldBegin("FieldA", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::integral, int32_t>::write(*prot_, this->FieldA);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

extern template void AStruct::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t AStruct::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t AStruct::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t AStruct::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void AStruct::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t AStruct::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t AStruct::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t AStruct::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;
extern template void AStruct::readNoXfer<>(apache::thrift::SimpleJSONProtocolReader*);
extern template uint32_t AStruct::write<>(apache::thrift::SimpleJSONProtocolWriter*) const;
extern template uint32_t AStruct::serializedSize<>(apache::thrift::SimpleJSONProtocolWriter const*) const;
extern template uint32_t AStruct::serializedSizeZC<>(apache::thrift::SimpleJSONProtocolWriter const*) const;

}}} // a::different::ns
namespace a { namespace different { namespace ns {

template <class Protocol_>
void AStructB::readNoXfer(Protocol_* iprot) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol_> _readState;

  _readState.readStructBegin(iprot);

  using apache::thrift::TProtocolException;


  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          0,
          1,
          apache::thrift::protocol::T_STRUCT))) {
    goto _loop;
  }
_readField_FieldA:
  {
    std::unique_ptr< ::a::different::ns::AStruct> ptr = std::make_unique< ::a::different::ns::AStruct>();
    ::apache::thrift::Cpp2Ops<  ::a::different::ns::AStruct>::read(iprot, ptr.get());
    this->FieldA = std::move(ptr);
  }

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          1,
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
    apache::thrift::detail::TccStructTraits<AStructB>::translateFieldName(_readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_STRUCT))) {
        goto _readField_FieldA;
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
uint32_t AStructB::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("AStructB");
  xfer += prot_->serializedFieldSize("FieldA", apache::thrift::protocol::T_STRUCT, 1);
  if (this->FieldA) {
    xfer += ::apache::thrift::Cpp2Ops<  ::a::different::ns::AStruct>::serializedSize(prot_, this->FieldA.get());
  }
  else {
    xfer += prot_->serializedStructSize("AStruct");
    xfer += prot_->serializedSizeStop();
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t AStructB::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("AStructB");
  xfer += prot_->serializedFieldSize("FieldA", apache::thrift::protocol::T_STRUCT, 1);
  if (this->FieldA) {
    xfer += ::apache::thrift::Cpp2Ops<  ::a::different::ns::AStruct>::serializedSizeZC(prot_, this->FieldA.get());
  }
  else {
    xfer += prot_->serializedStructSize("AStruct");
    xfer += prot_->serializedSizeStop();
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t AStructB::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("AStructB");
  xfer += prot_->writeFieldBegin("FieldA", apache::thrift::protocol::T_STRUCT, 1);
  if (this->FieldA) {
    xfer += ::apache::thrift::Cpp2Ops<  ::a::different::ns::AStruct>::write(prot_, this->FieldA.get());
  }
  else {
    xfer += prot_->writeStructBegin("AStruct");
    xfer += prot_->writeStructEnd();
    xfer += prot_->writeFieldStop();
  }
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

extern template void AStructB::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t AStructB::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t AStructB::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t AStructB::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void AStructB::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t AStructB::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t AStructB::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t AStructB::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;
extern template void AStructB::readNoXfer<>(apache::thrift::SimpleJSONProtocolReader*);
extern template uint32_t AStructB::write<>(apache::thrift::SimpleJSONProtocolWriter*) const;
extern template uint32_t AStructB::serializedSize<>(apache::thrift::SimpleJSONProtocolWriter const*) const;
extern template uint32_t AStructB::serializedSizeZC<>(apache::thrift::SimpleJSONProtocolWriter const*) const;

}}} // a::different::ns
