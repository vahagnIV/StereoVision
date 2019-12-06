//
// Created by vahagn on 12/6/19.
//

#ifndef STEREOVISION_MINOR_INDEX_H
#define STEREOVISION_MINOR_INDEX_H

#include "simple_index.h"

namespace StereoVision {
namespace linalg {

class MinorIndex : public iIndex {
 public:
  MinorIndex(index_t size, index_t row, index_t column);

  virtual const index_t operator[](int idx) const override;

  MinorIndex & operator()(const std::vector<unsigned> & new_values);

  iIndex & operator+=(int number);

  iIndex & operator++();

  bool IsValid() const { return minor_index_.IsValid(); }

  virtual const size_t size() const { return minor_index_.size(); }

  const SimpleIndex & GetMinorIndex() const;

 protected:
  int row_;
  int col_;
  SimpleIndex minor_index_;

};

}
}

#endif //STEREOVISION_MINOR_INDEX_H
