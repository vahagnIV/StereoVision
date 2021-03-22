//
// Created by vahagn on 12/2/19.
//

#include <cstdarg>
#include "simple_index.h"

namespace StereoVision {
namespace linalg {

SimpleIndex::SimpleIndex(const Shape & weights)
    : weights_(weights), index_values_(weights.size(), 0), is_invalid_(false) {

  if (weights_.empty())
    index_values_.push_back(0);
  for (int i = 0; i < index_values_.size(); ++i) {
    index_values_ptr_.push_back(index_values_.data() + i);
  }

}

iIndex & SimpleIndex::operator+=(int number) {
  if (weights_.empty()) {
    is_invalid_ = true;
    return *this;
  }

  int residual, tmp;
  for (int i = index_values_.size() - 1; i >= 0; --i) {
    if (weights_[i] == 1) {
      if (i == 0)
        is_invalid_ = true;
      continue;
    }

    residual = number % weights_[i];

    tmp = index_values_[i] + residual;

    if (tmp >= weights_[i])
      if (i > 0)
        index_values_[i - 1] += 1;
      else {
        is_invalid_ = true;
        return *this;
      }

    index_values_[i] = tmp % weights_[i];
    number = (number - residual) / weights_[i];

  }
  return *this;
}

iIndex & SimpleIndex::operator++() {
  return *this += 1;
};

bool SimpleIndex::IsValid() const {
  return !is_invalid_;
}

SimpleIndex & SimpleIndex::operator()(const std::vector<unsigned> & new_values) {
  if (new_values.size() != index_values_.size())
    throw IndexOverflowException("");
  index_values_ = new_values;
  return *this;
}

}
}