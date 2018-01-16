/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "src/gen-cpp2/includes_types.h"

#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>

#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/protocol/SimpleJSONProtocol.h>

namespace a { namespace different { namespace ns {

}}} // a::different::ns
namespace std {

} // std
namespace apache { namespace thrift {

}} // apache::thrift
namespace a { namespace different { namespace ns {

template <class Protocol_>
void AStruct::readNoXfer(Protocol_* iprot) {
  std::string _fname;
  apache::thrift::protocol::TType _ftype;
  int16_t fid;

  iprot->readStructBegin(_fname);

  using apache::thrift::TProtocolException;


  while (true) {
    iprot->readFieldBegin(_fname, _ftype, fid);
    if (_ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    if (iprot->kUsesFieldNames()) {
      this->translateFieldName(_fname, fid, _ftype);
    }
    switch (fid) {
      case 1:
      {
        if (_ftype == apache::thrift::protocol::T_I32) {
          iprot->readI32(this->FieldA);
          this->__isset.FieldA = true;
        } else {
          iprot->skip(_ftype);
        }
        break;
      }
      default:
      {
        iprot->skip(_ftype);
        break;
      }
    }
    iprot->readFieldEnd();
  }
  iprot->readStructEnd();

}

template <class Protocol_>
uint32_t AStruct::serializedSize(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("AStruct");
  xfer += prot_->serializedFieldSize("FieldA", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->FieldA);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t AStruct::serializedSizeZC(Protocol_ const* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("AStruct");
  xfer += prot_->serializedFieldSize("FieldA", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->FieldA);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t AStruct::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("AStruct");
  xfer += prot_->writeFieldBegin("FieldA", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->writeI32(this->FieldA);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

}}} // a::different::ns
namespace a { namespace different { namespace ns {

template <class Protocol_>
void AStructB::readNoXfer(Protocol_* iprot) {
  std::string _fname;
  apache::thrift::protocol::TType _ftype;
  int16_t fid;

  iprot->readStructBegin(_fname);

  using apache::thrift::TProtocolException;


  while (true) {
    iprot->readFieldBegin(_fname, _ftype, fid);
    if (_ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    if (iprot->kUsesFieldNames()) {
      this->translateFieldName(_fname, fid, _ftype);
    }
    switch (fid) {
      case 1:
      {
        if (_ftype == apache::thrift::protocol::T_STRUCT) {
          std::unique_ptr< ::a::different::ns::AStruct> ptr = std::make_unique< ::a::different::ns::AStruct>();
          ::apache::thrift::Cpp2Ops<  ::a::different::ns::AStruct>::read(iprot, ptr.get());
          this->FieldA = std::move(ptr);
        } else {
          iprot->skip(_ftype);
        }
        break;
      }
      default:
      {
        iprot->skip(_ftype);
        break;
      }
    }
    iprot->readFieldEnd();
  }
  iprot->readStructEnd();

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

}}} // a::different::ns
