//
// Created by vahagn on 12/2/19.
//

#include "tensor_indices.h"

namespace StereoVision {
namespace linalg {
TensorIndices &TensorIndices::operator+=(int number) {
  for (int i = index_values_.size() - 1; i >= 0; --i) {
    int residual = number % weights_[i];
    int tmp = index_values_[i] + residual;
    if (tmp >= weights_[i])
      if (i > 0)
        index_values_[i - 1] += 1;
      else
        throw IndexOverflowException("Invalid operation on index");
    index_values_[i] = tmp % weights_[i];
    number = (number - residual) / weights_[i];

  }
  return *this;
}

TensorIndices &TensorIndices::operator++() {
  return *this += 1;
};

const unsigned int &TensorIndices::operator[](int idx) const {
  return index_values_[idx];
}

const size_t TensorIndices::size() const {
  return index_values_.size();
}

std::ostream &operator<<(std::ostream &os, const TensorIndices indices) {
  for (int i = 0; i < indices.size(); ++i) {
    os << indices[i] << '\t';
  }

  return os;
}

}
}