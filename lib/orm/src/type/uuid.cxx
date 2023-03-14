#include <uuid/uuid.h>
#include <cstring>
#include <orm/type/uuid.hxx>
#include <orm/exception.hxx>

UUID::UUID() {
  clear();
}

UUID::UUID(const uuid_t uuid) {
  uuid_copy(uuid_, uuid);
}

UUID::UUID(const char* uuid) {
  if (uuid_parse(uuid, uuid_) != 0) throw UUIDFormatException();
}

UUID::UUID(std::string_view uuid) {
  if (uuid_parse(uuid.data(), uuid_) != 0) throw UUIDFormatException();
}

UUID::UUID(const UUID& uuid) {
  uuid_copy(uuid_, uuid.uuid_);
}

void UUID::generate() {
  uuid_generate(uuid_);
}

void UUID::clear() {
  uuid_clear(uuid_);
}

int UUID::compare(const UUID& uuid) const {
  return uuid_compare(uuid_, uuid.uuid_);
}

bool UUID::is_null() const {
  return uuid_is_null(uuid_);
}

std::string UUID::to_string() const {
  uuid_string_t uuid;
  uuid_unparse(uuid_, uuid);
  return uuid;
}

const uuid_t& UUID::uuid() const {
  return uuid_;
}

UUID& UUID::operator=(const char* uuid) {
  if (uuid_parse(uuid, uuid_) != 0) throw UUIDFormatException();
  return *this;
}

UUID& UUID::operator=(std::string_view s) {
  return operator=(s.data());
}

UUID& UUID::operator=(const uuid_t uuid) {
  uuid_copy(uuid_, uuid);
  return *this;
}

std::ostream& UUID::operator>>(std::ostream& out) const {
  out << to_string();
  return out;
}

std::ostream& operator<<(std::ostream& out, const UUID& uuid) {
  return uuid >> out;
}