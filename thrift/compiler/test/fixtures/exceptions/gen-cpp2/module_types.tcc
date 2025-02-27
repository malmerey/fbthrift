/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "thrift/compiler/test/fixtures/exceptions/gen-cpp2/module_types.h"

#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>
#include <thrift/lib/cpp2/gen/module_types_tcc.h>

#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/protocol/ProtocolReaderStructReadState.h>


namespace apache {
namespace thrift {
namespace detail {

template <>
struct TccStructTraits<::cpp2::Banal> {
  static void translateFieldName(
      folly::StringPiece _fname,
      int16_t& fid,
      apache::thrift::protocol::TType& _ftype);
};
template <>
struct TccStructTraits<::cpp2::Fiery> {
  static void translateFieldName(
      folly::StringPiece _fname,
      int16_t& fid,
      apache::thrift::protocol::TType& _ftype);
};
template <>
struct TccStructTraits<::cpp2::Serious> {
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
void Banal::readNoXfer(Protocol_* iprot) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol_> _readState;

  _readState.readStructBegin(iprot);

  using apache::thrift::TProtocolException;


  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          0,
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
    apache::thrift::detail::TccStructTraits<Banal>::translateFieldName(_readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    default:
    {
      _readState.skip(iprot);
      _readState.readFieldEnd(iprot);
      _readState.readFieldBeginNoInline(iprot);
      goto _loop;
    }
  }
}

template <class Protocol_>
uint32_t Banal::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Banal");
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Banal::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Banal");
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Banal::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("Banal");
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

extern template void Banal::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t Banal::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t Banal::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t Banal::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void Banal::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t Banal::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t Banal::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t Banal::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

} // cpp2
namespace cpp2 {

template <class Protocol_>
void Fiery::readNoXfer(Protocol_* iprot) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol_> _readState;

  _readState.readStructBegin(iprot);

  using apache::thrift::TProtocolException;


  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          0,
          1,
          apache::thrift::protocol::T_STRING))) {
    goto _loop;
  }
_readField_message:
  {
    iprot->readString(this->message);
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
    apache::thrift::detail::TccStructTraits<Fiery>::translateFieldName(_readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_STRING))) {
        goto _readField_message;
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
uint32_t Fiery::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Fiery");
  xfer += prot_->serializedFieldSize("message", apache::thrift::protocol::T_STRING, 1);
  xfer += prot_->serializedSizeString(this->message);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Fiery::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Fiery");
  xfer += prot_->serializedFieldSize("message", apache::thrift::protocol::T_STRING, 1);
  xfer += prot_->serializedSizeString(this->message);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Fiery::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("Fiery");
  xfer += prot_->writeFieldBegin("message", apache::thrift::protocol::T_STRING, 1);
  xfer += prot_->writeString(this->message);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

extern template void Fiery::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t Fiery::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t Fiery::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t Fiery::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void Fiery::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t Fiery::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t Fiery::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t Fiery::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

} // cpp2
namespace cpp2 {

template <class Protocol_>
void Serious::readNoXfer(Protocol_* iprot) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol_> _readState;

  _readState.readStructBegin(iprot);

  using apache::thrift::TProtocolException;


  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          0,
          1,
          apache::thrift::protocol::T_STRING))) {
    goto _loop;
  }
_readField_sonnet:
  {
    iprot->readString(this->sonnet);
    this->__isset.sonnet = true;
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
    apache::thrift::detail::TccStructTraits<Serious>::translateFieldName(_readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_STRING))) {
        goto _readField_sonnet;
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
uint32_t Serious::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Serious");
  if (this->__isset.sonnet) {
    xfer += prot_->serializedFieldSize("sonnet", apache::thrift::protocol::T_STRING, 1);
    xfer += prot_->serializedSizeString(this->sonnet);
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Serious::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Serious");
  if (this->__isset.sonnet) {
    xfer += prot_->serializedFieldSize("sonnet", apache::thrift::protocol::T_STRING, 1);
    xfer += prot_->serializedSizeString(this->sonnet);
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Serious::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("Serious");
  if (this->__isset.sonnet) {
    xfer += prot_->writeFieldBegin("sonnet", apache::thrift::protocol::T_STRING, 1);
    xfer += prot_->writeString(this->sonnet);
    xfer += prot_->writeFieldEnd();
  }
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

extern template void Serious::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t Serious::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t Serious::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t Serious::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void Serious::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t Serious::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t Serious::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t Serious::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

} // cpp2
