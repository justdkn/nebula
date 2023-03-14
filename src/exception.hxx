#pragma once

#include <exception>
#include <string>

class FileManagerException : public std::exception {
 public:
  FileManagerException(const char* msg) : msg_(msg) {
  }

  const char* what() const noexcept override {
    return msg_.c_str();
  }

 private:
  std::string msg_;
};
