#include <orm/query_where.hxx>

QueryWhere::QueryWhere(std::string sql, std::vector<MYSQL_BIND> binds)
    : sql_(sql), binds_(binds) {
}

void QueryWhere::release() {
  for (auto& bind : binds_) {
    delete[](char*) bind.buffer;
  }
}

size_t QueryWhere::size() const {
  return binds_.size();
}

const std::string& QueryWhere::sql() const {
  return sql_;
}

const std::vector<MYSQL_BIND>& QueryWhere::binds() const {
  return binds_;
}

QueryWhere::operator bool() const {
  return sql_.empty();
}

QueryWhere& QueryWhere::operator||(const QueryWhere& q) {
  sql_ = "(" + sql_ + ") or (" + q.sql_ + ")";
  binds_.insert(this->binds_.end(), q.binds_.begin(), q.binds_.end());
  return *this;
}

QueryWhere& QueryWhere::operator&&(const QueryWhere& q) {
  sql_ = "(" + sql_ + ") and (" + q.sql_ + ")";
  binds_.insert(this->binds_.end(), q.binds_.begin(), q.binds_.end());
  return *this;
}

std::ostream& QueryWhere::operator>>(std::ostream& out) const {
  out << sql_;
  return out;
}
