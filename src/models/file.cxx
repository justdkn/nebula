#include "file.hxx"
#include <dotenv.hxx>

File::File(Driver& driver)
    : Model(driver, "file"),
      id("id"),
      name("name"),
      uuid("uuid"),
      type("type"),
      parent_uuid("parent_uuid") {
}

File::~File() {
}

const UBigIntField* File::primary_key() const {
  return &id;
}

const std::vector<const FieldBase*> File::fields() const {
  return {&id, &uuid, &parent_uuid, &type, &name};
}
