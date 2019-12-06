//
// Created by vahagn on 12/6/19.
//

#ifndef STEREOVISION_SINGULAR_MATRIX_EXCEPTION_H
#define STEREOVISION_SINGULAR_MATRIX_EXCEPTION_H

#include <exception>
#include <string>

namespace StereoVision {

class SingularMatrixException : std::exception {
 public:
  explicit SingularMatrixException(const std::string &message) : message_(message) {};
  const char *what() const noexcept override {
    return message_.c_str();
  }
 private:
  std::string message_;

};
}
#endif //STEREOVISION_SINGULAR_MATRIX_EXCEPTION_H
