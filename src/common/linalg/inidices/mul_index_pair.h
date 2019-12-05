//
// Created by vahagn on 12/4/19.
//

#ifndef STEREOVISION_MUL_INDEX_PAIR_H
#define STEREOVISION_MUL_INDEX_PAIR_H

#include "simple_index.h"
#include <memory>


namespace StereoVision {
namespace linalg {

typedef std::pair<unsigned, unsigned> IndexPair;

class MulIndexPair : public SimpleIndex {
 public:
  MulIndexPair(const Shape & shape1, const Shape & shape2, const std::vector<IndexPair> & bound_indices);

  const iIndex & First() const { return index1_; }
  const iIndex & Second() const { return index2_; }


 private:
  const Shape InitJoinedShape(const Shape & shape1,
                              const Shape & shape2,
                              const std::vector<IndexPair> & bound_indices) const;

  iIndex index1_;
  iIndex index2_;


};

}
}

#endif //STEREOVISION_MUL_INDEX_PAIR_H
