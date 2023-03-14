#include "enum.hxx"

template <class E, typename T>
Enum<E, T>::Enum() : value_(0) {
}

template <class E, typename T>
Enum<E, T>::Enum(const Enum& value) : value_(value.value_) {
}

template <class E, typename T>
Enum<E, T>::Enum(const E value) : value_(static_cast<T>(value)) {
}

template <class E, typename T>
Enum<E, T>::Enum(const T value) : value_(value) {
}

template <class E, typename T>
const T& Enum<E, T>::value() const {
  return value_;
}

template <class E, typename T>
Enum<E, T>& Enum<E, T>::operator=(const Enum value) {
  value_ = value.value_;
  return *this;
}

template <class E, typename T>
Enum<E, T>& Enum<E, T>::operator=(const T value) {
  value_ = value;
  return *this;
}

template <class E, typename T>
std::ostream& Enum<E, T>::operator>>(std::ostream& out) const {
  out << value_;
  return out;
}

template <class E, typename T>
std::ostream& operator<<(std::ostream& out, const Enum<E, T>& Enum) {
  return out;
}