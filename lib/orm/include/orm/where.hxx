#pragma once

#include <optional>
#include "query_where.hxx"
#include "where_utils.hxx"

template <typename T>
QueryWhere EQ(const char* name, const T& value);
template <typename T>
QueryWhere EQ(const char* name, const std::optional<T>& value);
template <typename T>
QueryWhere NE(const char* name, const T& value);
template <typename T>
QueryWhere NE(const char* name, const std::optional<T>& value);
template <typename T>
QueryWhere GT(const char* name, const T& value);
template <typename T>
QueryWhere GT(const char* name, const std::optional<T>& value);
template <typename T>
QueryWhere GE(const char* name, const T& value);
template <typename T>
QueryWhere GE(const char* name, const std::optional<T>& value);
template <typename T>
QueryWhere LT(const char* name, const T& value);
template <typename T>
QueryWhere LT(const char* name, const std::optional<T>& value);
template <typename T>
QueryWhere LE(const char* name, const T& value);
template <typename T>
QueryWhere LE(const char* name, const std::optional<T>& value);

#include "where.ixx"