#include "file_model.hxx"

FileModel::FileModel(Driver& driver)
    : Model(driver, "file"),
      id("id"),
      name("name"),
      uuid("uuid"),
      type("type"),
      parent_uuid("parent_uuid") {
}

FileModel::~FileModel() {
}

const UBigIntField* FileModel::primary_key() const {
  return &id;
}

const std::vector<const FieldBase*> FileModel::fields() const {
  return {&id, &uuid, &parent_uuid, &type, &name};
}