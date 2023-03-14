#include "enum.hxx"
#include <iostream>
#include <type_traits>

// clang-format off

template <typename E, typename T>
requires EnumCheck<E, T>
Enum<E, T>::Enum()
  : value_(0) {
}

template <typename E, typename T>
requires EnumCheck<E, T>
Enum<E, T>::Enum(const Enum& value)
  : value_(value.value_) {
}

template <typename E, typename T>
requires EnumCheck<E, T>
Enum<E, T>::Enum(const E value)
  : value_(static_cast<T>(value)) {
}

template <typename E, typename T>
requires EnumCheck<E, T>
Enum<E, T>::Enum(const T value)
  : value_(value) {
}

template <typename E, typename T>
requires EnumCheck<E, T>
const T& Enum<E, T>::value() const {
  return value_;
}

template <typename E, typename T>
requires EnumCheck<E, T>
Enum<E, T>& Enum<E, T>::operator=(const Enum value) {
  value_ = value.value_;
  return *this;
}

template <typename E, typename T>
requires EnumCheck<E, T>
Enum<E, T>& Enum<E, T>::operator=(const T value) {
  value_ = value;
  return *this;
}

template <typename E, typename T>
requires EnumCheck<E, T>
std::ostream& Enum<E, T>::operator>>(std::ostream& out) const {
  out << value_;
  return out;
}

// clang-format on

template <typename E, typename T>
std::ostream& operator<<(std::ostream& out, const Enum<E, T>& Enum) {
  return out;
}