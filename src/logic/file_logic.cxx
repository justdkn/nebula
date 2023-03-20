#include "file_logic.hxx"
#include <optional>
#include <orm/orm.hxx>
#include "../common/db.hxx"
#include "exception.hxx"
#include <iostream>
#include <dotenv.hxx>

namespace file_logic {
std::optional<File> create(std::optional<UUID> parent_uuid, const char* name,
                           File::Type type) {
  std::optional<File> parent_folder;
  if (!exists(parent_uuid))
    throw FileLogicException("parent folder is not exists");
  if (Query<File>(get_db()).get(EQ("parent_uuid", parent_uuid) &&
                                EQ("name", name)))
    throw FileLogicException("file exists");
  File file(get_db());
  file.parent_uuid = parent_uuid;
  file.uuid        = UUID();
  file.uuid->generate();
  file.name = name;
  file.type = type;
  if (!file.save()) return std::nullopt;
  return file;
}

std::optional<File> create_file(std::optional<UUID> parent_uuid,
                                const char* name) {
  return create(parent_uuid, name, File::Type::File);
}

std::optional<File> create_folder(std::optional<UUID> parent_uuid,
                                  const char* name) {
  return create(parent_uuid, name, File::Type::Folder);
}

bool remove(UUID uuid) {
  std::optional<File> file = get(uuid);
  if (!file) return true;
  if (file->type.value() == File::Type::Folder && empty(file->uuid))
    throw FileLogicException("folder is not empty");
  return file->remove();
}

bool remove(std::optional<UUID> parent_uuid, const char* name) {
  std::optional<File> file = get(parent_uuid, name);
  if (!file) return true;
  if (file->type.value() == File::Type::Folder && empty(file->uuid))
    throw FileLogicException("folder is not empty");
  return file->remove();
}

bool move(std::optional<UUID> uuid, std::optional<UUID> parent_uuid) {
  std::optional<File> file = get(uuid);
  if (!file) throw FileLogicException("file is not exists");
  if (file->parent_uuid == parent_uuid) return true;
  if (!exists(parent_uuid))
    throw FileLogicException("parent folder is not exists");
  if (exists(parent_uuid, file->name.value().c_str()))
    throw FileLogicException("parent folder is not exists");
  file->parent_uuid = parent_uuid;
  return file->save();
}

bool move(std::optional<UUID> uuid, std::optional<UUID> parent_uuid,
          const char* name) {
  std::optional<File> file = get(uuid);
  if (!file) throw FileLogicException("file is not exists");
  if (!exists(parent_uuid))
    throw FileLogicException("parent folder is not exists");
  if (exists(parent_uuid, name))
    throw FileLogicException("parent folder is not exists");
  file->parent_uuid = parent_uuid;
  file->name        = name;
  return file->save();
}

std::optional<File> get(UUID uuid) {
  return Query<File>(get_db()).get(EQ("uuid", uuid));
}

std::optional<File> get(std::optional<UUID> uuid) {
  return uuid ? get(uuid.value()) : std::nullopt;
}

std::optional<File> get(std::optional<UUID> parent_uuid, const char* name) {
  return Query<File>(get_db()).get(EQ("parent_uuid", parent_uuid) &&
                                   EQ("name", name));
}

std::vector<File> list(std::optional<UUID> parent_uuid) {
  if (!exists(parent_uuid))
    throw FileLogicException("parent folder is not exists");
  return Query<File>(get_db()).get_all(EQ("parent_uuid", parent_uuid));
}

bool exists(UUID uuid) {
  return get(uuid).has_value();
}

bool exists(std::optional<UUID> uuid) {
  return uuid.has_value() ? exists(uuid.value()) : true;
}

bool exists(std::optional<UUID> parent_uuid, const char* name) {
  return get(parent_uuid, name).has_value();
}

bool empty(std::optional<UUID> parent_uuid) {
  return Query<File>(get_db()).get(EQ("parent_uuid", parent_uuid)).has_value();
}
};  // namespace file_logic