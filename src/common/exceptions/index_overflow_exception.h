//
// Created by vahagn on 12/2/19.
//

#ifndef STEREOVISION_COMMON_EXCEPTIONS_INDEX_OVERFLOW_EXCEPTION_H_
#define STEREOVISION_COMMON_EXCEPTIONS_INDEX_OVERFLOW_EXCEPTION_H_

#include <exception>
#include <string>

namespace StereoVision {

class IndexOverflowException : std::exception {
 public:
  explicit IndexOverflowException(const std::string &message) : message_(message) {};
  const char *what() const noexcept override {
    return message_.c_str();
  }
 private:
  std::string message_;

};
}

#endif //STEREOVISION_COMMON_EXCEPTIONS_INDEX_OVERFLOW_EXCEPTION_H_
