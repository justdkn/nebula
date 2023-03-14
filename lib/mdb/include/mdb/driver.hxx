#pragma once

#include <string_view>
#include <mysql.h>

class Driver {
 public:
  Driver();
  ~Driver();

 public:
  bool connect(const char* host, unsigned int port, const char* usr,
               const char* pwd, const char* db);
  void disconnect();
  bool is_connected() const;
  MYSQL* sock();
  unsigned int error() const;
  const char* error_str() const;
  int query(const char* query);
  int real_query(std::string_view query);
  int transaction();
  int commit();
  bool autocommit(bool auto_mode);
  bool rollback();

 private:
  bool is_connected_;
  MYSQL sock_;
};