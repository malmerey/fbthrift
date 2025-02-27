#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#
cimport cython as __cython
from cpython.bytes cimport PyBytes_AsStringAndSize
from cpython.object cimport PyTypeObject, Py_LT, Py_LE, Py_EQ, Py_NE, Py_GT, Py_GE
from libcpp.memory cimport shared_ptr, make_shared, unique_ptr, make_unique
from libcpp.string cimport string
from libcpp cimport bool as cbool
from libcpp.iterator cimport inserter as cinserter
from cpython cimport bool as pbool
from libc.stdint cimport int8_t, int16_t, int32_t, int64_t, uint32_t
from cython.operator cimport dereference as deref, preincrement as inc, address as ptr_address
import thrift.py3.types
cimport thrift.py3.types
cimport thrift.py3.exceptions
from thrift.py3.types import NOTSET as __NOTSET
from thrift.py3.types cimport (
    translate_cpp_enum_to_python,
    SetMetaClass as __SetMetaClass,
    constant_shared_ptr,
    default_inst,
)
cimport thrift.py3.std_libcpp as std_libcpp
from thrift.py3.serializer import Protocol as __Protocol
cimport thrift.py3.serializer as serializer
from thrift.py3.serializer import deserialize, serialize
import folly.iobuf as __iobuf
from folly.optional cimport cOptional

import sys
import itertools
from collections.abc import Sequence, Set, Mapping, Iterable
import warnings
import weakref as __weakref
import builtins as _builtins



cdef object __Nada_Union_TypeEnumMembers = None


@__cython.internal
@__cython.auto_pickle(False)
cdef class __Nada_Union_TypeMeta(type):
    def __call__(cls, value):
        cdef int cvalue
        if isinstance(value, cls) and value in __Nada_Union_TypeEnumMembers:
            return value

        if isinstance(value, int):
            cvalue = value
            if cvalue == 0:
                return __NadaType.EMPTY

        raise ValueError(f'{value} is not a valid Nada.Type')

    def __getitem__(cls, name):
        if name == "EMPTY":
            return __NadaType.EMPTY
        raise KeyError(name)

    def __dir__(cls):
        return ['__class__', '__doc__', '__members__', '__module__', 'EMPTY',
        ]

    @property
    def __members__(cls):
        return {m.name: m for m in cls}

    def __iter__(cls):
        yield __NadaType.EMPTY
        return iter(())

    def __reversed__(cls):
        return reversed(iter(cls))

    def __contains__(cls, item):
        if not isinstance(item, cls):
            return False
        return item in __Nada_Union_TypeEnumMembers

    def __len__(cls):
        return 0+1  # For Empty


@__cython.final
cdef class __NadaType(thrift.py3.types.CompiledEnum):
    EMPTY = __NadaType.__new__(__NadaType, 0, "EMPTY")

    def __cinit__(self, value, name):
        if __Nada_Union_TypeEnumMembers is not None:
            raise TypeError('For Safty we have disabled __new__')
        self.value = value
        self.name = name
        self.__hash = hash(name)
        self.__str = f"Nada.Type.{name}"
        self.__repr = f"<{self.__str}: {value}>"

    def __repr__(self):
        return self.__repr

    def __str__(self):
        return self.__str

    def __int__(self):
        return self.value

    def __eq__(self, other):
        if not isinstance(other, __NadaType):
            warnings.warn(f"comparison not supported between instances of { __NadaType } and {type(other)}", RuntimeWarning, stacklevel=2)
            return False
        return self is other

    def __hash__(self):
        return self.__hash

    def __reduce__(self):
        return __NadaType, (self.value,)

__SetMetaClass(<PyTypeObject*> __NadaType, <PyTypeObject*> __Nada_Union_TypeMeta)
__Nada_Union_TypeEnumMembers = set(__NadaType)


cdef class Empty(thrift.py3.types.Struct):

    def __init__(
        Empty self, *
    ):
        self._cpp_obj = move(Empty._make_instance(
          NULL,
          NULL,
        ))

    def __call__(
        Empty self
    ):
        return self

    @staticmethod
    cdef unique_ptr[cEmpty] _make_instance(
        cEmpty* base_instance,
        bint* __isNOTSET
    ) except *:
        cdef unique_ptr[cEmpty] c_inst
        if base_instance:
            c_inst = make_unique[cEmpty](deref(base_instance))
        else:
            c_inst = make_unique[cEmpty]()

        if base_instance:
            # Convert None's to default value. (or unset)
            pass
        # in C++ you don't have to call move(), but this doesn't translate
        # into a C++ return statement, so you do here
        return move_unique(c_inst)

    def __iter__(self):
        return iter(())

    def __bool__(self):
        return True

    @staticmethod
    cdef create(shared_ptr[cEmpty] cpp_obj):
        inst = <Empty>Empty.__new__(Empty)
        inst._cpp_obj = move_shared(cpp_obj)
        return inst


    def __hash__(Empty self):
        if not self.__hash:
            self.__hash = hash((
            type(self)   # Hash the class there are no fields
            ))
        return self.__hash

    def __repr__(Empty self):
        return f'Empty()'
    def __copy__(Empty self):
        cdef shared_ptr[cEmpty] cpp_obj = make_shared[cEmpty](
            deref(self._cpp_obj)
        )
        return Empty.create(move_shared(cpp_obj))

    def __richcmp__(self, other, op):
        cdef int cop = op
        if not (
                isinstance(self, Empty) and
                isinstance(other, Empty)):
            if cop == Py_EQ:  # different types are never equal
                return False
            elif cop == Py_NE:  # different types are always notequal
                return True
            else:
                return NotImplemented

        cdef cEmpty* cself = (<Empty>self)._cpp_obj.get()
        cdef cEmpty* cother = (<Empty>other)._cpp_obj.get()
        if cop == Py_EQ:
            return deref(cself) == deref(cother)
        elif cop == Py_NE:
            return deref(cself) != deref(cother)
        elif cop == Py_LT:
            return deref(cself) < deref(cother)
        elif cop == Py_LE:
            return deref(cself) <= deref(cother)
        elif cop == Py_GT:
            return deref(cself) > deref(cother)
        elif cop == Py_GE:
            return deref(cself) >= deref(cother)
        else:
            return NotImplemented

    cdef __iobuf.IOBuf _serialize(Empty self, proto):
        cdef __iobuf.cIOBufQueue queue = __iobuf.cIOBufQueue(__iobuf.cacheChainLength())
        cdef cEmpty* cpp_obj = self._cpp_obj.get()
        if proto is __Protocol.COMPACT:
            with nogil:
                serializer.CompactSerialize[cEmpty](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.BINARY:
            with nogil:
                serializer.BinarySerialize[cEmpty](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.JSON:
            with nogil:
                serializer.JSONSerialize[cEmpty](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.COMPACT_JSON:
            with nogil:
                serializer.CompactJSONSerialize[cEmpty](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        return __iobuf.from_unique_ptr(queue.move())

    cdef uint32_t _deserialize(Empty self, const __iobuf.cIOBuf* buf, proto) except? 0:
        cdef uint32_t needed
        self._cpp_obj = make_shared[cEmpty]()
        cdef cEmpty* cpp_obj = self._cpp_obj.get()
        if proto is __Protocol.COMPACT:
            with nogil:
                needed = serializer.CompactDeserialize[cEmpty](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.BINARY:
            with nogil:
                needed = serializer.BinaryDeserialize[cEmpty](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.JSON:
            with nogil:
                needed = serializer.JSONDeserialize[cEmpty](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.COMPACT_JSON:
            with nogil:
                needed = serializer.CompactJSONDeserialize[cEmpty](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        return needed

    def __reduce__(self):
        return (deserialize, (Empty, serialize(self)))




cdef class Nada(thrift.py3.types.Union):
    Type = __NadaType

    def __init__(
        self, *
    ):
        self._cpp_obj = move(Nada._make_instance(
          NULL,
        ))
        self._load_cache()

    @staticmethod
    def fromValue(value):
        if value is None:
            return Nada()
        raise ValueError(f"Unable to derive correct union field for value: {value}")

    @staticmethod
    cdef unique_ptr[cNada] _make_instance(
        cNada* base_instance
    ) except *:
        cdef unique_ptr[cNada] c_inst = make_unique[cNada]()
        cdef bint any_set = False
        # in C++ you don't have to call move(), but this doesn't translate
        # into a C++ return statement, so you do here
        return move_unique(c_inst)

    def __bool__(self):
        return self.type is not __NadaType.EMPTY

    @staticmethod
    cdef create(shared_ptr[cNada] cpp_obj):
        inst = <Nada>Nada.__new__(Nada)
        inst._cpp_obj = move_shared(cpp_obj)
        inst._load_cache()
        return inst


    def __hash__(Nada self):
        if not self.__hash:
            self.__hash = hash((
                self.type,
                self.value,
            ))
        return self.__hash

    def __repr__(Nada self):
        return f'Nada(type={self.type.name}, value={self.value!r})'

    cdef _load_cache(Nada self):
        self.type = Nada.Type(<int>(deref(self._cpp_obj).getType()))
        cdef int type = self.type.value
        if type == 0:    # Empty
            self.value = None

    def get_type(Nada self):
        return self.type

    def __copy__(Nada self):
        cdef shared_ptr[cNada] cpp_obj = make_shared[cNada](
            deref(self._cpp_obj)
        )
        return Nada.create(move_shared(cpp_obj))

    def __richcmp__(self, other, op):
        cdef int cop = op
        if not (
                isinstance(self, Nada) and
                isinstance(other, Nada)):
            if cop == Py_EQ:  # different types are never equal
                return False
            elif cop == Py_NE:  # different types are always notequal
                return True
            else:
                return NotImplemented

        cdef cNada* cself = (<Nada>self)._cpp_obj.get()
        cdef cNada* cother = (<Nada>other)._cpp_obj.get()
        if cop == Py_EQ:
            return deref(cself) == deref(cother)
        elif cop == Py_NE:
            return deref(cself) != deref(cother)
        elif cop == Py_LT:
            return deref(cself) < deref(cother)
        elif cop == Py_LE:
            return deref(cself) <= deref(cother)
        elif cop == Py_GT:
            return deref(cself) > deref(cother)
        elif cop == Py_GE:
            return deref(cself) >= deref(cother)
        else:
            return NotImplemented

    cdef __iobuf.IOBuf _serialize(Nada self, proto):
        cdef __iobuf.cIOBufQueue queue = __iobuf.cIOBufQueue(__iobuf.cacheChainLength())
        cdef cNada* cpp_obj = self._cpp_obj.get()
        if proto is __Protocol.COMPACT:
            with nogil:
                serializer.CompactSerialize[cNada](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.BINARY:
            with nogil:
                serializer.BinarySerialize[cNada](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.JSON:
            with nogil:
                serializer.JSONSerialize[cNada](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.COMPACT_JSON:
            with nogil:
                serializer.CompactJSONSerialize[cNada](deref(cpp_obj), &queue, serializer.SHARE_EXTERNAL_BUFFER)
        return __iobuf.from_unique_ptr(queue.move())

    cdef uint32_t _deserialize(Nada self, const __iobuf.cIOBuf* buf, proto) except? 0:
        cdef uint32_t needed
        self._cpp_obj = make_shared[cNada]()
        cdef cNada* cpp_obj = self._cpp_obj.get()
        if proto is __Protocol.COMPACT:
            with nogil:
                needed = serializer.CompactDeserialize[cNada](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.BINARY:
            with nogil:
                needed = serializer.BinaryDeserialize[cNada](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.JSON:
            with nogil:
                needed = serializer.JSONDeserialize[cNada](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        elif proto is __Protocol.COMPACT_JSON:
            with nogil:
                needed = serializer.CompactJSONDeserialize[cNada](buf, deref(cpp_obj), serializer.SHARE_EXTERNAL_BUFFER)
        # force a cache reload since the underlying data's changed
        self._load_cache()
        return needed

    def __reduce__(self):
        return (deserialize, (Nada, serialize(self)))


