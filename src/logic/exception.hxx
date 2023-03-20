#pragma once

#include <exception>
#include <string>

class FileLogicException : public std::exception {
 public:
  FileLogicException(const char* msg) : msg_(msg) {
  }

  const char* what() const noexcept override {
    return msg_.c_str();
  }

 private:
  std::string msg_;
};
