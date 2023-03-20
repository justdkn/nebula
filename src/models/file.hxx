#pragma once

#include <orm/orm.hxx>
#include <string>

class File : public Model {
 public:
  enum class Type : uint8_t {
    Folder,
    File,
  };

 public:
  File(Driver& driver);
  virtual ~File();

 public:
  virtual const UBigIntField* primary_key() const;
  virtual const std::vector<const FieldBase*> fields() const;

 public:
  std::string path() const;

 public:
  UBigIntField id;
  StringField name;
  UUIDField uuid;
  EnumField<Type> type;
  UUIDField parent_uuid;
};