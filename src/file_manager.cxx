#include "file_manager.hxx"
#include <optional>
#include <orm/orm.hxx>
#include "db.hxx"
#include "exception.hxx"
#include "models/file_model.hxx"
#include <iostream>

enum class Type {
  Folder,
  File,
};

namespace file_manager {
std::optional<FileModel> get(UUID uuid) {
  return Query<FileModel>(get_db()).get(EQ("uuid", uuid));
}
std::optional<FileModel> create_folder(std::optional<UUID> parent_uuid,
                                       const char* name) {
  std::optional<FileModel> parent_folder;
  if (parent_uuid) {
    parent_folder = get(parent_uuid.value());
    if (!parent_folder)
      throw FileManagerException("parent folder is not exists");
  }
  if (Query<FileModel>(get_db()).get(EQ("parent_uuid", parent_uuid) &&
                                     EQ("name", name)))
    throw FileManagerException("file exists");
  FileModel file(get_db());
  file.parent_uuid = parent_uuid;
  file.uuid        = UUID();
  file.uuid->generate();
  file.name = name;
  file.type = FileModel::Type::Folder;
  if (!file.save()) return std::nullopt;
  return file;
}
};  // namespace file_manager