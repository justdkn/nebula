#pragma once

#include <string_view>
#include "driver.hxx"

class Statment {
 public:
  Statment();
  explicit Statment(Driver &driver);
  Statment(const Statment &)           = delete;
  Statment operator=(const Statment &) = delete;
  ~Statment();

 public:
  const Driver *driver() const;
  bool init(Driver &driver);
  void close();
  bool is_open() const;
  int prepare(std::string_view query);
  int execute();
  int fetch();
  int fetch_column(MYSQL_BIND *bind, unsigned int column, unsigned long offset);
  int store_result();
  unsigned long param_count();
  bool attr_set(enum enum_stmt_attr_type attr_type, const void *attr);
  bool attr_get(enum enum_stmt_attr_type attr_type, void *attr);
  int bind_param(MYSQL_BIND *bind);
  int bind_result(MYSQL_BIND *bind);
  bool reset();
  bool free_result();
  bool send_long_data(unsigned int param_number, const char *data,
                      unsigned long length);
  MYSQL_RES *result_metadata();
  MYSQL_RES *param_metadata();
  unsigned int error() const;
  const char *error_str() const;
  const char *sqlstate();
  MYSQL_ROW_OFFSET row_seek(MYSQL_ROW_OFFSET offset);
  MYSQL_ROW_OFFSET row_tell();
  void data_seek(uint64_t offset);
  uint64_t num_rows();
  uint64_t affected_rows();
  uint64_t insert_id();
  unsigned int field_count();
  int next_result();

 private:
  MYSQL_STMT *stmt_;
  Driver *driver_;
};