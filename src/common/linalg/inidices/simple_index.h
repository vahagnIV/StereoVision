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

  bool IsValid() const;
  iIndex & operator+=(int number);
  iIndex & operator++();
  std::vector<index_t> index_values_;
 private:
  const Shape weights_;
  bool is_max_;

};



}
}

#endif //STEREOVISION_COMMON_LINALG_TENSOR_INDICES_H_
