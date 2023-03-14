#include <optional>
#include "field_tpl.hxx"
#include "transform.hxx"

template <class T, enum_field_types Type>
FieldTpl<T, Type>::FieldTpl(const char* name)
    : FieldBase(name), std::optional<T>(std::nullopt) {
}

template <class T, enum_field_types Type>
FieldTpl<T, Type>::~FieldTpl() {
}

template <class T, enum_field_types Type>
bool FieldTpl<T, Type>::is_null() const {
  return !this->has_value();
}

template <class T, enum_field_types Type>
void FieldTpl<T, Type>::to_param(MYSQL_BIND& bind) const {
  type_to_param(*static_cast<const std::optional<T>*>(this), bind, Type);
}

template <class T, enum_field_types Type>
void FieldTpl<T, Type>::to_result(MYSQL_BIND& bind) const {
  type_to_result<T>(bind, Type);
}

template <class T, enum_field_types Type>
void FieldTpl<T, Type>::from_result(const MYSQL_BIND& bind) {
  result_to_value(*static_cast<std::optional<T>*>(this), bind);
}

template <class T, enum_field_types Type>
std::ostream& FieldTpl<T, Type>::operator>>(std::ostream& out) const {
  if (this->has_value()) {
    out << this->value();
  } else {
    out << "null";
  }
  return out;
}
