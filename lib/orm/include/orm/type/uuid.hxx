#pragma once

#include <uuid/uuid.h>
#include <string>
#include <string_view>

class UUID {
 public:
  UUID();
  UUID(const uuid_t uuid);
  UUID(const char* uuid);
  UUID(std::string_view uuid);
  UUID(const UUID& uuid);

 public:
  void generate();
  void clear();
  int compare(const UUID& uuid) const;
  bool is_null() const;
  std::string to_string() const;
  const uuid_t& uuid() const;
  UUID& operator=(const char* s);
  UUID& operator=(std::string_view s);
  UUID& operator=(const uuid_t uuid);
  bool operator==(const UUID& uuid) const;
  bool operator!=(const UUID& uuid) const;
  std::ostream& operator>>(std::ostream& out) const;

 private:
  uuid_t uuid_;
};

std::ostream& operator<<(std::ostream& out, const UUID& uuid);