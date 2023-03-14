#include "model_query.hxx"
#include <sstream>
#include <orm/exception.hxx>

template <typename T>
ModelQuery<T>::ModelQuery(Driver& driver)
    : stmt_(driver),
      model_(driver),
      fields_(model_.fields()),
      order_(nullptr),
      limit_start_(SIZE_MAX),
      limit_count_(SIZE_MAX),
      where_(nullptr) {
  if (fields_.empty()) throw OrmException("fields is empty");
}

template <typename T>
ModelQuery<T>::~ModelQuery() {
  for (auto& result : results_) {
    if (result.buffer) delete[](char*) result.buffer;
  }
}

template <typename T>
ModelQuery<T>& ModelQuery<T>::order_by(const char* order) {
  order_ = order;
  return *this;
}

template <typename T>
ModelQuery<T>& ModelQuery<T>::limit(size_t start) {
  limit_start_ = start;
  return *this;
}

template <typename T>
ModelQuery<T>& ModelQuery<T>::limit(size_t start, size_t count) {
  limit_start_ = start;
  limit_count_ = count;
  return *this;
}

template <typename T>
ModelQuery<T>& ModelQuery<T>::where(const QueryWhere* where) {
  where_ = where;
  return *this;
}

#include <iostream>
template <typename T>
ModelQuery<T>& ModelQuery<T>::query() {
  // 构建SQL语句
  std::stringstream ss;
  ss << "SELECT `" << fields_[0]->name() << "`";
  for (auto i = 1; i < fields_.size(); ++i) {
    ss << ",`" << fields_[i]->name() << "`";
  }
  ss << " FROM `" << model_.table_name() << "`";
  if (where_ != nullptr) ss << " WHERE " << where_->sql();
  if (order_ != nullptr) ss << " ORDER BY " << order_;
  if (limit_start_ != SIZE_MAX) {
    ss << " LIMIT " << limit_start_;
    if (limit_count_ != SIZE_MAX) ss << ", " << limit_count_;
  }
  // 解析SQL语句和绑定参数与结果数据对象
  std::cout << ss.str() << std::endl;
  if (stmt_.prepare(ss.str()) != 0) throw OrmException(stmt_.error_str());
  if (stmt_.param_count() > 0) {
    if (stmt_.param_count() != where_->size())
      throw OrmException("param count not equal");
    MYSQL_BIND* params = const_cast<MYSQL_BIND*>(where_->binds().data());
    if (stmt_.bind_param(params) != 0) throw OrmException(stmt_.error_str());
  }
  results_.resize(fields_.size());
  for (auto i = 0; i < results_.size(); ++i) {
    fields_[i]->to_result(results_[i]);
  }
  if (stmt_.bind_result(results_.data()) != 0)
    throw OrmException(stmt_.error_str());
  if (stmt_.execute() != 0) throw OrmException(stmt_.error_str());
  if (stmt_.store_result() != 0) throw OrmException(stmt_.error_str());
  if (fields_.size() != stmt_.field_count())
    throw OrmException("field count not equal");
  return *this;
}

template <typename T>
bool ModelQuery<T>::fetch() {
  int ret = stmt_.fetch();
  if (ret != 0 && ret != MYSQL_DATA_TRUNCATED) return false;
  for (auto i = 0; i < results_.size(); ++i) {
    if (results_[i].buffer_length < results_[i].length_value) {
      delete[](char*) results_[i].buffer;
      results_[i].buffer        = nullptr;
      results_[i].buffer        = new char[results_[i].length_value];
      results_[i].buffer_length = results_[i].length_value;
      if (stmt_.fetch_column(&results_[i], i, 0) != 0)
        throw OrmException("fetch_column failed");
      if (stmt_.bind_result(results_.data()) != 0)
        throw OrmException("bind result failed");
    }
    const_cast<FieldBase*>(fields_[i])->from_result(results_[i]);
  }
  return true;
}

template <typename T>
const T& ModelQuery<T>::model() const {
  return model_;
}