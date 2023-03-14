#pragma once

#include <mdb/statment.hxx>
#include "query_where.hxx"
#include "model.hxx"

template <typename T>
class ModelQuery {
 public:
  ModelQuery(Driver& driver);
  ~ModelQuery();

 public:
  ModelQuery& order_by(const char* order);
  ModelQuery& limit(size_t start);
  ModelQuery& limit(size_t start, size_t count);
  ModelQuery& where(const QueryWhere* where);
  ModelQuery& query();
  bool fetch();
  const T& model() const;

 private:
  Statment stmt_;
  std::vector<MYSQL_BIND> results_;
  T model_;
  const std::vector<const FieldBase*> fields_;
  const QueryWhere* where_;
  const char* order_;
  size_t limit_start_;
  size_t limit_count_;
};

#include "model_query.ixx"