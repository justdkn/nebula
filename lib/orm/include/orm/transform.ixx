#include "orm/exception.hxx"
#include "transform.hxx"
#include "exception.hxx"

template <typename T>
void type_to_param(const T& v, MYSQL_BIND& bind, enum_field_types type) {
  init_bind(bind, type, sizeof(T));
  bind.is_unsigned = std::is_signed_v<T>;
  memcpy(bind.buffer, &v, sizeof(T));
}

template <typename T>
void type_to_param(const std::optional<T>& v, MYSQL_BIND& bind,
                   enum_field_types type) {
  if (v) {
    type_to_param(v.value(), bind, type);
  } else {
    type_to_param(nullptr, bind, type);
  }
}

template <typename T>
void type_to_param(const std::optional<T>& v, MYSQL_BIND& bind) {
  if (v) {
    type_to_param(v.value(), bind);
  } else {
    type_to_param(nullptr, bind);
  }
}

template <typename T>
void type_to_result(MYSQL_BIND& bind, enum_field_types type) {
  init_bind(bind, type, sizeof(T));
}

template <typename T>
T result_to_value(const MYSQL_BIND& bind) {
  if (bind.length_value != sizeof(T)) throw OrmException("类型大小不匹配");
  return *(T*)bind.buffer;
}

template <typename T>
void result_to_value(std::optional<T>& v, const MYSQL_BIND& bind) {
  if (bind.buffer_type == MYSQL_TYPE_NULL || bind.is_null_value) {
    v = std::nullopt;
  } else {
    v = result_to_value<T>(bind);
  }
}