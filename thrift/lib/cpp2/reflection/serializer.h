/*
 * Copyright 2016-present Facebook, Inc.
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

#include <bitset>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

#include <fatal/type/call_traits.h>
#include <fatal/type/trie.h>
#include <folly/Traits.h>
#include <folly/Utility.h>
#include <thrift/lib/cpp2/GeneratedSerializationCodeHelper.h>
#include <thrift/lib/cpp2/reflection/container_traits.h>
#include <thrift/lib/cpp2/reflection/reflection.h>

namespace apache {
namespace thrift {

namespace detail {

inline bool is_unknown_container_size(uint32_t const size) {
  return size == std::numeric_limits<decltype(size)>::max();
}

} // namespace detail

/**
 * Specializations of `protocol_methods` encapsulate a collection of
 * read/write/size/sizeZC methods that can be performed on Thrift
 * objects and primitives. TypeClass (see apache::thrift::type_class)
 * refers to the general type of data that Type is, and is passed around for
 * two reasons:
 *  - to provide support for generic containers which have a common interface
 *    for building collections (e.g. a `std::vector<int>` and `std::deque<int>`,
 *    which can back a Thrift list, and thus have
 *    `type_class::list<type_class::integral>`, or an
 *    `std::map<std::string, MyStruct>` would have
 *    `type_class::map<type_class::string, type_class::structure>``).
 *  - to differentiate between Thrift types that are represented with the
 *    same C++ type, e.g. both Thrift binaries and strings are represented
 *    with an `std::string`, TypeClass is used to decide which protocol
 *    method to call.
 *
 * Example:
 *
 * // MyModule.thrift:
 * struct MyStruct {
 *   1: i32 fieldA
 *   2: string fieldB
 *   3: binary fieldC
 * }
 *
 * // C++
 *
 * using methods = protocol_methods<type_class::structure, MyStruct>;
 *
 * MyStruct struct_instance;
 * CompactProtocolReader reader;
 * methods::read(struct_instance, reader);
 *
 * @author: Dylan Knutson <dymk@fb.com>
 */
template <typename TypeClass, typename Type, typename Enable = void>
struct protocol_methods;

#define THRIFT_PROTOCOL_METHODS_INHERIT(Class, Type)                         \
  template <>                                                                \
  struct protocol_methods<type_class::Class, Type>                           \
      : detail::pm::protocol_methods<type_class::Class, Type> {              \
    using base = detail::pm::protocol_methods<type_class::Class, Type>;      \
    template <bool ZeroCopy, typename Protocol>                              \
    static std::size_t serialized_size(Protocol& protocol, Type const& in) { \
      return base::template serializedSize<ZeroCopy>(protocol, in);          \
    }                                                                        \
  }

THRIFT_PROTOCOL_METHODS_INHERIT(integral, std::int8_t);
THRIFT_PROTOCOL_METHODS_INHERIT(integral, std::int16_t);
THRIFT_PROTOCOL_METHODS_INHERIT(integral, std::int32_t);
THRIFT_PROTOCOL_METHODS_INHERIT(integral, std::int64_t);
THRIFT_PROTOCOL_METHODS_INHERIT(integral, bool);
THRIFT_PROTOCOL_METHODS_INHERIT(floating_point, double);
THRIFT_PROTOCOL_METHODS_INHERIT(floating_point, float);
THRIFT_PROTOCOL_METHODS_INHERIT(string, std::string);
THRIFT_PROTOCOL_METHODS_INHERIT(string, folly::fbstring);
THRIFT_PROTOCOL_METHODS_INHERIT(binary, std::string);
THRIFT_PROTOCOL_METHODS_INHERIT(binary, folly::fbstring);
THRIFT_PROTOCOL_METHODS_INHERIT(binary, folly::IOBuf);
THRIFT_PROTOCOL_METHODS_INHERIT(binary, std::unique_ptr<folly::IOBuf>);

#undef THRIFT_PROTOCOL_METHODS_INHERIT

namespace detail {

// is_smart_pointer is a helper for determining if a type is a supported
// pointer type for cpp2.ref fields, while discrimiminating against the
// pointer corner case in Thrift (e.g., a unqiue_pointer<folly::IOBuf>)
template <typename>
struct is_smart_pointer : std::false_type {};
template <typename D>
struct is_smart_pointer<std::unique_ptr<folly::IOBuf, D>> : std::false_type {};

// supported smart pointer types for cpp2.ref_type fields
template <typename T, typename D>
struct is_smart_pointer<std::unique_ptr<T, D>> : std::true_type {};
template <typename T>
struct is_smart_pointer<std::shared_ptr<T>> : std::true_type {};

template <typename T>
using enable_if_smart_pointer =
    typename std::enable_if<is_smart_pointer<T>::value>::type;

template <typename T>
using disable_if_smart_pointer =
    typename std::enable_if<!is_smart_pointer<T>::value>::type;

// enums, unions, and structs from IDLs without fatal metadata might
// be included in e,u,s from IDLs with fatal metadata. If those fields
// don't have fatal metadata, we fall back to using their legacy generated
// read/write/serializedSize(ZC) methods.
template <typename Type, protocol::TType TTypeValue>
struct legacy_fallback_methods {
  constexpr static protocol::TType ttype_value = TTypeValue;

  template <typename Protocol>
  static void read(Protocol& protocol, Type& out) {
    Cpp2Ops<Type>::read(&protocol, &out);
  }
  template <typename Protocol>
  static std::size_t write(Protocol& protocol, Type const& in) {
    return Cpp2Ops<Type>::write(&protocol, &in);
  }
  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, Type const& in) {
    if (ZeroCopy) {
      return Cpp2Ops<Type>::serializedSizeZC(&protocol, &in);
    } else {
      return Cpp2Ops<Type>::serializedSize(&protocol, &in);
    }
  }
};

} /* namespace detail */

// handle dereferencing smart pointers
template <typename TypeClass, typename PtrType>
struct protocol_methods<
    TypeClass,
    PtrType,
    typename detail::enable_if_smart_pointer<PtrType>> {
  using value_type = typename PtrType::element_type;
  using type_methods = protocol_methods<TypeClass, value_type>;

  constexpr static protocol::TType ttype_value = type_methods::ttype_value;

  template <typename Protocol>
  static void read(Protocol& protocol, PtrType& out) {
    type_methods::read(protocol, *out);
  }

  template <typename Protocol>
  static std::size_t write(Protocol& protocol, PtrType const& in) {
    return type_methods::write(protocol, *in);
  }

  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, PtrType const& in) {
    return type_methods::template serialized_size<ZeroCopy>(protocol, *in);
  }
};

// Enumerations
template <typename Type>
struct protocol_methods<type_class::enumeration, Type>
    : detail::pm::protocol_methods<type_class::enumeration, Type> {
  using base = detail::pm::protocol_methods<type_class::enumeration, Type>;
  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, Type const& in) {
    return base::template serializedSize<ZeroCopy>(protocol, in);
  }
};

// Lists
template <typename ElemClass, typename Type>
struct protocol_methods<type_class::list<ElemClass>, Type> {
  constexpr static protocol::TType ttype_value = protocol::T_LIST;

  using elem_type = typename Type::value_type;

  static_assert(
      !std::is_same<ElemClass, type_class::unknown>(),
      "Unable to serialize unknown list element");

  using elem_methods = protocol_methods<ElemClass, elem_type>;

  template <typename Protocol>
  static void read(Protocol& protocol, Type& out) {
    std::uint32_t list_size = -1;
    protocol::TType reported_type = protocol::T_STOP;

    out = Type();

    protocol.readListBegin(reported_type, list_size);

    Type list;
    if (detail::is_unknown_container_size(list_size)) {
      // list size unknown, SimpleJSON protocol won't know type, either
      // so let's just hope that it spits out something that makes sense
      // (if it did set reported_type to something known)
      if (reported_type != protocol::T_STOP) {
        assert(reported_type == elem_methods::ttype_value);
      }

      for (decltype(list_size) i = 0; protocol.peekList(); i++) {
        // TODO: this should grow better (e.g., 1.5x each time)
        // For now, we just bump the container size by 1 each time
        // because that's what the currently generated Thrift code does.
        out.resize(i + 1);
        elem_methods::read(protocol, out[i]);
      }
    } else {
      assert(reported_type == elem_methods::ttype_value);
      out.resize(list_size);
      for (decltype(list_size) i = 0; i < list_size; i++) {
        elem_methods::read(protocol, out[i]);
      }
    }

    protocol.readListEnd();
  }

  template <typename Protocol>
  static std::size_t write(Protocol& protocol, Type const& out) {
    std::size_t xfer = 0;
    xfer += protocol.writeListBegin(elem_methods::ttype_value, out.size());

    for (auto const& elem : out) {
      xfer += elem_methods::write(protocol, elem);
    }

    xfer += protocol.writeListEnd();
    return xfer;
  }

  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, Type const& out) {
    std::size_t xfer = 0;
    xfer +=
        protocol.serializedSizeListBegin(elem_methods::ttype_value, out.size());

    for (auto const& elem : out) {
      xfer += elem_methods::template serialized_size<ZeroCopy>(protocol, elem);
    }

    xfer += protocol.serializedSizeListEnd();
    return xfer;
  }
};

// Sets
template <typename ElemClass, typename Type>
struct protocol_methods<type_class::set<ElemClass>, Type> {
  constexpr static protocol::TType ttype_value = protocol::T_SET;

  // TODO: fair amount of shared code bewteen this and specialization for
  // type_class::list
  using elem_type = typename Type::value_type;

  static_assert(
      !std::is_same<ElemClass, type_class::unknown>(),
      "Unable to serialize unknown type");
  using elem_methods = protocol_methods<ElemClass, elem_type>;

 private:
  template <typename Protocol>
  static void consume_elem(Protocol& protocol, Type& out) {
    elem_type tmp;
    elem_methods::read(protocol, tmp);
    out.insert(std::move(tmp));
  }

 public:
  template <typename Protocol>
  static void read(Protocol& protocol, Type& out) {
    // TODO: readSetBegin takes (TType, std::uint32_t)
    // instead of a (TType, std::size_t)
    std::uint32_t set_size = -1;
    protocol::TType reported_type = protocol::T_STOP;

    out = Type();
    protocol.readSetBegin(reported_type, set_size);
    if (detail::is_unknown_container_size(set_size)) {
      while (protocol.peekSet()) {
        consume_elem(protocol, out);
      }
    } else {
      assert(reported_type == elem_methods::ttype_value);
      for (decltype(set_size) i = 0; i < set_size; i++) {
        consume_elem(protocol, out);
      }
    }

    protocol.readSetEnd();
  }

  template <typename Protocol>
  static std::size_t write(Protocol& protocol, Type const& in) {
    std::size_t xfer = 0;
    xfer += protocol.writeSetBegin(elem_methods::ttype_value, in.size());
    for (auto const& elem : in) {
      xfer += elem_methods::write(protocol, elem);
    }
    xfer += protocol.writeSetEnd();
    return xfer;
  }

  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, Type const& out) {
    std::size_t xfer = 0;
    xfer +=
        protocol.serializedSizeSetBegin(elem_methods::ttype_value, out.size());

    for (auto const& elem : out) {
      xfer += elem_methods::template serialized_size<ZeroCopy>(protocol, elem);
    }

    xfer += protocol.serializedSizeSetEnd();
    return xfer;
  }
};

// Maps
template <typename KeyClass, typename MappedClass, typename Type>
struct protocol_methods<type_class::map<KeyClass, MappedClass>, Type> {
  constexpr static protocol::TType ttype_value = protocol::T_MAP;

  using key_type =
      folly::remove_cvref_t<decltype(std::declval<Type>().begin()->first)>;
  using mapped_type =
      folly::remove_cvref_t<decltype(std::declval<Type>().begin()->second)>;

  static_assert(
      !std::is_same<KeyClass, type_class::unknown>(),
      "Unable to serialize unknown key type in map");
  static_assert(
      !std::is_same<MappedClass, type_class::unknown>(),
      "Unable to serialize unknown mapped type in map");

  using key_methods = protocol_methods<KeyClass, key_type>;
  using mapped_methods = protocol_methods<MappedClass, mapped_type>;

 private:
  template <typename Protocol>
  static void consume_elem(Protocol& protocol, Type& out) {
    key_type key_tmp;
    key_methods::read(protocol, key_tmp);
    mapped_methods::read(protocol, out[std::move(key_tmp)]);
  }

 public:
  template <typename Protocol>
  static void read(Protocol& protocol, Type& out) {
    // TODO: see above re: readMapBegin taking a uint32_t size param
    std::uint32_t map_size = -1;
    protocol::TType rpt_key_type = protocol::T_STOP,
                    rpt_mapped_type = protocol::T_STOP;
    out = Type();

    protocol.readMapBegin(rpt_key_type, rpt_mapped_type, map_size);
    DVLOG(3) << "read map begin: " << rpt_key_type << "/" << rpt_mapped_type
             << " (" << map_size << ")";

    if (detail::is_unknown_container_size(map_size)) {
      while (protocol.peekMap()) {
        consume_elem(protocol, out);
      }
    } else {
      // CompactProtocol does not transmit key/mapped types if
      // the map is empty
      if (map_size > 0) {
        assert(key_methods::ttype_value == rpt_key_type);
        assert(mapped_methods::ttype_value == rpt_mapped_type);
      }
      for (decltype(map_size) i = 0; i < map_size; i++) {
        consume_elem(protocol, out);
      }
    }

    protocol.readMapEnd();
  }

  template <typename Protocol>
  static std::size_t write(Protocol& protocol, Type const& out) {
    std::size_t xfer = 0;
    DVLOG(3) << "start map write: " << key_methods::ttype_value << "/"
             << mapped_methods::ttype_value << " (" << out.size() << ")";
    xfer += protocol.writeMapBegin(
        key_methods::ttype_value, mapped_methods::ttype_value, out.size());

    for (auto const& elem_pair : out) {
      xfer += key_methods::write(protocol, elem_pair.first);
      xfer += mapped_methods::write(protocol, elem_pair.second);
    }

    xfer += protocol.writeMapEnd();
    return xfer;
  }

  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, Type const& out) {
    std::size_t xfer = 0;
    xfer += protocol.serializedSizeMapBegin(
        key_methods::ttype_value, mapped_methods::ttype_value, out.size());

    for (auto const& elem_pair : out) {
      xfer += key_methods ::template serialized_size<ZeroCopy>(
          protocol, elem_pair.first);
      xfer += mapped_methods ::template serialized_size<ZeroCopy>(
          protocol, elem_pair.second);
    }

    xfer += protocol.serializedSizeMapEnd();
    return xfer;
  }
};

namespace detail {

// helper predicate for determining if a struct's MemberInfo is required
// to be read out of the protocol
struct is_required_field {
  template <typename MemberInfo>
  using apply = std::integral_constant<
      bool,
      MemberInfo::optional::value == optionality::required>;
};

// marks isset either on the required field array,
// or the appropriate member within the Struct being read
template <
    std::underlying_type<optionality>::type Optional,
    typename,
    typename MemberInfo,
    typename isset_array,
    typename Struct>
typename std::enable_if<
    static_cast<optionality>(Optional) != optionality::required>::type
mark_isset(isset_array& /*isset*/, Struct& obj) {
  MemberInfo::mark_set(obj, true);
}

template <
    std::underlying_type<optionality>::type Optional,
    typename required_fields,
    typename MemberInfo,
    typename isset_array,
    typename Struct>
typename std::enable_if<
    static_cast<optionality>(Optional) == optionality::required>::type
mark_isset(isset_array& isset, Struct& /*obj*/) {
  using fid_idx = fatal::index_of<required_fields, MemberInfo>;
  static_assert(
      fid_idx::value != fatal::size<required_fields>::value,
      "internal error: didn't find reqired field");
  assert(fid_idx::value < fatal::size<required_fields>::value);
  isset[fid_idx::value] = true;
}

struct extract_descriptor_fid {
  template <typename T>
  using apply = typename T::metadata::id;
};

template <typename T, typename Enable = void>
struct deref;

// General case: methods on deref are no-op, returning their input
template <typename T>
struct deref<T, disable_if_smart_pointer<T>> {
  static T& clear_and_get(T& in) {
    return in;
  }
  static T const& get_const(T const& in) {
    return in;
  }
};

// Special case: We specifically *do not* dereference a unique pointer to
// an IOBuf, because this is a type that the protocol can (de)serialize
// directly
template <>
struct deref<std::unique_ptr<folly::IOBuf>> {
  using T = std::unique_ptr<folly::IOBuf>;
  static T& clear_and_get(T& in) {
    return in;
  }
  static T const& get_const(T const& in) {
    return in;
  }
};

// General case: deref returns a reference to what the
// unique pointer contains
template <typename PtrType>
struct deref<PtrType, enable_if_smart_pointer<PtrType>> {
  using T = typename std::remove_const<typename PtrType::element_type>::type;
  static T& clear_and_get(std::shared_ptr<T const>& in) {
    auto t = std::make_shared<T>();
    auto ret = t.get();
    in = std::move(t);
    return *ret;
  }
  static T& clear_and_get(std::shared_ptr<T>& in) {
    in = std::make_shared<T>();
    return *in;
  }
  static T& clear_and_get(std::unique_ptr<T>& in) {
    in = std::make_unique<T>();
    return *in;
  }
  static T const& get_const(PtrType const& in) {
    return *in;
  }
};

} // namespace detail

// specialization for variants (Thrift unions)
template <typename Union>
struct protocol_methods<type_class::variant, Union> {
  constexpr static protocol::TType ttype_value = protocol::T_STRUCT; // overlaps

  using traits = fatal::variant_traits<Union>;
  using enum_traits = fatal::enum_traits<typename traits::id>;

  // Union.Type id -> descriptor
  using sorted_ids = fatal::sort<
      fatal::transform<typename traits::descriptors, fatal::get_type::id>>;

 private:
  // Visitor for a trie of union field names,
  // for mapping member field `fname` to  field `fid` and `ftype`
  struct member_fname_to_fid {
    template <typename Field>
    void
    operator()(fatal::tag<Field>, field_id_t& fid, protocol::TType& ftype) {
      using descriptor = fatal::get<
          typename traits::descriptors,
          typename Field::value,
          fatal::get_type::id>;

      using field_type = typename descriptor::type;
      using field_tclass = typename descriptor::metadata::type_class;

      static_assert(
          !std::is_same<field_tclass, type_class::unknown>(),
          "Instantiation failure, unknown field type");
      static_assert(
          std::is_same<
              typename descriptor::metadata::name,
              typename Field::name>::value,
          "Instantiation failure, descriptor name mismatch");

      DVLOG(3) << "(union) matched string: "
               << fatal::z_data<typename Field::name>() << ", fid: " << fid
               << ", ftype: " << ftype;

      fid = descriptor::metadata::id::value;
      ftype = protocol_methods<field_tclass, field_type>::ttype_value;
    }
  };

  // Visitor for a binary search on (sorted) field IDs,
  // sets the field `Fid` on the Union `obj` when called
  template <typename Protocol>
  struct set_member_by_fid {
    // Fid is a std::integral_constant<field_id_t, fid>
    template <typename Fid, std::size_t Index>
    void operator()(
        fatal::indexed<Fid, Index>,
        const protocol::TType ftype,
        Protocol& protocol,
        Union& obj) const {
      using descriptor = fatal::get<
          typename traits::descriptors,
          Fid,
          detail::extract_descriptor_fid>;

      using field_methods = protocol_methods<
          typename descriptor::metadata::type_class,
          typename descriptor::type>;

      if (ftype == field_methods::ttype_value) {
        typename descriptor::type tmp;
        typename descriptor::setter field_setter;
        field_methods::read(protocol, tmp);
        field_setter(obj, std::move(tmp));
      } else {
        protocol.skip(ftype);
      }
    }
  };

 public:
  template <typename Protocol>
  static void read(Protocol& protocol, Union& out) {
    field_id_t fid = -1;
    protocol::TType ftype = protocol::T_STOP;
    std::string fname;

    protocol.readStructBegin(fname);

    DVLOG(3) << "began reading union: " << fname;
    protocol.readFieldBegin(fname, ftype, fid);
    if (ftype == protocol::T_STOP) {
      out.__clear();
    } else {
      // fid might not be known, such as in the case of the SimpleJSON protocol
      if (fid == std::numeric_limits<int16_t>::min()) {
        // if so, look up fid via fname
        assert(fname != "");
        bool const found = fatal::
            trie_find<typename enum_traits::fields, fatal::get_type::name>(
                fname.begin(), fname.end(), member_fname_to_fid(), fid, ftype);
        assert(found);
      }

      using sorted_fids = fatal::sort<fatal::transform<
          typename traits::descriptors,
          detail::extract_descriptor_fid>>;
      if (!fatal::sorted_search<sorted_fids>(
              fid, set_member_by_fid<Protocol>(), ftype, protocol, out)) {
        DVLOG(3) << "didn't find field, fid: " << fid;
        protocol.skip(ftype);
      }

      protocol.readFieldEnd();
      protocol.readFieldBegin(fname, ftype, fid);
      if (UNLIKELY(ftype != protocol::T_STOP)) {
        using apache::thrift::protocol::TProtocolException;
        TProtocolException::throwUnionMissingStop();
      }
      protocol.readStructEnd();
    }
  }

 private:
  struct write_member_by_fid {
    template <typename Id, std::size_t Index, typename Protocol>
    void operator()(
        fatal::indexed<Id, Index>,
        std::size_t& xfer,
        Protocol& protocol,
        Union const& obj) {
      using descriptor =
          fatal::get<typename traits::descriptors, Id, fatal::get_type::id>;

      typename descriptor::getter getter;
      using methods = protocol_methods<
          typename descriptor::metadata::type_class,
          typename descriptor::type>;

      assert(Id::value == descriptor::id::value);

      DVLOG(3) << "writing union field "
               << fatal::z_data<typename descriptor::metadata::name>()
               << ", fid: " << descriptor::metadata::id::value
               << ", ttype: " << methods::ttype_value;

      xfer += protocol.writeFieldBegin(
          fatal::z_data<typename descriptor::metadata::name>(),
          methods::ttype_value,
          descriptor::metadata::id::value);
      auto const& tmp = getter(obj);
      using member_type = folly::remove_cvref_t<decltype(tmp)>;
      xfer +=
          methods::write(protocol, detail::deref<member_type>::get_const(tmp));
      xfer += protocol.writeFieldEnd();
    }
  };

 public:
  template <typename Protocol>
  static std::size_t write(Protocol& protocol, Union const& in) {
    std::size_t xfer = 0;
    xfer += protocol.writeStructBegin(fatal::z_data<typename traits::name>());
    fatal::sorted_search<sorted_ids>(
        in.getType(), write_member_by_fid(), xfer, protocol, in);
    xfer += protocol.writeFieldStop();
    xfer += protocol.writeStructEnd();
    DVLOG(3) << "end writing union";
    return xfer;
  }

 private:
  template <bool ZeroCopy>
  struct size_member_by_type_id {
    template <typename Id, std::size_t Index, typename Protocol>
    void operator()(
        fatal::indexed<Id, Index>,
        std::size_t& xfer,
        Protocol& protocol,
        Union const& obj) {
      using descriptor =
          fatal::get<typename traits::descriptors, Id, fatal::get_type::id>;
      typename descriptor::getter getter;
      using methods = protocol_methods<
          typename descriptor::metadata::type_class,
          typename descriptor::type>;

      assert(Id::value == descriptor::id::value);

      DVLOG(3) << "sizing union field "
               << fatal::z_data<typename descriptor::metadata::name>()
               << ", fid: " << descriptor::metadata::id::value
               << ", ttype: " << methods::ttype_value;

      xfer += protocol.serializedFieldSize(
          fatal::z_data<typename descriptor::metadata::name>(),
          methods::ttype_value,
          descriptor::metadata::id::value);
      auto const& tmp = getter(obj);
      using member_type = folly::remove_cvref_t<decltype(tmp)>;
      xfer += methods::template serialized_size<ZeroCopy>(
          protocol, detail::deref<member_type>::get_const(tmp));
    }
  };

 public:
  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, Union const& in) {
    std::size_t xfer = 0;

    xfer +=
        protocol.serializedStructSize(fatal::z_data<typename traits::name>());
    fatal::sorted_search<sorted_ids>(
        in.getType(), size_member_by_type_id<ZeroCopy>(), xfer, protocol, in);
    xfer += protocol.serializedSizeStop();
    return xfer;
  }
};

// specialization for structs
template <typename Struct>
struct protocol_methods<type_class::structure, Struct> {
  constexpr static protocol::TType ttype_value = protocol::T_STRUCT;

 private:
  using traits = apache::thrift::reflect_struct<Struct>;

  using all_fields =
      fatal::partition<typename traits::members, detail::is_required_field>;
  using required_fields = fatal::first<all_fields>;
  using optional_fields = fatal::second<all_fields>;

  using isset_array = std::bitset<fatal::size<required_fields>::value>;

  // mapping member fname -> fid
  struct member_fname_to_fid {
    template <typename Member>
    void
    operator()(fatal::tag<Member>, field_id_t& fid, protocol::TType& ftype) {
      fid = Member::id::value;
      ftype =
          protocol_methods<typename Member::type_class, typename Member::type>::
              ttype_value;

      DVLOG(3) << "matched string: " << fatal::z_data<typename Member::name>()
               << ", fid: " << fid << ", ftype: " << ftype;
    }
  };

  // match on member field id -> set that field
  struct set_member_by_fid {
    // Fid is a std::integral_constant<field_id_t, fid>
    template <
        typename Fid,
        std::size_t Index,
        typename Protocol,
        typename isset_array>
    void operator()(
        fatal::indexed<Fid, Index>,
        const protocol::TType ftype,
        Protocol& protocol,
        Struct& obj,
        isset_array& required_isset) {
      using member =
          fatal::get<typename traits::members, Fid, fatal::get_type::id>;
      using getter = typename member::getter;

      using protocol_method =
          protocol_methods<typename member::type_class, typename member::type>;

      using member_type = folly::remove_cvref_t<decltype(getter::ref(obj))>;

      if (ftype == protocol_method::ttype_value) {
        detail::mark_isset<
            folly::to_underlying(member::optional::value),
            required_fields,
            member>(required_isset, obj);
        protocol_method::read(
            protocol,
            detail::deref<member_type>::clear_and_get(getter::ref(obj)));
      } else {
        protocol.skip(ftype);
      }
    }
  };

 public:
  template <typename Protocol>
  static void read(Protocol& protocol, Struct& out) {
    using namespace fatal;
    std::string fname;
    apache::thrift::protocol::TType ftype = protocol::T_STOP;
    std::int16_t fid = -1;
    isset_array required_isset = {};

    protocol.readStructBegin(fname);
    DVLOG(3) << "start reading struct: " << fname << " ("
             << z_data<typename traits::name>() << ")";

    while (true) {
      protocol.readFieldBegin(fname, ftype, fid);
      DVLOG(3) << "type: " << ftype << ", fname: " << fname << ", fid: " << fid;

      if (ftype == apache::thrift::protocol::T_STOP) {
        break;
      }

      // fid might not be known, such as in the case of SimpleJSON protocol
      if (fid == std::numeric_limits<int16_t>::min()) {
        // if so, look up fid via fname
        assert(fname != "");
        bool const found_ =
            trie_find<typename traits::members, fatal::get_type::name>(
                fname.begin(), fname.end(), member_fname_to_fid(), fid, ftype);
        if (!found_) {
          protocol.skip(ftype);
          protocol.readFieldEnd();
          continue;
        }
      }

      using sorted_fids =
          sort<transform<typename traits::members, get_type::id>>;
      if (!sorted_search<sorted_fids>(
              fid, set_member_by_fid(), ftype, protocol, out, required_isset)) {
        DVLOG(3) << "didn't find field, fid: " << fid << ", fname: " << fname;
        protocol.skip(ftype);
      }

      protocol.readFieldEnd();
    }

    for (std::size_t idx = 0; idx < required_isset.size(); idx++) {
      if (!required_isset[idx]) {
        throw protocol::TProtocolException(
            protocol::TProtocolException::MISSING_REQUIRED_FIELD,
            "Required field was not found in serialized data!");
      }
    }

    protocol.readStructEnd();
  }

 private:
  template <
      typename Protocol,
      field_id_t MemberFid,
      typename TypeClass,
      typename MemberType,
      typename Methods,
      std::underlying_type<optionality>::type Optional,
      typename Enable = void>
  struct field_writer;

  // generic field writer
  template <
      typename Protocol,
      field_id_t MemberFid,
      typename TypeClass,
      typename MemberType,
      typename Methods,
      std::underlying_type<optionality>::type Optional>
  struct field_writer<
      Protocol,
      MemberFid,
      TypeClass,
      MemberType,
      Methods,
      Optional,
      detail::disable_if_smart_pointer<MemberType>> {
    using Member = fatal::get<
        typename traits::members,
        std::integral_constant<field_id_t, MemberFid>,
        fatal::get_type::id>;

    static std::size_t write(Protocol& protocol, MemberType const& in) {
      std::size_t xfer = 0;
      // TODO: can maybe get rid of get_const?
      xfer += protocol.writeFieldBegin(
          fatal::z_data<typename Member::name>(),
          Methods::ttype_value,
          Member::id::value);
      xfer +=
          Methods::write(protocol, detail::deref<MemberType>::get_const(in));
      xfer += protocol.writeFieldEnd();
      return xfer;
    }
  };

  // writer for default/required ref structrs
  template <
      typename Protocol,
      field_id_t MemberFid,
      typename PtrType,
      typename Methods,
      std::underlying_type<optionality>::type Optional>
  struct field_writer<
      Protocol,
      MemberFid,
      type_class::structure,
      PtrType,
      Methods,
      Optional,
      detail::enable_if_smart_pointer<PtrType>> {
    using struct_type =
        typename std::remove_const<typename PtrType::element_type>::type;
    using Member = fatal::get<
        typename traits::members,
        std::integral_constant<field_id_t, MemberFid>,
        fatal::get_type::id>;

    static std::size_t write(Protocol& protocol, PtrType const& in) {
      std::size_t xfer = 0;
      // `in` is a pointer to a struct.
      // if not present, and this isn't an optional field,
      // write out an empty struct
      if (in) {
        xfer += field_writer<
            Protocol,
            MemberFid,
            type_class::structure,
            struct_type,
            Methods,
            Optional>::write(protocol, *in);
      } else {
        using field_traits = reflect_struct<struct_type>;
        DVLOG(3) << "empty ref struct, writing blank struct! "
                 << fatal::z_data<typename field_traits::name>();
        xfer += protocol.writeFieldBegin(
            fatal::z_data<typename Member::name>(),
            Methods::ttype_value,
            Member::id::value);
        xfer += protocol.writeStructBegin(
            fatal::z_data<typename field_traits::name>());
        xfer += protocol.writeFieldStop();
        xfer += protocol.writeStructEnd();
        xfer += protocol.writeFieldEnd();
      }

      return xfer;
    }
  };

  // writer for optional ref structs
  template <
      typename Protocol,
      field_id_t MemberFid,
      typename PtrType,
      typename Methods>
  struct field_writer<
      Protocol,
      MemberFid,
      type_class::structure,
      PtrType,
      Methods,
      static_cast<std::underlying_type<optionality>::type>(
          optionality::optional),
      detail::enable_if_smart_pointer<PtrType>> {
    static std::size_t write(Protocol& protocol, PtrType const& in) {
      if (in) {
        return field_writer<
            Protocol,
            MemberFid,
            type_class::structure,
            PtrType,
            Methods,
            static_cast<std::underlying_type<optionality>::type>(
                optionality::required)>::write(protocol, in);
      } else {
        return 0;
      }
    }
  };

  struct member_writer {
    template <typename Member, std::size_t Index, typename Protocol>
    void operator()(
        fatal::indexed<Member, Index>,
        Protocol& protocol,
        Struct const& in,
        std::size_t& xfer) {
      using methods =
          protocol_methods<typename Member::type_class, typename Member::type>;

      if ((Member::optional::value == optionality::required_of_writer) ||
          Member::is_set(in)) {
        DVLOG(3) << "start field write: "
                 << fatal::z_data<typename Member::name>()
                 << " ttype:" << methods::ttype_value
                 << ", id:" << Member::id::value;

        auto const& got = Member::getter::ref(in);
        using member_type = folly::remove_cvref_t<decltype(got)>;

        xfer += field_writer<
            Protocol,
            Member::id::value,
            typename Member::type_class,
            member_type,
            methods,
            static_cast<std::underlying_type<optionality>::type>(
                Member::optional::value)>::write(protocol, got);
      }
    }
  };

  template <
      bool ZeroCopy,
      typename Protocol,
      field_id_t MemberFid,
      typename TypeClass,
      typename MemberType,
      typename Methods,
      std::underlying_type<optionality>::type,
      typename Enable = void>
  struct field_size;

  // generic field size
  template <
      bool ZeroCopy,
      typename Protocol,
      field_id_t MemberFid,
      typename TypeClass,
      typename MemberType,
      typename Methods,
      std::underlying_type<optionality>::type Optional>
  struct field_size<
      ZeroCopy,
      Protocol,
      MemberFid,
      TypeClass,
      MemberType,
      Methods,
      Optional,
      detail::disable_if_smart_pointer<MemberType>> {
    using Member = fatal::get<
        typename traits::members,
        std::integral_constant<field_id_t, MemberFid>,
        fatal::get_type::id>;

    static std::size_t size(Protocol& protocol, MemberType const& in) {
      std::size_t xfer = 0;
      xfer += protocol.serializedFieldSize(
          fatal::z_data<typename Member::name>(),
          Methods::ttype_value,
          Member::id::value);
      xfer += Methods::template serialized_size<ZeroCopy>(
          protocol, detail::deref<MemberType>::get_const(in));
      return xfer;
    }
  };

  // size for default/required ref structrs
  template <
      bool ZeroCopy,
      typename Protocol,
      field_id_t MemberFid,
      typename PtrType,
      typename Methods,
      std::underlying_type<optionality>::type Optional>
  struct field_size<
      ZeroCopy,
      Protocol,
      MemberFid,
      type_class::structure,
      PtrType,
      Methods,
      Optional,
      detail::enable_if_smart_pointer<PtrType>> {
    using struct_type =
        typename std::remove_const<typename PtrType::element_type>::type;
    using Member = fatal::get<
        typename traits::members,
        std::integral_constant<field_id_t, MemberFid>,
        fatal::get_type::id>;

    static std::size_t size(Protocol& protocol, PtrType const& in) {
      std::size_t xfer = 0;
      if (in) {
        xfer += field_size<
            ZeroCopy,
            Protocol,
            MemberFid,
            type_class::structure,
            struct_type,
            Methods,
            Optional>::size(protocol, *in);
      } else {
        using field_traits = reflect_struct<struct_type>;
        DVLOG(3) << "empty ref struct, sizing blank struct! "
                 << fatal::z_data<typename field_traits::name>();
        xfer += protocol.serializedFieldSize(
            fatal::z_data<typename Member::name>(),
            Methods::ttype_value,
            Member::id::value);
        xfer += protocol.serializedStructSize(
            fatal::z_data<typename field_traits::name>());
        xfer += protocol.serializedSizeStop();
      }

      return xfer;
    }
  };

  // size for optional ref structs
  template <
      bool ZeroCopy,
      typename Protocol,
      field_id_t MemberFid,
      typename PtrType,
      typename Methods>
  struct field_size<
      ZeroCopy,
      Protocol,
      MemberFid,
      type_class::structure,
      PtrType,
      Methods,
      static_cast<std::underlying_type<optionality>::type>(
          optionality::optional),
      detail::enable_if_smart_pointer<PtrType>> {
    static std::size_t size(Protocol& protocol, PtrType const& in) {
      if (in) {
        return field_size<
            ZeroCopy,
            Protocol,
            MemberFid,
            type_class::structure,
            PtrType,
            Methods,
            static_cast<std::underlying_type<optionality>::type>(
                optionality::required)>::size(protocol, in);
      } else {
        return 0;
      }
    }
  };

  template <bool ZeroCopy>
  struct member_size {
    template <typename Member, std::size_t Index, typename Protocol>
    void inline operator()(
        fatal::indexed<Member, Index>,
        Protocol& protocol,
        Struct const& in,
        std::size_t& xfer) {
      using methods =
          protocol_methods<typename Member::type_class, typename Member::type>;

      auto const& got = Member::getter::ref(in);
      using member_type = folly::remove_cvref_t<decltype(got)>;

      xfer += field_size<
          ZeroCopy,
          Protocol,
          Member::id::value,
          typename Member::type_class,
          member_type,
          methods,
          static_cast<std::underlying_type<optionality>::type>(
              Member::optional::value)>::size(protocol, got);
    }
  };

 public:
  template <typename Protocol>
  static std::size_t write(Protocol& protocol, Struct const& in) {
    std::size_t xfer = 0;

    xfer += protocol.writeStructBegin(fatal::z_data<typename traits::name>());
    fatal::foreach<typename traits::members>(
        member_writer(), protocol, in, xfer);
    xfer += protocol.writeFieldStop();
    xfer += protocol.writeStructEnd();
    return xfer;
  }

  template <bool ZeroCopy, typename Protocol>
  static std::size_t serialized_size(Protocol& protocol, Struct const& in) {
    std::size_t xfer = 0;
    xfer +=
        protocol.serializedStructSize(fatal::z_data<typename traits::name>());
    fatal::foreach<typename traits::members>(
        member_size<ZeroCopy>(), protocol, in, xfer);
    xfer += protocol.serializedSizeStop();
    return xfer;
  }
};

/**
 * Entrypoints for using new serialization methods
 *
 * // C++
 * MyStruct a;
 * MyUnion b;
 * CompactProtocolReader reader;
 * CompactProtocolReader writer;
 *
 * serializer_read(a, reader);
 * serializer_write(b, writer);
 *
 * @author: Dylan Knutson <dymk@fb.com>
 */

template <typename Type, typename Protocol>
std::size_t serializer_read(Type& out, Protocol& protocol) {
  auto xferStart = protocol.getCursorPosition();
  protocol_methods<reflect_type_class<Type>, Type>::read(protocol, out);
  return protocol.getCursorPosition() - xferStart;
}

template <typename Type, typename Protocol>
std::size_t serializer_write(Type const& in, Protocol& protocol) {
  return protocol_methods<reflect_type_class<Type>, Type>::write(protocol, in);
}

template <typename Type, typename Protocol>
std::size_t serializer_serialized_size(Type const& in, Protocol& protocol) {
  return protocol_methods<reflect_type_class<Type>, Type>::
      template serialized_size<false>(protocol, in);
}

template <typename Type, typename Protocol>
std::size_t serializer_serialized_size_zc(Type const& in, Protocol& protocol) {
  return protocol_methods<reflect_type_class<Type>, Type>::
      template serialized_size<true>(protocol, in);
}

} // namespace thrift
} // namespace apache
