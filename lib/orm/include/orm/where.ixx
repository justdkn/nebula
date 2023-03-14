#include <string>
#include "where.hxx"

template <typename T>
QueryWhere EQ(const char* name, const T& value) {
  return new_query_where(name, Op::eq, value);
}

template <typename T>
QueryWhere EQ(const char* name, const std::optional<T>& value) {
  if (value) {
    return EQ(name, value.value());
  } else {
    return EQ(name, nullptr);
  }
}

template <typename T>
QueryWhere NE(const char* name, const T& value) {
  return new_query_where(name, Op::ne, value);
}

template <typename T>
QueryWhere NE(const char* name, const std::optional<T>& value) {
  if (value) {
    return NE(name, value.value());
  } else {
    return NE(name, nullptr);
  }
}

template <typename T>
QueryWhere GT(const char* name, const T& value) {
  return new_query_where(name, Op::gt, value);
}

template <typename T>
QueryWhere GT(const char* name, const std::optional<T>& value) {
  if (value) {
    return GT(name, value.value());
  } else {
    return GT(name, nullptr);
  }
}

template <typename T>
QueryWhere GE(const char* name, const T& value) {
  return new_query_where(name, Op::ge, value);
}

template <typename T>
QueryWhere GE(const char* name, const std::optional<T>& value) {
  if (value) {
    return GE(name, value.value());
  } else {
    return GE(name, nullptr);
  }
}

template <typename T>
QueryWhere LT(const char* name, const T& value) {
  return new_query_where(name, Op::lt, value);
}

template <typename T>
QueryWhere LT(const char* name, const std::optional<T>& value) {
  if (value) {
    return LT(name, value.value());
  } else {
    return LT(name, nullptr);
  }
}

template <typename T>
QueryWhere LE(const char* name, const T& value) {
  return new_query_where(name, Op::le, value);
}

template <typename T>
QueryWhere LE(const char* name, const std::optional<T>& value) {
  if (value) {
    return LE(name, value.value());
  } else {
    return LE(name, nullptr);
  }
}