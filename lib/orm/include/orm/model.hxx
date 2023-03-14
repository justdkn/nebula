#pragma once

#include <vector>
#include <mdb/driver.hxx>
#include "field.hxx"

class Model {
 public:
  explicit Model(Driver& driver, const char* table_name);
  virtual ~Model();

 public:
  const char* table_name() const;
  bool save();
  bool remove();
  bool update(std::vector<std::string_view> names = {});

 public:
  virtual const UBigIntField* primary_key() const            = 0;
  virtual const std::vector<const FieldBase*> fields() const = 0;

 public:
  std::ostream& operator>>(std::ostream& out) const;

 private:
  Driver driver_;
  const char* table_name_;
};

std::ostream& operator<<(std::ostream& out, const Model& model);