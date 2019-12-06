//
// Created by vahagn on 12/5/19.
//

#ifndef STEREOVISION_SUM_INDEX_PAIR_H
#define STEREOVISION_SUM_INDEX_PAIR_H

#include "mul_index_pair.h"
namespace StereoVision {
namespace linalg {

class SumIndexPair : public MulIndexPair {
 public:
  SumIndexPair(const Shape & shape1, const Shape & shape2, const std::vector<IndexPair> & bound_indices);
  virtual const index_t operator[](int idx) const override { return *valid_indices_[idx]; }
  virtual index_t & operator[](int idx) { return *valid_indices_[idx]; }
  virtual const size_t size() const { return valid_indices_.size(); }
  virtual const Shape & GetShape() const override { return valid_shape_; }
  std::vector<index_t *> & GetIndexPtrs() { return valid_indices_; }
 protected:
  std::vector<index_t *> valid_indices_;
  Shape valid_shape_;
};

}
}

#endif //STEREOVISION_SUM_INDEX_PAIR_H
