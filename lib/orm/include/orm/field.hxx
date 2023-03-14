#pragma once

#include <string>
#include <type_traits>
#include "field_tpl.hxx"
#include "type/uuid.hxx"
#include "type/enum.hxx"

using TinyIntField   = FieldTpl<int8_t, MYSQL_TYPE_TINY>;
using UTinyIntField  = FieldTpl<uint8_t, MYSQL_TYPE_TINY>;
using SmallIntField  = FieldTpl<int16_t, MYSQL_TYPE_SHORT>;
using USmallIntField = FieldTpl<uint16_t, MYSQL_TYPE_SHORT>;
using IntField       = FieldTpl<int32_t, MYSQL_TYPE_LONG>;
using UIntField      = FieldTpl<uint32_t, MYSQL_TYPE_LONG>;
using BigIntField    = FieldTpl<int64_t, MYSQL_TYPE_LONGLONG>;
using UBigIntField   = FieldTpl<uint64_t, MYSQL_TYPE_LONGLONG>;
using FloatField     = FieldTpl<float, MYSQL_TYPE_LONGLONG>;
using BoolField      = FieldTpl<bool, MYSQL_TYPE_BOOL>;
using StringField    = FieldTpl<std::string, MYSQL_TYPE_STRING>;
using UUIDField      = FieldTpl<UUID, MYSQL_TYPE_TINY_BLOB>;
template <class E>
using TinyEnumField = FieldTpl<Enum<E, int8_t>, MYSQL_TYPE_TINY>;
