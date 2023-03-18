#pragma once

#include <vector>
#include <optional>
#include <string_view>
#include "models/file.hxx"

namespace FileManager {
std::optional<File> get(UUID uuid);
std::optional<File> get(std::optional<UUID> parent_uuid, const char* name);
std::vector<File> list(std::optional<UUID> parent_uuid);

bool exists(UUID uuid);
bool exists(std::optional<UUID> uuid);
bool exists(std::optional<UUID> parent_uuid, const char* name);
bool children_exists(std::optional<UUID> parent_uuid);

std::optional<File> create(std::optional<UUID> parent_uuid, const char* name,
                           File::Type type);
std::optional<File> create_file(std::optional<UUID> parent_uuid,
                                const char* name);
std::optional<File> create_folder(std::optional<UUID> parent_uuid,
                                  const char* name);
bool rename(std::optional<UUID> parent_uuid, const char* src, const char* dst);
bool move(UUID uuid, std::optional<UUID> parent_uuid, const char* name);
bool remove(std::optional<UUID> parent_uuid, const char* name);
std::string get_file_path(std::optional<File> file);

}  // namespace FileManager
