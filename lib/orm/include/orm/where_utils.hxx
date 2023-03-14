#pragma once

#include <cstddef>
#include <optional>
#include "query_where.hxx"

enum class Op {
  eq,
  ne,
  lt,
  le,
  gt,
  ge,
};

template <typename T>
QueryWhere new_query_where(std::string name, Op op, const T& v);

#include "where_utils.ixx"