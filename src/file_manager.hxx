#pragma once

#include <vector>
#include <optional>
#include <string_view>
#include "models/file_model.hxx"

namespace FileManager {
std::optional<FileModel> get(UUID uuid);
std::optional<FileModel> get(std::optional<UUID> parent_uuid, const char* name);
std::vector<FileModel> list(std::optional<UUID> parent_uuid);

bool exists(UUID uuid);
bool exists(std::optional<UUID> uuid);
bool exists(std::optional<UUID> parent_uuid, const char* name);
bool children_exists(std::optional<UUID> parent_uuid);

std::optional<FileModel> create(std::optional<UUID> parent_uuid,
                                const char* name, FileModel::Type type);
std::optional<FileModel> create_file(std::optional<UUID> parent_uuid,
                                     const char* name);
std::optional<FileModel> create_folder(std::optional<UUID> parent_uuid,
                                       const char* name);
bool rename(std::optional<UUID> parent_uuid, const char* src, const char* dst);
bool move(UUID uuid, std::optional<UUID> parent_uuid, const char* name);
bool remove(std::optional<UUID> parent_uuid, const char* name);
std::string get_file_path(std::optional<FileModel> file);

}  // namespace FileManager
