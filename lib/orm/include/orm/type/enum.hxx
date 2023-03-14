#pragma once

#include <iostream>
#include <type_traits>

template <typename E, typename T>
concept EnumCheck = std::is_same_v<typename std::underlying_type<E>::type, T>;

template <typename E, typename T>
requires EnumCheck<E, T>
class Enum {
 public:
  Enum();
  Enum(const Enum& value);
  Enum(const E value);
  Enum(const T value);

 public:
  const T& value() const;
  Enum& operator=(const Enum value);
  Enum& operator=(const T value);
  std::ostream& operator>>(std::ostream& out) const;

 private:
  T value_;
};

template <class E, typename T>
std::ostream& operator<<(std::ostream& out, const Enum<E, T>& Enum);

#include "enum.ixx"