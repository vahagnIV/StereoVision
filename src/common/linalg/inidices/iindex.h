//
// Created by vahagn on 12/5/19.
//

#ifndef STEREOVISION_I_INDEX_H
#define STEREOVISION_I_INDEX_H

#include <cstddef>
#include <vector>
#include <ostream>
namespace StereoVision {
namespace linalg {

typedef unsigned int index_t;

class iIndex {
 public:
  virtual const index_t operator[](int idx) const { return *index_values_ptr_[idx]; }
  virtual index_t & operator[](int idx) { return *index_values_ptr_[idx]; }
  virtual const size_t size() const { return index_values_ptr_.size(); }
  std::vector<index_t *> & GetIndexPtrs() { return index_values_ptr_; }
 protected:
  std::vector<index_t *> index_values_ptr_;

};

std::ostream & operator<<(std::ostream & os, const iIndex & indices);


}
}

#endif //STEREOVISION_I_INDEX_H
