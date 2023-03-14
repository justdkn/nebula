#pragma once

#include <exception>
#include <string>

class OrmException : public std::exception {
 public:
  OrmException(const char* msg) : msg_(msg) {
  }

  const char* what() const noexcept override {
    return msg_.c_str();
  }

 private:
  std::string msg_;
};

class UUIDFormatException : public std::exception {};