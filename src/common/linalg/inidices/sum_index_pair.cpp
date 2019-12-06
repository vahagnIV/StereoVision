//
// Created by vahagn on 12/5/19.
//
#include <algorithm>
#include "sum_index_pair.h"

namespace StereoVision {
namespace linalg {

SumIndexPair::SumIndexPair(const Shape & shape1, const Shape & shape2, const std::vector<IndexPair> & bound_indices)
    : MulIndexPair(shape1, shape2, bound_indices) {

  for (int i = 0; i < shape1.size(); ++i) {
    if (std::find_if(bound_indices.begin(),
                     bound_indices.end(),
                     [&](const IndexPair & elem) { return elem.first == i; }) == bound_indices.end()) {
      valid_indices_.push_back(index_values_ptr_[i]);
      valid_shape_.push_back(shape1[i]);
    }
  }

  for (int j = 0; j < shape2.size(); ++j)
    if (std::find_if(bound_indices.begin(),
                     bound_indices.end(),
                     [&](const IndexPair & elem) { return elem.second == j; }) == bound_indices.end()) {
      valid_indices_.push_back(index_values_ptr_[j + shape1.size() - 1]);
      valid_shape_.push_back(shape2[j]);
    }

}
}
}