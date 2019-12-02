//
// Created by vahagn on 11/27/19.
//
#include <iostream>
#include <variant>
#include <memory>
#include <linalg/tensor.h>

int main(int argc, char *argv[]) {
  /*std::variant<std::shared_ptr<int[]>, int *> q(std::shared_ptr<int[]>(new int[10]));
  StereoVision::linalg::Shape weights = {3, 4, 3};

  for (StereoVision::linalg::TensorIndices indices(weights, {0, 0, 0});; indices += 2) {
    std::cout << indices << std::endl;
  }*/
  {
    StereoVision::linalg::IndexSlice slice = {2, -1, -1};
    StereoVision::linalg::IndexSlice slice2 = {2, -1};
    StereoVision::linalg::Tensor<int> tensor({3, 4, 2});
    typeof(tensor) t = tensor[slice];
    typeof(tensor) t2 = t[slice2];
  }

  {
    StereoVision::linalg::Shape shape = {2, 3};
    StereoVision::linalg::Shape shape2 = {3};
    StereoVision::linalg::Tensor<int> tensor(shape);

    StereoVision::linalg::Tensor<int> row(shape2);
    row[0] = 1;
    row[1] = 2;
    row[2] = 3;
    tensor = row;
    StereoVision::linalg::Tensor<float> tensor2 = tensor + row;

    tensor2.Dot(row);

//    tensor[0][2] = 10;
    int m = tensor[0][1];
    std::cout << tensor2 << std::endl;

  }

  return 0;
}