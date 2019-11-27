//
// Created by vahagn on 11/27/19.
//
#include "row.h"
#include <iostream>
#include <variant>
#include <memory>
#include <matrix.h>

int main(int argc, char *argv[]) {
  std::variant<std::shared_ptr<int[]>, int *> q(std::shared_ptr<int[]>(new int[10]));
//  q = ;

  StereoVision::Matrix<int> mat1(6, 5);
  StereoVision::Matrix<float> mat2(6, 5);
  for (int j = 0; j < mat1.Rows(); ++j) {
    for (int i = 0; i < mat1.Cols(); ++i) {
      mat1[j][i] = i * j;
      mat2[j][i] = (float) i / (j + 0.001);
    }
  }

  std::cout << " =================== Mat 1 =============" << std::endl;
  std::cout << mat1 << std::endl;
  std::cout << " =================== Mat 2 =============" << std::endl;
  std::cout << mat2 << std::endl;
  std::cout << " =================== Mat 1 + 2 =============" << std::endl;
  std::cout << mat1 + mat2 << std::endl;
  return 0;

  StereoVision::Row<int> row1(6);
  StereoVision::Row<float> row2(6);

  for (int i = 0; i < row1.Length(); ++i) {
    row1[i] = i;
    row2[i] = 2 * i;
  }

  std::cout << row1 << std::endl;
  std::cout << row2 << std::endl;

  auto sum = row1 + row2;
  auto sub = row1 - row2;
  auto mul = row1 * row2;

  auto dot = row1.dot(row2);

  std::cout << sum << std::endl;
  std::cout << sub << std::endl;
  std::cout << mul << std::endl;
  std::cout << dot << std::endl;

  return 0;
}