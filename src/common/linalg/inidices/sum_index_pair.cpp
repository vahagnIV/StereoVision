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
    if(std::find_if(bound_indices.begin(), bound_indices.end(),[&](const IndexPair & elem){ return elem.first == i;} )== bound_indices.end())
      valid_indices_.push_back(i);
  }
}
}
}