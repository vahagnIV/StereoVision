//
// Created by vahagn on 12/2/19.
//

#ifndef STEREOVISION_TENSOR_H
#define STEREOVISION_TENSOR_H

#include <memory>
#include <atomic>
#include <numeric>
#include <cstring>
#include <algorithm>
#include "linalg/inidices/iindex.h"
#include "../exceptions/invalid_conversion_exception.h"
#include "../exceptions/wrong_operand_exception.h"
#include "linalg/inidices/mul_index_pair.h"

namespace StereoVision {
namespace linalg {
#define DECLTYPEPlus(A, B) decltype(std::declval<A>() + std::declval<B>())
#define DECLTYPEMul(A, B) decltype(std::declval<A>() * std::declval<B>())

typedef std::vector<int> IndexSlice;

template<typename T>
class Tensor {

  template<typename K>
  friend
  class Tensor;

 public:

  /*!
   * Constructor
   * @param shape shape of the tensor
   */
  Tensor(const Shape & shape)
      : Tensor(new T[std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<unsigned int>())],
               shape, false, 0, new std::atomic<int>(0)) {
  }

  /*!
   * Copy constructor
   * @param other
   */
  Tensor(const Tensor & other) : Tensor(other.data_,
                                        other.shape_,
                                        other.data_is_external_,
                                        other.offset_,
                                        other.reference_counter_,
                                        other.weights_
  ) {

  }

  // ======================= Access ==========================================

  unsigned int Total() const {
    unsigned int count = 1;
    for (int dim : shape_)
      count *= dim;
    return count;
  }

  const Shape & GetShape() const {
    return shape_;
  }

  bool IsScalar() const {
    return shape_.size() == 0 || (shape_.size() == 1 && shape_[0] == 1);
  }

  SimpleIndex GetIndex() const {
    return SimpleIndex(GetShape());
  }

  Tensor<T> operator[](int i) {
    IndexSlice slice(shape_.size(), -1);
    slice[0] = i;
    return (*this)[slice];
  }

  const Tensor<T> & operator[](int i) const {
    IndexSlice slice(shape_.size(), -1);
    slice[0] = i;
    return (*this)[slice];
  }

  Tensor<T> operator[](const IndexSlice & slice) const {
    if (slice.size() != shape_.size())
      throw IndexOverflowException("Invalid slice");
    int offset = offset_;
    Shape weights, shape, ordering;

    int new_dim_index = 0, ordering_value = 0;
    for (int i = 0; i < slice.size(); ++i) {
      if (slice[i] != -1)
        offset += slice[i] * weights_[i];
      else {
        shape.push_back(shape_[i]);
        weights.push_back(weights_[i]);
      }
    }
    return Tensor<T>(data_, shape, data_is_external_, offset, reference_counter_, weights);
  }

  T & operator[](const iIndex & idx) {
    if (IsScalar())
      return *(data_ + offset_);
    int offset = offset_;
    for (int i = 0; i < idx.size(); ++i) {
      offset += weights_[i] * idx[i];
    }
    return *(data_ + offset);
  }

  T operator[](const iIndex & idx) const {
    if (IsScalar())
      return *(data_ + offset_);
    int offset = offset_;
    for (int i = 0; i < idx.size(); ++i) {
      offset += weights_[i] * idx[i];
    }
    return *(data_ + offset);
  }

  // ====================== Conversion ==========================================
  template<typename K>
  operator Tensor<K>() const {
    Tensor<K> result(shape_);

    for (SimpleIndex index = result.GetIndex(); index.IsValid(); ++index) {
      result[index] = (*this)[index];
    }
    return result;
  }

  template<typename K>
  Tensor<K> As() {
    return this->operator Tensor<K>();
  }

  operator T &() const {
    if (!IsScalar())
      throw InvalidConversionException("Tensor cannot be converted to scalar");
    return *(data_ + offset_);
  }

  // ====================== Transformation ======================================

  Tensor<T> Transpose(const std::vector<unsigned> & permutations = {}) {
    if (permutations.empty() && shape_.size() != 2)
      throw IndexOverflowException("Transponation without parameters is defined only for 2D tensors aka matrices");

    const std::vector<unsigned> & perms = permutations.empty() ? std::vector<unsigned>{1, 0} : permutations;

    if (perms.size() != shape_.size())
      throw IndexOverflowException("Wrong transposition");
    Shape shape, weights;
    for (const unsigned int & axix: perms) {
      shape.push_back(shape_[axix]);
      weights.push_back(weights_[axix]);
    }

    return Tensor<T>(data_, shape, data_is_external_, offset_, reference_counter_, weights);
  }


  // ====================== Arithmetics =========================================

  template<typename K>
  auto operator+(const Tensor<K> & other) const -> Tensor<DECLTYPEPlus(T, K)> {
    Tensor<DECLTYPEPlus(T, K)> result(shape_);

    if (shape_.size() > other.GetShape().size())
      for (int j = 0; j < GetShape()[0]; ++j) {
        result[j] = (*this)[j] + other;
      }
    else if (shape_ == other.GetShape()) {
      for (SimpleIndex index = result.GetIndex(); index.IsValid(); ++index)
        result[index] = (*this)[index] + other[index];
    } else
      throw WrongOperandException("Trying to add two tensors of different size.");
    return result;
  }

  template<typename K>
  auto operator-(const Tensor<K> & other) const -> Tensor<DECLTYPEPlus(T, K)> {
    Tensor<DECLTYPEPlus(T, K)> result(shape_);

    if (shape_.size() > other.GetShape().size())
      for (int j = 0; j < GetShape()[0]; ++j) {
        result[j] = (*this)[j] - other;
      }
    else if (shape_ == other.GetShape()) {
      for (SimpleIndex index = result.GetIndex(); index.IsValid(); ++index)
        result[index] = (*this)[index] - other[index];
    } else
      throw WrongOperandException("Trying to add subtract tensors of different size.");
    return result;
  }

  template<typename K>
  auto operator*(const Tensor<K> & other) const -> Tensor<DECLTYPEMul(T, K)> {

    std::vector<IndexPair> pairs;
    for (int last1 = shape_.size() - 1, last2 = other.shape_.size() - 1; last1 >= 0 && last2 >= 0;
         --last1, --last2) {
      if (shape_[last1] == other.shape_[last2])
        pairs.push_back({last1, last2});
    }
    MulIndexPair pair_index(shape_, other.shape_, pairs);

    Tensor<DECLTYPEMul(T, K)> result(pair_index.GetShape());

    for (; pair_index.IsValid(); ++pair_index)
      result[pair_index] = (*this)[pair_index.First()] * other[pair_index.Second()];

    return result;

  }

  virtual ~Tensor() {
    if (!data_is_external_ && --(*reference_counter_) == 0)
      delete[] data_;

  }

 protected:

  Tensor(T *data,
         const Shape & shape,
         bool data_is_external,
         int offset,
         std::atomic<int> *reference_counter,
         const Shape & weights = {}
  )
      : data_(data),
        shape_(shape),
        weights_(weights),
        data_is_external_(data_is_external),
        offset_(offset),
        reference_counter_(reference_counter) {
    if (!data_is_external)
      ++(*reference_counter);

    // Weights
    if (weights_.empty() && !shape.empty()) {
      weights_.resize(shape_.size());
      weights_[weights_.size() - 1] = 1;
      for (int i = shape_.size() - 2; i >= 0; --i) {
        weights_[i] = shape_[i + 1] * weights_[i + 1];
      }
    }
  }

 private:
  std::atomic<int> *reference_counter_;
  Shape shape_;
  Shape weights_;
  bool data_is_external_;
  T *data_;
  int offset_;

};

template<typename T>
std::ostream & operator<<(std::ostream & os, const Tensor<T> & tensor) {

  int counter = 0;
  for (SimpleIndex indices = tensor.GetIndex(); indices.IsValid(); ++indices) {
    std::cout << tensor[indices] << '\t';
    ++counter;
    if (tensor.GetShape().size() && counter % tensor.GetShape()[tensor.GetShape().size() - 1] == 0)
      std::cout << '\n';
  }
  return os;
}

}
}

#endif //STEREOVISION_TENSOR_H
