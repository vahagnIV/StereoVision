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
#include "tensor_indices.h"
#include "../exceptions/invalid_conversion_exception.h"
#include "../exceptions/wrong_operand_exception.h"

namespace StereoVision {
namespace linalg {
#define DECLTYPEPlus(A, B) decltype(std::declval<A>() + std::declval<B>())
#define DECLTYPEMul(A, B) decltype(std::declval<A>() * std::declval<B>())

typedef std::vector<int> IndexSlice;

template<typename T>
class Tensor {
 public:
  Tensor(const Shape &shape)
      : Tensor(new T[std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<unsigned int>())],
               shape, false) {

  }

  Tensor(T *data, const Shape &shape, bool data_is_external = true) : Tensor(data,
                                                                             shape,
                                                                             data_is_external,
                                                                             new std::atomic<int>(1),
                                                                             std::vector<int>(shape.size(), -1),
                                                                             shape) {}

  Tensor(const Tensor &other) : Tensor(other.data_,
                                       other.shape_,
                                       other.data_is_external_,
                                       other.reference_counter_,
                                       other.slice_,
                                       other.weights_
  ) {
    if (!data_is_external_) {
      reference_counter_ = other.reference_counter_;
      ++(*reference_counter_);
    }
  }

  operator T() const {
    if (shape_.size() != 1 && shape_[0] != 1)
      throw InvalidConversionException("Tensor cannot be converted to scalar");
    return data_[0];
  }

  T *Data() const {
    return data_;
  }

  const Shape &GetShape() const {
    return shape_;
  }

  template<typename K>
  operator Tensor<K>() const {
    Tensor<K> result(shape_);
    for (int i = 0; i < Total(); ++i) {
      result.Data()[i] = data_[i];
    }
    return result;
  }

  const Tensor<T> &operator[](int i) const {IndexSlice slice = slice_;
    slice[0] = i;
    return (*this)[slice]; }

  Tensor<T> operator[](int i) {
    IndexSlice slice = slice_;
    slice[0] = i;
    return (*this)[slice];
  }

  Tensor<T> operator[](const IndexSlice &slice) const {
    IndexSlice new_slice;
    Shape new_shape;
    int slice_index = 0;
    for (int new_slice_index = 0; new_slice_index < slice_.size(); ++new_slice_index) {
      if (slice_[new_slice_index] == -1) {
        new_slice.push_back(slice[slice_index++]);
      } else {
        new_slice.push_back(slice_[new_slice_index]);
      }
      if (new_slice[new_slice_index] == -1)
        new_shape.push_back(weights_[new_slice_index]);

    }
    if (slice_index != slice.size())
      throw IndexOverflowException("Invalid slice");
    if (new_shape.size() == 0)
      new_shape.push_back(1);

    return Tensor<T>(data_, new_shape, true, nullptr, new_slice, weights_);
  }

  Tensor<T> &operator=(const T &value) {
    if (IsScalar())
      data_[0] = value;
    else {
      for (int i = 0; i < shape_[0]; ++i) {
        (*this)[i] = value;
      }
    }
  }

  Tensor<T> &operator=(const Tensor<T> &other) {
    if (IsScalar() && other.IsScalar()) {
      *this = other.operator T();
      return *this;
    }

    if (shape_.size() > other.GetShape().size())
      for (int i = 0; i < shape_[0]; ++i) {
        (*this)[i] = other;
      }
    else if (GetShape() == other.GetShape())
      for (int i = 0; i < shape_[0]; ++i) {
        (*this)[i] = other[i];
      }
    else
      throw WrongOperandException("Trying to add operands of differnet size");

  }

  template<typename K>
  auto operator+(const Tensor<K> &other) const -> Tensor<DECLTYPEPlus(T, K)> {
    Tensor<DECLTYPEPlus(T, K)> result(shape_);

    if (shape_.size() > other.GetShape().size())
      for (int j = 0; j < GetShape()[0]; ++j) {
        result[j] = (*this)[j] + other;
      }
    else if (shape_ == other.GetShape()) {

      for (int i = 0; i < Total(); ++i) {
        result.data_[i] = data_[i] + other.data_[i];
      }
      /*if (IsScalar())
        result = (*this).operator T() + other.operator T();
      else {
        for (int j = 0; j < GetShape()[0]; ++j) {
          result[j] = (*this)[j] + other[j];
        }
      }*/
    } else
      throw WrongOperandException("Trying to add two tensors of different size.");
    return result;
  }

  template<typename K>
  auto operator-(const Tensor<K> &other) const -> Tensor<DECLTYPEPlus(T, K)> {
    Tensor<DECLTYPEPlus(T, K)> result(shape_);

    if (shape_.size() > other.GetShape().size())
      for (int j = 0; j < GetShape()[0]; ++j) {
        result[j] = (*this)[j] + other;
      }
    else if (shape_ == other.GetShape()) {

      for (int i = 0; i < Total(); ++i) {
        result.data_[i] = data_[i] - other.data_[i];
      }
      /*if (IsScalar())
        result = (*this).operator T() - other.operator T();
      else {
        for (int j = 0; j < GetShape()[0]; ++j) {
          result[j] = (*this)[j] + other[j];
        }
      }*/
    } else
      throw WrongOperandException("Trying to subtract two tensors of different size.");
    return result;
  }

  template<typename K>
  auto operator*(const Tensor<K> &other) const -> Tensor<DECLTYPEMul(T, K)> {
    Tensor<DECLTYPEMul(T, K)> result(shape_);

    if (shape_.size() > other.GetShape().size())
      for (int j = 0; j < GetShape()[0]; ++j) {
        result[j] = (*this)[j] + other;
      }
    else if (shape_ == other.GetShape()) {

      for (int i = 0; i < Total(); ++i) {
        result.data_[i] = data_[i] * other.data_[i];
      }
      /*if (IsScalar())
        result = (*this).operator T() * other.operator T();
      else {
        for (int j = 0; j < GetShape()[0]; ++j) {
          result[j] = (*this)[j] + other[j];
        }
      }*/
    } else
      throw WrongOperandException("Trying to Haar multiply two tensors of different size.");
    return result;
  }

  template<typename K>
  auto Dot(const Tensor<K> &other,
           std::vector<std::pair<unsigned int, unsigned int>> dims = {}) const -> DECLTYPEMul(T, K) {

    if (dims.size() == 0)
      dims = {{shape_.size() - 1, 0}};

    for (std::pair<unsigned int, unsigned int> dim: dims)
      if (shape_[dim.first] != other.GetShape()[dim.second])
        throw WrongOperandException("Invalid operand for dot product");

    Shape free_indices1, free_indices2, result_shape;
    for (int i = 0; i < shape_.size(); ++i) {
      if (std::find_if(dims.begin(), dims.end(),
                       [&](const std::pair<unsigned, unsigned> &element) { return element.first == i; })
          == dims.end()) {
        free_indices1.push_back(i);
        result_shape.push_back(shape_[i]);
      }

    }

    for (int i = 0; i < other.GetShape().size(); ++i) {
      if (std::find_if(dims.begin(), dims.end(),
                       [&](const std::pair<unsigned, unsigned> &element) { return element.second == i; })
          == dims.end()) {
        free_indices2.push_back(i);
        result_shape.push_back(other.GetShape()[i]);
      }
    }

    Tensor<DECLTYPEMul(T, K)> result(result_shape);
    Shape iteration_indices1(free_indices1.size());
    Shape iteration_indices2(free_indices2.size());
    for (int j = 0; j < std::max(iteration_indices1.size(), iteration_indices2.size()); ++j) {
      if (j < iteration_indices1.size())
        iteration_indices1[j] = 0;
      if (j < iteration_indices2.size())
        iteration_indices2[j] = 0;
    }

    result = 0;

    return result;

  }

  unsigned int Total() const {
    unsigned int count = 1;
    for (int dim : shape_)
      count *= dim;
    return count;
  }

  bool IsScalar() const {
    return shape_.size() == 1 && shape_[0] == 1;
  }

  virtual ~Tensor() {
    if (!data_is_external_ && --(*reference_counter_) == 0)
      delete[] data_;

    for (Tensor<T> *child: children_)
      delete child;

  }

 protected:

  Tensor(T *data,
         const Shape &shape,
         bool data_is_external,
         std::atomic<int> *reference_count,
         const std::vector<int> &slice,
         const Shape &weights)
      : data_(data),
        shape_(shape),
        reference_counter_(reference_count),
        data_is_external_(data_is_external),
        slice_(slice),
        weights_(weights) {

    int offset = 0;
    int s = shape.size();
    if (shape.size() == 1 && shape[0] == 1)
      return;
    Shape new_shape(shape.begin() + 1, shape.end());
    Tensor<T> *child;
    for (int i = 0; i < shape[0]; ++i) {
      child =
          0 == shape.size() - 1 ?
          new Tensor<T>(data + offset, Shape{1}) :
          new Tensor<T>(data + offset,
                        new_shape);
      offset += child->Total();
      children_.push_back(child);
    }
  }

 private:
  std::atomic<int> *reference_counter_;
  Shape shape_;
  Shape weights_;
  bool data_is_external_;
  T *data_;
  std::vector<Tensor *> children_;
  IndexSlice slice_;

};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Tensor<T> tensor) {
  if (tensor.IsScalar()) {
    os << tensor.operator T();
    return os;
  }

  if (tensor.GetShape().size() == 1)
    for (int i = 0; i < tensor.GetShape()[0]; ++i) {
      os << (tensor[i]) << "\t";
    }
  else if (tensor.GetShape().size() == 2)
    for (int i = 0; i < tensor.GetShape()[0]; ++i) {
      os << (tensor[i]) << "\n";
    }
  else {
    os << "Tensor";
  }

  return os;
}

}
}

#endif //STEREOVISION_TENSOR_H
