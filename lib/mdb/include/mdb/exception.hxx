#pragma once

#include <exception>
#include <string>

class StatmentException : public std::exception {
 public:
  StatmentException(unsigned int code) : code_(code) {
  }

  unsigned int code() const noexcept {
    return code_;
  }

 private:
  unsigned int code_;
};