//
// Created by vahagn on 12/5/19.
//

#include "iindex.h"

namespace StereoVision {
namespace linalg {

std::ostream & operator<<(std::ostream & os, const iIndex & indices) {
  for (int i = 0; i < indices.size(); ++i) {
    os << indices[i] << '\t';
  }

  return os;
}
}
}