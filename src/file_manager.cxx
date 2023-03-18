#include "file_manager.hxx"
#include <optional>
#include <orm/orm.hxx>
#include "db.hxx"
#include "exception.hxx"
#include "models/file.hxx"
#include <iostream>
#include <dotenv.hxx>

std::optional<File> FileManager::get(UUID uuid) {
  return Query<File>(get_db()).get(EQ("uuid", uuid));
}

std::optional<File> FileManager::get(std::optional<UUID> parent_uuid,
                                     const char* name) {
  return Query<File>(get_db()).get(EQ("parent_uuid", parent_uuid) &&
                                   EQ("name", name));
}

std::vector<File> FileManager::list(std::optional<UUID> parent_uuid) {
  if (!exists(parent_uuid))
    throw FileManagerException("parent folder is not exists");
  return Query<File>(get_db()).get_all(EQ("parent_uuid", parent_uuid));
}

bool FileManager::exists(UUID uuid) {
  return get(uuid).has_value();
}

bool FileManager::exists(std::optional<UUID> uuid) {
  return uuid.has_value() ? exists(uuid.value()) : true;
}

bool FileManager::exists(std::optional<UUID> parent_uuid, const char* name) {
  return get(parent_uuid, name).has_value();
}

bool FileManager::children_exists(std::optional<UUID> parent_uuid) {
  return Query<File>(get_db()).get(EQ("parent_uuid", parent_uuid)).has_value();
}

std::optional<File> FileManager::create(std::optional<UUID> parent_uuid,
                                        const char* name, File::Type type) {
  std::optional<File> parent_folder;
  if (!exists(parent_uuid))
    throw FileManagerException("parent folder is not exists");
  if (Query<File>(get_db()).get(EQ("parent_uuid", parent_uuid) &&
                                EQ("name", name)))
    throw FileManagerException("file exists");
  File file(get_db());
  file.parent_uuid = parent_uuid;
  file.uuid        = UUID();
  file.uuid->generate();
  file.name = name;
  file.type = type;
  if (!file.save()) return std::nullopt;
  return file;
}

std::optional<File> FileManager::create_file(std::optional<UUID> parent_uuid,
                                             const char* name) {
  return create(parent_uuid, name, File::Type::File);
}

std::optional<File> FileManager::create_folder(std::optional<UUID> parent_uuid,
                                               const char* name) {
  return create(parent_uuid, name, File::Type::Folder);
}

bool FileManager::rename(std::optional<UUID> parent_uuid, const char* src,
                         const char* dst) {
  if (!exists(parent_uuid))
    throw FileManagerException("parent folder is not exists");
  std::optional<File> file = get(parent_uuid, src);
  if (!file) throw FileManagerException("src file is not exists");
  if (exists(parent_uuid, dst))
    throw FileManagerException("dst file is exists");
  file->name = dst;
  return file->save();
}

bool FileManager::remove(std::optional<UUID> parent_uuid, const char* name) {
  std::optional<File> file = get(parent_uuid, name);
  if (!file) return true;
  if (file->type.value() == File::Type::Folder && children_exists(file->uuid))
    throw FileManagerException("folder is not empty");
  return file->remove();
}

bool FileManager::move(UUID uuid, std::optional<UUID> parent_uuid,
                       const char* name) {
  std::optional<File> file = get(uuid);
  if (!file) throw FileManagerException("file is not exists");
  if (!exists(parent_uuid))
    throw FileManagerException("parent folder is not exists");
  if (exists(parent_uuid, name))
    throw FileManagerException("parent folder is not exists");
  file->parent_uuid = parent_uuid;
  file->name        = name;
  return file->save();
}

std::string FileManager::get_file_path(std::optional<File> file) {
  if (!file->id || !file->type || file->type.value() != File::Type::File)
    throw FileManagerException("invalid file");
  std::stringstream ss;
  ss << dotenv::env("FILE_MANAGER_ROOT") << file->id.value() << ".dat";
  return ss.str();
}