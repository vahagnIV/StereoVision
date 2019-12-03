//
// Created by vahagn on 12/2/19.
//

#ifndef STEREOVISION_COMMON_LINALG_TENSOR_INDICES_H_
#define STEREOVISION_COMMON_LINALG_TENSOR_INDICES_H_
#include <vector>
#include <ostream>
#include "../exceptions/index_overflow_exception.h"

namespace StereoVision {
namespace linalg {

typedef std::vector<unsigned int> Shape;

class TensorIndices {
 public:
  TensorIndices(const Shape & weights, const std::vector<unsigned> & values)
      : index_values_(values), weights_(weights), is_max_(false) {

  }

  TensorIndices(const Shape & weights) : TensorIndices(weights, std::vector<unsigned>(weights.size(), 0)) {
    if (weights_.empty())
      index_values_.push_back(0);
  }

  TensorIndices & operator () (const std::vector<unsigned > & new_values);

  bool IsValid() const;
  TensorIndices & operator+=(int number);
  TensorIndices & operator++();
  const unsigned int operator[](int idx) const;
  unsigned int & operator[](int idx);
  const size_t size() const;
 private:
  std::vector<unsigned int> index_values_;
  const Shape & weights_;
  bool is_max_;

};

std::ostream & operator<<(std::ostream & os, const TensorIndices indices);

}
}

#endif //STEREOVISION_COMMON_LINALG_TENSOR_INDICES_H_
