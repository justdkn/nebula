#pragma once

#include <optional>
#include <type_traits>
#include "field_base.hxx"

template <class T, enum_field_types Type>
class FieldTpl : public FieldBase, public std::optional<T> {
 public:
  explicit FieldTpl(const char* name);
  virtual ~FieldTpl();

 public:
  static constexpr bool is_unsigned  = std::is_unsigned_v<T>;
  static constexpr size_t value_size = sizeof(T);

 public:
  virtual bool is_null() const;
  virtual void to_param(MYSQL_BIND& bind) const;
  virtual void to_result(MYSQL_BIND& bind) const;
  virtual void from_result(const MYSQL_BIND& bind);
  virtual std::ostream& operator>>(std::ostream& out) const;

 public:
  using std::optional<T>::operator bool;
  using std::optional<T>::operator*;
  using std::optional<T>::operator->;
  using std::optional<T>::operator=;
};

#include "field_tpl.ixx"