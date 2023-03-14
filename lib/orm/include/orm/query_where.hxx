#pragma once

#include <vector>
#include <string>
#include <mysql.h>

class QueryWhere {
 public:
  QueryWhere(std::string sql, std::vector<MYSQL_BIND> binds);

 public:
  void release();
  size_t size() const;
  const std::string& sql() const;
  const std::vector<MYSQL_BIND>& binds() const;

 public:
  operator bool() const;
  QueryWhere& operator||(const QueryWhere& q);
  QueryWhere& operator&&(const QueryWhere& q);
  std::ostream& operator>>(std::ostream& out) const;

 private:
  std::string sql_;
  std::vector<MYSQL_BIND> binds_;
};
