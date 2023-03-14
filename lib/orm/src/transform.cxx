#include <cstring>
#include <orm/transform.hxx>
#include <type_traits>

void init_bind(MYSQL_BIND& bind, enum_field_types type, size_t size) {
  memset(&bind, 0, sizeof(MYSQL_BIND));
  bind.buffer_type   = type;
  bind.buffer        = (void*)new char[size];
  bind.buffer_length = size;
  bind.length_value  = size;
}

void type_to_param(const std::nullptr_t v, MYSQL_BIND& bind,
                   enum_field_types type) {
  memset(&bind, 0, sizeof(MYSQL_BIND));
  bind.buffer_type = MYSQL_TYPE_NULL;
}

void type_to_param(const char* v, MYSQL_BIND& bind, enum_field_types type) {
  const int size = strlen(v) + 1;
  init_bind(bind, type, size);
  memcpy(bind.buffer, v, size);
  bind.length_value = size - 1;
}

void type_to_param(const std::string& v, MYSQL_BIND& bind,
                   enum_field_types type) {
  type_to_param(v.c_str(), bind, type);
}

void type_to_param(const std::nullptr_t v, MYSQL_BIND& bind) {
  memset(&bind, 0, sizeof(MYSQL_BIND));
  bind.buffer_type = MYSQL_TYPE_NULL;
}

void type_to_param(const int8_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_TINY);
}

void type_to_param(const uint8_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_TINY);
}

void type_to_param(const int16_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_SHORT);
}

void type_to_param(const uint16_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_SHORT);
}

void type_to_param(const int32_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_LONG);
}

void type_to_param(const uint32_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_LONG);
}

void type_to_param(const int64_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_LONGLONG);
}

void type_to_param(const uint64_t v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_LONGLONG);
}

void type_to_param(const float v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_FLOAT);
}

void type_to_param(const bool v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_BOOL);
}

void type_to_param(const char* v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_STRING);
}

void type_to_param(const std::string& v, MYSQL_BIND& bind) {
  type_to_param(v.c_str(), bind);
}

void type_to_param(const UUID& v, MYSQL_BIND& bind) {
  type_to_param(v, bind, MYSQL_TYPE_TINY_BLOB);
}

template <>
void type_to_result<std::string>(MYSQL_BIND& bind, enum_field_types type) {
  constexpr size_t DefaultSize = 300;
  init_bind(bind, type, DefaultSize);
}

template <>
std::string result_to_value<std::string>(const MYSQL_BIND& bind) {
  return (const char*)bind.buffer;
}

template <>
UUID result_to_value<UUID>(const MYSQL_BIND& bind) {
  return UUID((const unsigned char*)bind.buffer);
}