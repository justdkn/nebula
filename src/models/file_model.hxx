#pragma once

#include <orm/orm.hxx>

class FileModel : public Model {
 public:
  enum class Type {
    Folder,
    File,
  };

 public:
  FileModel(Driver& driver);
  virtual ~FileModel();

 public:
  virtual const UBigIntField* primary_key() const;
  virtual const std::vector<const FieldBase*> fields() const;

 public:
  UBigIntField id;
  StringField name;
  UUIDField uuid;
  TinyEnumField<Type> type;
  // TinyIntField type;
  UUIDField parent_uuid;
};