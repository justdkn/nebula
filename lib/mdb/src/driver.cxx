#include <mdb/driver.hxx>
#include <optional>

Driver::Driver() : is_connected_(false) {
}

Driver::~Driver() {
}

bool Driver::connect(const char* host, unsigned int port, const char* usr,
                     const char* pwd, const char* db) {
  disconnect();
  if (mysql_init(&sock_) == nullptr) {
    return false;
  }
  is_connected_ = true;
  if (mysql_real_connect(&sock_, host, usr, pwd, db, port, nullptr, 0) ==
      nullptr) {
    disconnect();
    return false;
  }
  return true;
}

void Driver::disconnect() {
  if (is_connected_) {
    mysql_close(&sock_);
    is_connected_ = false;
  }
}

inline bool Driver::is_connected() const {
  return is_connected_;
}

MYSQL* Driver::sock() {
  return &sock_;
}

unsigned int Driver::error() const {
  return mysql_errno(const_cast<MYSQL*>(&sock_));
}

const char* Driver::error_str() const {
  return mysql_error(const_cast<MYSQL*>(&sock_));
}

int Driver::query(const char* query) {
  return mysql_query(&sock_, query);
}

int Driver::real_query(std::string_view query) {
  return mysql_real_query(&sock_, query.data(), query.length());
}

int Driver::transaction() {
  return real_query("START TRANSACTION");
}

int Driver::commit() {
  return mysql_commit(&sock_);
}

bool Driver::autocommit(bool auto_mode) {
  return mysql_autocommit(&sock_, auto_mode);
}

bool Driver::rollback() {
  return mysql_rollback(&sock_);
}