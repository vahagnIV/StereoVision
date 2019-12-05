//
// Created by vahagn on 12/4/19.
//

#include <algorithm>
#include <numeric>
#include "mul_index_pair.h"

namespace StereoVision {
namespace linalg {

MulIndexPair::MulIndexPair(const Shape & shape1,
                           const Shape & shape2,
                           const std::vector<IndexPair> & bound_indices)
    : SimpleIndex(InitJoinedShape(shape1, shape2, bound_indices)), index1_(), index2_() {
  for (int i = 0; i < shape1.size(); ++i) {
    index1_.GetIndexPtrs().push_back(index_values_ptr_[i]);
  }
  for (int i = 0; i < shape2.size(); ++i) {
    auto x = std::find_if(bound_indices.begin(),
                          bound_indices.end(),
                          [&](const IndexPair & elem) { return elem.second == i; });
    if (x != bound_indices.end())
      index2_.GetIndexPtrs().push_back(index_values_ptr_[(*x).first]);
    else
      index2_.GetIndexPtrs().push_back(index_values_.data() + (index1_.size() + index2_.GetIndexPtrs().size() - 1));
  }
}

const Shape MulIndexPair::InitJoinedShape(const Shape & shape1,
                                          const Shape & shape2,
                                          const std::vector<IndexPair> & bound_indices) const {
  Shape joined_shape = shape1;

  for (int i = 0; i < shape2.size(); ++i) {
    if (std::find_if(bound_indices.begin(),
                     bound_indices.end(),
                     [&](const IndexPair & elem) { return elem.second == i; }) == bound_indices.end())
      joined_shape.push_back(shape2[i]);
  }

  return joined_shape;
}

}
}