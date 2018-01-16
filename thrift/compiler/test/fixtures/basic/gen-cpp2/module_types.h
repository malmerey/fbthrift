/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/Thrift.h>
#include <thrift/lib/cpp2/protocol/Protocol.h>
#include <thrift/lib/cpp/TApplicationException.h>
#include <folly/io/IOBuf.h>
#include <folly/io/Cursor.h>

#include <thrift/lib/cpp2/GeneratedHeaderHelper.h>



namespace cpp2 {

class MyStruct;
class MyDataItem;

enum class MyEnum {
  MyValue1 = 0,
  MyValue2 = 1
};

using _MyEnum_EnumMapFactory = apache::thrift::detail::TEnumMapFactory<MyEnum, MyEnum>;
extern const _MyEnum_EnumMapFactory::ValuesToNamesMapType _MyEnum_VALUES_TO_NAMES;
extern const _MyEnum_EnumMapFactory::NamesToValuesMapType _MyEnum_NAMES_TO_VALUES;

} // cpp2
namespace std {

template<> struct hash<typename  ::cpp2::MyEnum> : public apache::thrift::detail::enum_hash<typename  ::cpp2::MyEnum> {};
template<> struct equal_to<typename  ::cpp2::MyEnum> : public apache::thrift::detail::enum_equal_to<typename  ::cpp2::MyEnum> {};

} // std
namespace apache { namespace thrift {

template <> struct TEnumDataStorage< ::cpp2::MyEnum>;
template <> const std::size_t TEnumTraits< ::cpp2::MyEnum>::size;
template <> const folly::Range<const  ::cpp2::MyEnum*> TEnumTraits< ::cpp2::MyEnum>::values;
template <> const folly::Range<const folly::StringPiece*> TEnumTraits< ::cpp2::MyEnum>::names;
template <> const char* TEnumTraits< ::cpp2::MyEnum>::findName( ::cpp2::MyEnum value);
template <> bool TEnumTraits< ::cpp2::MyEnum>::findValue(const char* name,  ::cpp2::MyEnum* outValue);

template <> inline constexpr  ::cpp2::MyEnum TEnumTraits< ::cpp2::MyEnum>::min() {
  return  ::cpp2::MyEnum::MyValue1;
}

template <> inline constexpr  ::cpp2::MyEnum TEnumTraits< ::cpp2::MyEnum>::max() {
  return  ::cpp2::MyEnum::MyValue2;
}

}} // apache::thrift
namespace cpp2 {

class MyStruct final : private apache::thrift::detail::st::ComparisonOperators<MyStruct> {
 public:

  MyStruct() :
      MyIntField(0) {}
  // FragileConstructor for use in initialization lists only
  MyStruct(apache::thrift::FragileConstructor, int64_t MyIntField__arg, std::string MyStringField__arg,  ::cpp2::MyDataItem MyDataField__arg);
  template <typename T__ThriftWrappedArgument__Ctor, typename... Args__ThriftWrappedArgument__Ctor>
  MyStruct(::apache::thrift::detail::argument_wrapper<1, T__ThriftWrappedArgument__Ctor> arg, Args__ThriftWrappedArgument__Ctor&&... args):
    MyStruct(std::forward<Args__ThriftWrappedArgument__Ctor>(args)...)
  {
    MyIntField = arg.move();
    __isset.MyIntField = true;
  }
  template <typename T__ThriftWrappedArgument__Ctor, typename... Args__ThriftWrappedArgument__Ctor>
  MyStruct(::apache::thrift::detail::argument_wrapper<2, T__ThriftWrappedArgument__Ctor> arg, Args__ThriftWrappedArgument__Ctor&&... args):
    MyStruct(std::forward<Args__ThriftWrappedArgument__Ctor>(args)...)
  {
    MyStringField = arg.move();
    __isset.MyStringField = true;
  }
  template <typename T__ThriftWrappedArgument__Ctor, typename... Args__ThriftWrappedArgument__Ctor>
  MyStruct(::apache::thrift::detail::argument_wrapper<3, T__ThriftWrappedArgument__Ctor> arg, Args__ThriftWrappedArgument__Ctor&&... args):
    MyStruct(std::forward<Args__ThriftWrappedArgument__Ctor>(args)...)
  {
    MyDataField = arg.move();
    __isset.MyDataField = true;
  }

  MyStruct(MyStruct&&) = default;

  MyStruct(const MyStruct&) = default;

  MyStruct& operator=(MyStruct&&) = default;

  MyStruct& operator=(const MyStruct&) = default;
  void __clear();
  int64_t MyIntField;
  std::string MyStringField;
   ::cpp2::MyDataItem MyDataField;

  struct __isset {

    bool MyIntField;
    bool MyStringField;
    bool MyDataField;
  } __isset = {};
  bool operator==(const MyStruct& rhs) const;
  bool operator < (const MyStruct& rhs) const;

  int64_t get_MyIntField() const {
    return MyIntField;
  }

  int64_t& set_MyIntField(int64_t MyIntField_) {
    MyIntField = MyIntField_;
    __isset.MyIntField = true;
    return MyIntField;
  }

  const std::string& get_MyStringField() const& {
    return MyStringField;
  }

  std::string get_MyStringField() && {
    return std::move(MyStringField);
  }

  template <typename T_MyStruct_MyStringField_struct_setter>
  std::string& set_MyStringField(T_MyStruct_MyStringField_struct_setter&& MyStringField_) {
    MyStringField = std::forward<T_MyStruct_MyStringField_struct_setter>(MyStringField_);
    __isset.MyStringField = true;
    return MyStringField;
  }
  const  ::cpp2::MyDataItem& get_MyDataField() const&;
   ::cpp2::MyDataItem get_MyDataField() &&;

  template <typename T_MyStruct_MyDataField_struct_setter>
   ::cpp2::MyDataItem& set_MyDataField(T_MyStruct_MyDataField_struct_setter&& MyDataField_) {
    MyDataField = std::forward<T_MyStruct_MyDataField_struct_setter>(MyDataField_);
    __isset.MyDataField = true;
    return MyDataField;
  }

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t serializedSize(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t serializedSizeZC(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t write(Protocol_* prot_) const;

 private:
  static void translateFieldName(FOLLY_MAYBE_UNUSED folly::StringPiece _fname, FOLLY_MAYBE_UNUSED int16_t& fid, FOLLY_MAYBE_UNUSED apache::thrift::protocol::TType& _ftype);
};

void swap(MyStruct& a, MyStruct& b);
extern template uint32_t MyStruct::read<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t MyStruct::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t MyStruct::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t MyStruct::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t MyStruct::read<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t MyStruct::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t MyStruct::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t MyStruct::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

} // cpp2
namespace apache { namespace thrift {

template <> inline void Cpp2Ops< ::cpp2::MyStruct>::clear( ::cpp2::MyStruct* obj) {
  return obj->__clear();
}

template <> inline constexpr apache::thrift::protocol::TType Cpp2Ops< ::cpp2::MyStruct>::thriftType() {
  return apache::thrift::protocol::T_STRUCT;
}

template <> template <class Protocol> uint32_t Cpp2Ops< ::cpp2::MyStruct>::write(Protocol* proto,  ::cpp2::MyStruct const* obj) {
  return obj->write(proto);
}

template <> template <class Protocol> void Cpp2Ops< ::cpp2::MyStruct>::read(Protocol* proto,  ::cpp2::MyStruct* obj) {
  obj->read(proto);
}

template <> template <class Protocol> uint32_t Cpp2Ops< ::cpp2::MyStruct>::serializedSize(Protocol const* proto,  ::cpp2::MyStruct const* obj) {
  return obj->serializedSize(proto);
}

template <> template <class Protocol> uint32_t Cpp2Ops< ::cpp2::MyStruct>::serializedSizeZC(Protocol const* proto,  ::cpp2::MyStruct const* obj) {
  return obj->serializedSizeZC(proto);
}

}} // apache::thrift
namespace cpp2 {

class MyDataItem final : private apache::thrift::detail::st::ComparisonOperators<MyDataItem> {
 public:

  MyDataItem() {}
  // FragileConstructor for use in initialization lists only
  MyDataItem(apache::thrift::FragileConstructor);

  MyDataItem(MyDataItem&&) = default;

  MyDataItem(const MyDataItem&) = default;

  MyDataItem& operator=(MyDataItem&&) = default;

  MyDataItem& operator=(const MyDataItem&) = default;
  void __clear();
  bool operator==(const MyDataItem& /* rhs */) const;

  bool operator < (const MyDataItem& rhs) const {
    (void)rhs;
    return false;
  }

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t serializedSize(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t serializedSizeZC(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t write(Protocol_* prot_) const;

 private:
  static void translateFieldName(FOLLY_MAYBE_UNUSED folly::StringPiece _fname, FOLLY_MAYBE_UNUSED int16_t& fid, FOLLY_MAYBE_UNUSED apache::thrift::protocol::TType& _ftype);
};

void swap(MyDataItem& a, MyDataItem& b);
extern template uint32_t MyDataItem::read<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t MyDataItem::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t MyDataItem::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t MyDataItem::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t MyDataItem::read<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t MyDataItem::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t MyDataItem::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t MyDataItem::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

} // cpp2
namespace apache { namespace thrift {

template <> inline void Cpp2Ops< ::cpp2::MyDataItem>::clear( ::cpp2::MyDataItem* obj) {
  return obj->__clear();
}

template <> inline constexpr apache::thrift::protocol::TType Cpp2Ops< ::cpp2::MyDataItem>::thriftType() {
  return apache::thrift::protocol::T_STRUCT;
}

template <> template <class Protocol> uint32_t Cpp2Ops< ::cpp2::MyDataItem>::write(Protocol* proto,  ::cpp2::MyDataItem const* obj) {
  return obj->write(proto);
}

template <> template <class Protocol> void Cpp2Ops< ::cpp2::MyDataItem>::read(Protocol* proto,  ::cpp2::MyDataItem* obj) {
  obj->read(proto);
}

template <> template <class Protocol> uint32_t Cpp2Ops< ::cpp2::MyDataItem>::serializedSize(Protocol const* proto,  ::cpp2::MyDataItem const* obj) {
  return obj->serializedSize(proto);
}

template <> template <class Protocol> uint32_t Cpp2Ops< ::cpp2::MyDataItem>::serializedSizeZC(Protocol const* proto,  ::cpp2::MyDataItem const* obj) {
  return obj->serializedSizeZC(proto);
}

}} // apache::thrift
namespace cpp2 {

} // cpp2
