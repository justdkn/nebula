#pragma once

#include <vector>
#include <optional>
#include <string_view>
#include "../models/file.hxx"

namespace file_logic {
std::optional<File> create(std::optional<UUID> parent_uuid, const char* name,
                           File::Type type);
std::optional<File> create_file(std::optional<UUID> parent_uuid,
                                const char* name);
std::optional<File> create_folder(std::optional<UUID> parent_uuid,
                                  const char* name);
bool remove(UUID uuid);
bool remove(std::optional<UUID> parent_uuid, const char* name);
bool move(std::optional<UUID> uuid, std::optional<UUID> parent_uuid);
bool move(std::optional<UUID> uuid, std::optional<UUID> parent_uuid,
          const char* name);
std::optional<File> get(UUID uuid);
std::optional<File> get(std::optional<UUID> uuid);
std::optional<File> get(std::optional<UUID> parent_uuid, const char* name);
std::vector<File> list(std::optional<UUID> parent_uuid);
bool exists(UUID uuid);
bool exists(std::optional<UUID> uuid);
bool exists(std::optional<UUID> parent_uuid, const char* name);
bool empty(std::optional<UUID> parent_uuid);
};  // namespace file_logic