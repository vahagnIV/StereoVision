//
// Created by vahagn on 12/6/19.
//

#include "minor_index.h"
namespace StereoVision {
namespace linalg {

MinorIndex::MinorIndex(StereoVision::linalg::index_t size,

                       StereoVision::linalg::index_t row,
                       StereoVision::linalg::index_t column) : minor_index_({size - 1, size - 1}) , row_(row), col_(column){
  index_values_ptr_.resize(2);
  index_values_ptr_[0] = minor_index_.GetIndexPtrs()[0];
  index_values_ptr_[1] = minor_index_.GetIndexPtrs()[1];
}

const index_t MinorIndex::operator[](int idx) const {
  int skip_value = idx == 0 ? row_ : col_;
  return *index_values_ptr_[idx] >= skip_value ? *index_values_ptr_[idx] + 1 : *index_values_ptr_[idx];
}

iIndex & MinorIndex::operator+=(int number) {
  minor_index_.operator+=(number);
  return *this;
}

iIndex & MinorIndex::operator++() {
  ++minor_index_;
  return *this;
}

MinorIndex & MinorIndex::operator()(const std::vector<unsigned> & new_values) {
  if (new_values[0] >= row_)
    *index_values_ptr_[0] = new_values[0] + 1;

  if (new_values[1] >= col_)
    *index_values_ptr_[1] = new_values[1] + 1;

  return *this;
}

const SimpleIndex & MinorIndex::GetMinorIndex() const {
  return minor_index_;
}

}
}