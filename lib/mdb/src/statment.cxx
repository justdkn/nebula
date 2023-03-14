#include <_types/_uint64_t.h>
#include <mdb/statment.hxx>
#include <mdb/exception.hxx>

Statment::Statment() : stmt_(nullptr) {
}

Statment::Statment(Driver &driver) : stmt_(nullptr) {
  init(driver);
}

Statment::~Statment() {
  close();
}

const Driver *Statment::driver() const {
  return driver_;
}

bool Statment::init(Driver &driver) {
  close();
  driver_ = &driver;
  stmt_   = mysql_stmt_init(driver.sock());
  return stmt_ != nullptr;
}

bool Statment::is_open() const {
  return stmt_ != nullptr;
}

void Statment::close() {
  if (stmt_ != nullptr) {
    mysql_stmt_close(stmt_);
    stmt_   = nullptr;
    driver_ = nullptr;
  }
}

int Statment::prepare(std::string_view query) {
  return mysql_stmt_prepare(stmt_, query.data(), query.length());
}

int Statment::execute() {
  return mysql_stmt_execute(stmt_);
}

int Statment::fetch() {
  return mysql_stmt_fetch(stmt_);
}

unsigned long Statment::param_count() {
  return mysql_stmt_param_count(stmt_);
}

int Statment::store_result() {
  return mysql_stmt_store_result(stmt_);
}

int Statment::fetch_column(MYSQL_BIND *bind, unsigned int column,
                           unsigned long offset) {
  return mysql_stmt_fetch_column(stmt_, bind, column, offset);
}

bool Statment::attr_set(enum enum_stmt_attr_type attr_type, const void *attr) {
  return mysql_stmt_attr_set(stmt_, attr_type, attr);
}

bool Statment::attr_get(enum enum_stmt_attr_type attr_type, void *attr) {
  return mysql_stmt_attr_get(stmt_, attr_type, attr);
}

int Statment::bind_param(MYSQL_BIND *bind) {
  return mysql_stmt_bind_param(stmt_, bind);
}

int Statment::bind_result(MYSQL_BIND *bind) {
  return mysql_stmt_bind_result(stmt_, bind);
}

bool Statment::reset() {
  return mysql_stmt_reset(stmt_);
}

bool Statment::free_result() {
  return mysql_stmt_free_result(stmt_);
}

bool Statment::send_long_data(unsigned int param_number, const char *data,
                              unsigned long length) {
  return mysql_stmt_send_long_data(stmt_, param_number, data, length);
}

MYSQL_RES *Statment::result_metadata() {
  return mysql_stmt_result_metadata(stmt_);
}

MYSQL_RES *Statment::param_metadata() {
  return mysql_stmt_param_metadata(stmt_);
}

unsigned int Statment::error() const {
  return mysql_stmt_errno(stmt_);
}

const char *Statment::error_str() const {
  return mysql_stmt_error(stmt_);
}

const char *Statment::sqlstate() {
  return mysql_stmt_sqlstate(stmt_);
}

MYSQL_ROW_OFFSET Statment::row_seek(MYSQL_ROW_OFFSET offset) {
  return mysql_stmt_row_seek(stmt_, offset);
}

MYSQL_ROW_OFFSET Statment::row_tell() {
  return mysql_stmt_row_tell(stmt_);
}

void Statment::data_seek(uint64_t offset) {
  return mysql_stmt_data_seek(stmt_, offset);
}

uint64_t Statment::num_rows() {
  return mysql_stmt_num_rows(stmt_);
}

uint64_t Statment::affected_rows() {
  return mysql_stmt_affected_rows(stmt_);
}

uint64_t Statment::insert_id() {
  return mysql_stmt_insert_id(stmt_);
}

unsigned int Statment::field_count() {
  return mysql_stmt_field_count(stmt_);
}

int Statment::next_result() {
  return mysql_stmt_next_result(stmt_);
}