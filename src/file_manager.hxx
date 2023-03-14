#pragma once

#include <vector>
#include <optional>
#include <string_view>
#include "models/file_model.hxx"

namespace file_manager {

std::optional<FileModel> get(UUID uuid);
std::optional<FileModel> create_folder(std::optional<UUID> parent_uuid,
                                       const char* name);
std::vector<FileModel> folder_list(std::optional<UUID> parent_uuid);
};  // namespace file_manager