/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "thrift/compiler/test/fixtures/basic-enum/gen-cpp2/module_types.h"

#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>
#include <thrift/lib/cpp2/gen/module_types_tcc.h>

#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/protocol/ProtocolReaderStructReadState.h>

namespace test { namespace fixtures { namespace enumstrict {

}}} // test::fixtures::enumstrict
namespace std {

} // std
namespace apache { namespace thrift {

}} // apache::thrift
namespace test { namespace fixtures { namespace enumstrict {

}}} // test::fixtures::enumstrict
namespace std {

} // std
namespace apache { namespace thrift {

}} // apache::thrift
namespace test { namespace fixtures { namespace enumstrict {

}}} // test::fixtures::enumstrict
namespace std {

} // std
namespace apache { namespace thrift {

}} // apache::thrift

namespace apache {
namespace thrift {
namespace detail {

template <>
struct TccStructTraits<::test::fixtures::enumstrict::MyStruct> {
  static void translateFieldName(
      folly::StringPiece _fname,
      int16_t& fid,
      apache::thrift::protocol::TType& _ftype);
};

} // namespace detail
} // namespace thrift
} // namespace apache

namespace test { namespace fixtures { namespace enumstrict {

template <class Protocol_>
void MyStruct::readNoXfer(Protocol_* iprot) {
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
_readField_myEnum:
  {
    ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyEnum>::read(*iprot, this->myEnum);
    this->__isset.myEnum = true;
  }

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          1,
          2,
          apache::thrift::protocol::T_I32))) {
    goto _loop;
  }
_readField_myBigEnum:
  {
    ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyBigEnum>::read(*iprot, this->myBigEnum);
    this->__isset.myBigEnum = true;
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
    apache::thrift::detail::TccStructTraits<MyStruct>::translateFieldName(_readState.fieldName(), _readState.fieldId, _readState.fieldType);
  }

  switch (_readState.fieldId) {
    case 1:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_I32))) {
        goto _readField_myEnum;
      } else {
        goto _skip;
      }
    }
    case 2:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_I32))) {
        goto _readField_myBigEnum;
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
uint32_t MyStruct::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("MyStruct");
  xfer += prot_->serializedFieldSize("myEnum", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyEnum>::serializedSize<false>(*prot_, this->myEnum);
  xfer += prot_->serializedFieldSize("myBigEnum", apache::thrift::protocol::T_I32, 2);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyBigEnum>::serializedSize<false>(*prot_, this->myBigEnum);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t MyStruct::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("MyStruct");
  xfer += prot_->serializedFieldSize("myEnum", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyEnum>::serializedSize<false>(*prot_, this->myEnum);
  xfer += prot_->serializedFieldSize("myBigEnum", apache::thrift::protocol::T_I32, 2);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyBigEnum>::serializedSize<false>(*prot_, this->myBigEnum);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t MyStruct::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("MyStruct");
  xfer += prot_->writeFieldBegin("myEnum", apache::thrift::protocol::T_I32, 1);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyEnum>::write(*prot_, this->myEnum);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("myBigEnum", apache::thrift::protocol::T_I32, 2);
  xfer += ::apache::thrift::detail::pm::protocol_methods< ::apache::thrift::type_class::enumeration,  ::test::fixtures::enumstrict::MyBigEnum>::write(*prot_, this->myBigEnum);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

extern template void MyStruct::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t MyStruct::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t MyStruct::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t MyStruct::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void MyStruct::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t MyStruct::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t MyStruct::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t MyStruct::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

}}} // test::fixtures::enumstrict
