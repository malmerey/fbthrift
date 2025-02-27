#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

import folly.iobuf as __iobuf
import thrift.py3.types
import thrift.py3.exceptions
from thrift.py3.types import NOTSET, NOTSETTYPE
from thrift.py3.serializer import Protocol
import typing as _typing

import sys
import itertools


__property__ = property


class EmptyEnum(thrift.py3.types.Enum):
    pass


class MyEnum(thrift.py3.types.Enum):
    ONE: MyEnum = ...
    TWO: MyEnum = ...


class MyBigEnum(thrift.py3.types.Enum):
    UNKNOWN: MyBigEnum = ...
    ONE: MyBigEnum = ...
    TWO: MyBigEnum = ...
    THREE: MyBigEnum = ...
    FOUR: MyBigEnum = ...
    FIVE: MyBigEnum = ...
    SIX: MyBigEnum = ...
    SEVEN: MyBigEnum = ...
    EIGHT: MyBigEnum = ...
    NINE: MyBigEnum = ...
    TEN: MyBigEnum = ...
    ELEVEN: MyBigEnum = ...
    TWELVE: MyBigEnum = ...
    THIRTEEN: MyBigEnum = ...
    FOURTEEN: MyBigEnum = ...
    FIFTEEN: MyBigEnum = ...
    SIXTEEN: MyBigEnum = ...
    SEVENTEEN: MyBigEnum = ...
    EIGHTEEN: MyBigEnum = ...
    NINETEEN: MyBigEnum = ...


class MyStruct(thrift.py3.types.Struct, _typing.Hashable, _typing.Iterable[_typing.Tuple[str, _typing.Any]]):
    def __init__(
        self, *,
        myEnum: _typing.Optional[MyEnum]=None,
        myBigEnum: _typing.Optional[MyBigEnum]=None
    ) -> None: ...

    def __call__(
        self, *,
        myEnum: _typing.Union[MyEnum, NOTSETTYPE, None]=NOTSET,
        myBigEnum: _typing.Union[MyBigEnum, NOTSETTYPE, None]=NOTSET
    ) -> MyStruct: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['MyStruct'], bytes]]: ...
    def __iter__(self) -> _typing.Iterator[_typing.Tuple[str, _typing.Any]]: ...
    def __bool__(self) -> bool: ...
    def __hash__(self) -> int: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'MyStruct') -> bool: ...
    def __gt__(self, other: 'MyStruct') -> bool: ...
    def __le__(self, other: 'MyStruct') -> bool: ...
    def __ge__(self, other: 'MyStruct') -> bool: ...

    @__property__
    def myEnum(self) -> MyEnum: ...
    @__property__
    def myBigEnum(self) -> MyBigEnum: ...


kOne: MyEnum = ...
