#pragma once

#include "model.hxx"
#include "query_where.hxx"

template <class T>
class Query {
 public:
  explicit Query(Driver& driver);
  virtual ~Query();

 public:
  Query& order_by(const char* order);
  Query& limit(size_t start);
  Query& limit(size_t start, size_t count);
  std::optional<T> get(const QueryWhere where);
  std::vector<T> get_all(const QueryWhere where);

 private:
  Driver driver_;
  const char* order_;
  size_t limit_start_;
  size_t limit_count_;
};

#include "query.ixx"