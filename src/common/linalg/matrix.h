//
// Created by vahagn on 12/6/19.
//

#ifndef STEREOVISION_MATRIX_H
#define STEREOVISION_MATRIX_H
#include <exceptions/singular_matrix_exception.h>
#include "tensor.h"

namespace StereoVision {
namespace linalg {

template<typename T>
class Matrix : public Tensor<T> {
 public:
  Matrix(unsigned rows, unsigned cols) : Tensor<T>({rows, cols}) {}

  Matrix<double> Inverse() {
    // Get adjugate matrix
    Matrix<double> adjoint(this->shape_);

    for (int i = 0; i < this->shape_[0]; ++i) {
      for (int j = 0; j < this->shape_[1]; ++j) {
        Matrix<double > minor_m({this->shape_[0] - 1, this->shape_[1] -1});
        for(auto index = minor_m.GetIndex(); index.IsValid(); ++index)
        {
         // minor_m[]
        }
      }
    }
  }

  T Det() const {
    if (this->shape_[0] != this->shape_[1])
      throw WrongOperandException("Determinant is defined only for square matrices");

    Tensor<double> tmp_row(this->shape_[1]);
    Matrix<double> tmp_matrix(this->shape_[0], this->shape_[1]);

    auto index = this->GetIndex();
    this->CopyTo(tmp_matrix);


    // Partition Matrix
    for (unsigned int i = 0; i < this->shape_[0]; ++i) {
      if (tmp_matrix[index({i, i})] == 0) {
        bool swaped = false;
        for (unsigned int j = i; j < this->shape_[1]; ++j) {
          if (tmp_matrix[index({j, i})] != 0) {
            tmp_matrix[j].CopyTo(tmp_row);
            Tensor<double> row = tmp_matrix[j];
            tmp_matrix[i].CopyTo(row);
            tmp_row.CopyTo(row);
            swaped = true;
            break;
          }
        }
        if (!swaped)
          return 0;
      }
    }

    // Make it upper diagonal
    for (unsigned int k = 1; k < this->shape_[0]; ++k) {
      for (unsigned int c = 0; c < k; ++c) {
        if (tmp_matrix[index({k, c})] != 0) {
          double coefficient = (double) tmp_matrix[index] / tmp_matrix[index({c, c})];
          tmp_matrix[k] -= (tmp_matrix[c] * coefficient);
        }
      }
    }

    T result = 1;

    for (unsigned int l = 0; l < this->shape_[0]; ++l) {
      result * tmp_matrix[index({l, l})];
    }
    return result;
  }

};

}
}

#endif //STEREOVISION_MATRIX_H
