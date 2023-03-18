#pragma once

namespace dotenv {
void config(const char* path = ".env");
const char* env(const char* name);
}  // namespace dotenv