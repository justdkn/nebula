#include <optional>
#include <sstream>
#include "mdb/statment.hxx"
#include "query.hxx"
#include "exception.hxx"
#include "model_query.hxx"

template <class T>
Query<T>::Query(Driver& driver)
    : driver_(driver),
      order_(nullptr),
      limit_start_(SIZE_MAX),
      limit_count_(SIZE_MAX) {
}

template <class T>
Query<T>::~Query() {
}

template <class T>
Query<T>& Query<T>::order_by(const char* order) {
  order_ = order;
  return *this;
}

template <class T>
Query<T>& Query<T>::limit(size_t start) {
  limit_start_ = start;
  return *this;
}

template <class T>
Query<T>& Query<T>::limit(size_t start, size_t count) {
  limit_start_ = start;
  limit_count_ = count;
  return *this;
}

template <class T>
std::optional<T> Query<T>::get(const QueryWhere where) {
  ModelQuery<T> query(driver_);
  if (!query.limit(limit_start_, limit_count_)
           .order_by(order_)
           .where(&where)
           .query()
           .fetch()) {
    return std::nullopt;
  }
  return query.model();
}

template <class T>
std::vector<T> Query<T>::get_all(const QueryWhere where) {
  ModelQuery<T> query(driver_);
  query.limit(limit_start_, limit_count_).order_by(order_).query();
  std::vector<T> datas;
  while (query.fetch()) {
    datas.push_back(query.model());
  }
  return datas;
}
