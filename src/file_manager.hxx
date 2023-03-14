#pragma once

#include <optional>
#include <string_view>
#include "models/file_model.hxx"

namespace file_manager {

enum {
  FILE_TYPE_FOLDER,
  FILE_TYPE_FILE,
};

std::optional<FileModel> get(UUID uuid);
std::optional<FileModel> create_folder(std::optional<UUID> parent_uuid,
                                       const char* name);
};  // namespace file_manager