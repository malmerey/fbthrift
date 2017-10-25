#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#
from libcpp.memory cimport shared_ptr, make_shared, unique_ptr, make_unique
from libcpp.string cimport string
from libcpp cimport bool as cbool
from cpython cimport bool as pbool
from libc.stdint cimport int8_t, int16_t, int32_t, int64_t
from libcpp.vector cimport vector as vector
from libcpp.set cimport set as cset
from libcpp.map cimport map as cmap
from cython.operator cimport dereference as deref, typeid
from cpython.ref cimport PyObject
from thrift.py3.client cimport py3_get_exception, cRequestChannel_ptr, makeClientWrapper
from folly cimport cFollyTry, cFollyUnit, c_unit
from libcpp.typeinfo cimport type_info
import thrift.py3.types
cimport thrift.py3.types
import thrift.py3.client
cimport thrift.py3.client
from folly.futures cimport bridgeFutureWith
from folly.executor cimport get_executor
cimport cython

import asyncio
import sys
import traceback

cimport module.types
import module.types

from module.clients_wrapper cimport cSomeServiceAsyncClient, cSomeServiceClientWrapper


cdef void SomeService_bounce_map_callback(
    cFollyTry[module.types.std_unordered_map[int32_t,string]]&& result,
    PyObject* future
):
    cdef object pyfuture = <object> future
    if result.hasException():
        try:
            result.exception().throw_exception()
        except Exception as ex:
            pyfuture.set_exception(ex)
    else:
        pyfuture.set_result(module.types.std_unordered_map__Map__i32_string.create(make_shared[module.types.std_unordered_map[int32_t,string]](result.value())))


cdef class SomeService(thrift.py3.client.Client):

    def __cinit__(SomeService self):
        loop = asyncio.get_event_loop()
        self._connect_future = loop.create_future()
        self._executor = get_executor()

    cdef const type_info* _typeid(SomeService self):
        return &typeid(cSomeServiceAsyncClient)

    @staticmethod
    cdef _module_SomeService_set_client(SomeService inst, shared_ptr[cSomeServiceClientWrapper] c_obj):
        """So the class hierarchy talks to the correct pointer type"""
        inst._module_SomeService_client = c_obj

    cdef _module_SomeService_reset_client(SomeService self):
        """So the class hierarchy resets the shared pointer up the chain"""
        self._module_SomeService_client.reset()

    def __dealloc__(SomeService self):
        if self._cRequestChannel or self._module_SomeService_client:
            print('client was not cleaned up, use the context manager', file=sys.stderr)

    async def __aenter__(SomeService self):
        await self._connect_future
        if self._cRequestChannel:
            SomeService._module_SomeService_set_client(
                self,
                makeClientWrapper[cSomeServiceAsyncClient, cSomeServiceClientWrapper](
                    self._cRequestChannel
                ),
            )
            self._cRequestChannel.reset()
        else:
            raise asyncio.InvalidStateError('Client context has been used already')
        return self

    async def __aexit__(SomeService self, *exc):
        self._check_connect_future()
        loop = asyncio.get_event_loop()
        future = loop.create_future()
        bridgeFutureWith[cFollyUnit](
            self._executor,
            deref(self._module_SomeService_client).disconnect(),
            closed_SomeService_py3_client_callback,
            <PyObject *>future
        )
        # To break any future usage of this client
        badfuture = loop.create_future()
        badfuture.set_exception(asyncio.InvalidStateError('Client Out of Context'))
        badfuture.exception()
        self._connect_future = badfuture
        await future
        self._module_SomeService_reset_client()

    def set_persistent_header(SomeService self, str key, str value):
        cdef string ckey = <bytes> key.encode('utf-8')
        cdef string cvalue = <bytes> value.encode('utf-8')
        deref(self._module_SomeService_client).setPersistentHeader(ckey, cvalue)

    @cython.always_allow_keywords(True)
    async def bounce_map(
            SomeService self,
            m):
        self._check_connect_future()
        __loop = asyncio.get_event_loop()
        __future = __loop.create_future()
        bridgeFutureWith[module.types.std_unordered_map[int32_t,string]](
            self._executor,
            deref(self._module_SomeService_client).bounce_map(
                module.types.std_unordered_map[int32_t,string](deref(module.types.std_unordered_map__Map__i32_string(m)._cpp_obj.get())),
            ),
            SomeService_bounce_map_callback,
            <PyObject *> __future
        )
        return await __future



cdef void closed_SomeService_py3_client_callback(
    cFollyTry[cFollyUnit]&& result,
    PyObject* fut,
):
    cdef object pyfuture = <object> fut
    pyfuture.set_result(None)
