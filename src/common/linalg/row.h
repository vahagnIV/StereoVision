//
// Created by vahagn on 11/27/19.
//

#ifndef STEREOVISION_ROW_H
#define STEREOVISION_ROW_H

#include <memory>
#include <variant>
#include "../exceptions/wrong_operand_exception.h"

namespace StereoVision {

#define DECLTYPEPlus(A, B) decltype(std::declval<A>() + std::declval<B>())
#define DECLTYPEMul(A, B) decltype(std::declval<A>() * std::declval<B>())

template<typename T>
class Row {

 public:
  Row(int length) : length_(length), data_(std::shared_ptr<T[]>(new T[length_])), out_memory_(false), span_(1) {

  }

  Row(T *data, int length, int span = 1) : length_(length), out_memory_(true), span_(span), data_(data) {

  }

  const T *Data() const {
    return out_memory_ ? std::get<T *>(data_) : std::get<std::shared_ptr<T[]> >(data_).get();
  }

  T *Data() {
    return out_memory_ ? std::get<T *>(data_) : std::get<std::shared_ptr<T[]> >(data_).get();
  }

  unsigned int Length() const { return length_; }

  const T & operator[](int i) const { return Data()[i * span_]; }

  T & operator[](int i) { return Data()[i * span_]; }

  template<typename K>
  auto operator+(const Row<K> & other) const -> Row<DECLTYPEPlus(T, K)> {
    if (length_ != other.Length())
      throw WrongOperandException("Trying to add two rows of different size.");

    Row<DECLTYPEPlus(T, K)> result(length_);
    for (int i = 0; i < Length(); ++i) {
      result[i] = (*this)[i] + other[i];
    }
    return result;
  }

  template<typename K>
  auto operator-(const Row<K> & other) const -> Row<DECLTYPEPlus(T, K)> {
    if (length_ != other.Length())
      throw WrongOperandException("Trying to add two rows of different size.");

    Row<DECLTYPEPlus(T, K)> result(length_);
    for (int i = 0; i < Length(); ++i) {
      result[i] = (*this)[i] - other[i];
    }
    return result;
  }

  template<typename K>
  auto operator*(const Row<K> & other) const -> Row<DECLTYPEMul(T, K)> {
    if (length_ != other.Length())
      throw WrongOperandException("Trying to add two rows of different size.");

    Row<DECLTYPEMul(T, K)> result(length_);
    for (int i = 0; i < Length(); ++i) {
      result[i] = (*this)[i] * other[i];
    }
    return result;
  }

  template<typename K>
  auto dot(const Row<K> & other) const -> DECLTYPEMul(T, K) {
    if (length_ != other.Length())
      throw WrongOperandException("Trying to add two rows of different size.");

    DECLTYPEMul(T, K) result = 0;

    for (int i = 0; i < Length(); ++i) {
      result += (*this)[i] * other[i];
    }
    return result;
  }

 private:
  unsigned int length_;
  std::variant<std::shared_ptr<T[]>, T *> data_;
  bool out_memory_;
  int span_;

};

template<typename T>
std::ostream & operator<<(std::ostream & os, const Row<T> row) {
  for (int i = 0; i < row.Length(); ++i) {
    os << (row[i]) << "\t";
  }
  return os;
}

}

#endif //STEREOVISION_ROW_H
