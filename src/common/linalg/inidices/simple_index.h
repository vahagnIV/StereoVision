//
// Created by vahagn on 12/2/19.
//

#ifndef STEREOVISION_COMMON_LINALG_TENSOR_INDICES_H_
#define STEREOVISION_COMMON_LINALG_TENSOR_INDICES_H_
#include <vector>
#include <ostream>
#include "../../exceptions/index_overflow_exception.h"
#include "iindex.h"

namespace StereoVision {
namespace linalg {

typedef std::vector<unsigned int> Shape;

class SimpleIndex : public iIndex {
 public:

  SimpleIndex(const Shape & weights) ;

  virtual const Shape & GetShape() const { return weights_; }

  SimpleIndex & operator()(const std::vector<unsigned> & new_values);

  virtual bool IsValid() const;
  virtual iIndex & operator+=(int number);
  virtual iIndex & operator++();
  std::vector<index_t> index_values_;
 private:
  const Shape weights_;
  bool is_invalid_;

};



}
}

#endif //STEREOVISION_COMMON_LINALG_TENSOR_INDICES_H_
