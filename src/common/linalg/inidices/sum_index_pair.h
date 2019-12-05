//
// Created by vahagn on 12/5/19.
//

#ifndef STEREOVISION_SUM_INDEX_PAIR_H
#define STEREOVISION_SUM_INDEX_PAIR_H

#include "mul_index_pair.h"
namespace StereoVision {
namespace linalg {

class SumIndexPair : public MulIndexPair {
  SumIndexPair(const Shape & shape1, const Shape & shape2, const std::vector<IndexPair> & bound_indices);
 protected:
  std::vector<index_t> valid_indices_;
  Shape valid_shape_;

};

}
}

#endif //STEREOVISION_SUM_INDEX_PAIR_H
