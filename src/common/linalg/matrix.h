//
// Created by vahagn on 11/27/19.
//

#ifndef STEREOVISION_MATRIX_H
#define STEREOVISION_MATRIX_H

#include "row.h"
#include <vector>
#include <variant>

namespace StereoVision {

template<typename T>
class Matrix {
 public:
  Matrix(int rows, int cols)
      : n_rows_(rows), n_cols_(cols), data_(new T[rows * cols]) {
    for (int i = 0; i < n_rows_; ++i) {
      rows_.push_back(Row<T>(data_.get() + i * n_cols_, n_cols_));
    }
  }

  template<typename K>
  auto operator+(const Matrix<K> & other) const -> Matrix<DECLTYPEPlus(T, K)> {
    if (Rows() != other.Rows() || Cols() != other.Cols())
      throw WrongOperandException("Trying to add two matrices of different size.");

    Matrix<DECLTYPEPlus(T, K)> result(Rows(), Cols());
    for (int i = 0; i < Rows(); ++i) {
      for (int j = 0; j < Cols(); ++j) {
        result[i][j] = (*this)[i][j] + other[i][j];
      }
    }
    return result;
  }

  template<typename K>
  auto operator-(const Matrix<K> & other) const -> Matrix<DECLTYPEPlus(T, K)> {
    if (Rows() != other.Rows() || Cols() != other.Cols())
      throw WrongOperandException("Trying to add two matrices of different size.");

    Matrix<DECLTYPEPlus(T, K)> result(Rows(), Cols());
    for (int i = 0; i < Rows(); ++i) {
      for (int j = 0; j < Cols(); ++j) {
        result[i][j] = (*this)[i][j] - other[i][j];
      }
    }
    return result;
  }

  template<typename K>
  auto operator*(const Matrix<K> & other) const -> Matrix<DECLTYPEMul(T, K)> {
    if (Rows() != other.Rows() || Cols() != other.Cols())
      throw WrongOperandException("Trying to add two matrices of different size.");

    Matrix<DECLTYPEMul(T, K)> result(Rows(), Cols());
    for (int i = 0; i < Rows(); ++i) {
      for (int j = 0; j < Cols(); ++j) {
        result[i][j] = (*this)[i][j] * other[i][j];
      }
    }
    return result;
  }

  const Row<T> & operator[](int i) const { return rows_[i]; }

  Row<T> & operator[](int i) { return rows_[i]; }

  unsigned int Rows() const { return n_rows_; }
  unsigned int Cols() const { return n_cols_; }

 private:
  int n_rows_, n_cols_;
  std::shared_ptr<T[]> data_;
  std::vector<Row < T>> rows_;

};

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> matrix) {
  for (int i = 0; i < matrix.Rows(); ++i) {
    os << (matrix[i]) << "\n";
  }
  return os;
}

}

#endif //STEREOVISION_MATRIX_H
