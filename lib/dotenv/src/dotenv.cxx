#include <dotenv.hxx>
#include <fstream>

void dotenv::config(const char* path) {
  std::ifstream file;
  file.open(path);
  if (!file.is_open()) {
    throw std::runtime_error("open config file failed");
  }
  std::string line;
  while (std::getline(file, line)) {
    std::string::size_type pos = line.find('=');
    if (pos != std::string::npos && pos > 0) {
      line[pos] = '\0';
      if (setenv(line.c_str(), line.c_str() + pos + 1, 0) == 0) {
        continue;
      }
    }
    throw std::runtime_error("config file invalid format");
  }
}

const char* dotenv::env(const char* name) {
  return getenv(name);
}