#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <mysql.h>
#include "type/uuid.hxx"

void init_bind(MYSQL_BIND& bind, enum_field_types type, size_t size);

template <typename T>
void type_to_param(const T& v, MYSQL_BIND& bind, enum_field_types type);
template <typename T>
void type_to_param(const std::optional<T>& v, MYSQL_BIND& bind,
                   enum_field_types type);

void type_to_param(const std::nullptr_t v, MYSQL_BIND& bind,
                   enum_field_types type);
void type_to_param(const char* v, MYSQL_BIND& bind, enum_field_types type);
void type_to_param(const std::string& v, MYSQL_BIND& bind,
                   enum_field_types type);

template <typename T>
void type_to_param(const std::optional<T>& v, MYSQL_BIND& bind);
void type_to_param(const std::nullptr_t v, MYSQL_BIND& bind);
void type_to_param(const int8_t v, MYSQL_BIND& bind);
void type_to_param(const uint8_t v, MYSQL_BIND& bind);
void type_to_param(const int16_t v, MYSQL_BIND& bind);
void type_to_param(const uint16_t v, MYSQL_BIND& bind);
void type_to_param(const int32_t v, MYSQL_BIND& bind);
void type_to_param(const uint32_t v, MYSQL_BIND& bind);
void type_to_param(const uint64_t v, MYSQL_BIND& bind);
void type_to_param(const float v, MYSQL_BIND& bind);
void type_to_param(const bool v, MYSQL_BIND& bind);
void type_to_param(const char* v, MYSQL_BIND& bind);
void type_to_param(const std::string& v, MYSQL_BIND& bind);
void type_to_param(const UUID& v, MYSQL_BIND& bind);

template <typename T>
void type_to_result(MYSQL_BIND& bind, enum_field_types type);
template <>
void type_to_result<std::string>(MYSQL_BIND& bind, enum_field_types type);

template <typename T>
T result_to_value(const MYSQL_BIND& bind);
template <typename T>
void result_to_value(std::optional<T>& v, const MYSQL_BIND& bind);
template <>
std::string result_to_value<std::string>(const MYSQL_BIND& bind);
template <>
UUID result_to_value<UUID>(const MYSQL_BIND& bind);

#include "transform.ixx"