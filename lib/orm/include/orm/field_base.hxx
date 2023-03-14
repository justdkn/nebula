#pragma once

#include <ostream>
#include <mysql.h>

class FieldBase {
 public:
  explicit FieldBase(const char* name);
  virtual ~FieldBase();

 public:
  const char* name() const;

 public:
  virtual bool is_null() const                              = 0;
  virtual void from_result(const MYSQL_BIND& bind)          = 0;
  virtual void to_param(MYSQL_BIND& bind) const             = 0;
  virtual void to_result(MYSQL_BIND& bind) const            = 0;
  virtual std::ostream& operator>>(std::ostream& out) const = 0;

 private:
  const char* name_;
};

std::ostream& operator<<(std::ostream& out, const FieldBase& field);