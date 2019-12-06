//
// Created by vahagn on 11/27/19.
//
#include <iostream>
#include <variant>
#include <memory>
#include <linalg/tensor.h>
#include <linalg/matrix.h>
#include <linalg/inidices/mul_index_pair.h>
#include <linalg/inidices/sum_index_pair.h>
#include <linalg/inidices/minor_index.h>

int main(int argc, char *argv[]) {
  /*std::variant<std::shared_ptr<int[]>, int *> q(std::shared_ptr<int[]>(new int[10]));
  StereoVision::linalg::Shape weights = {3, 4, 3};

  for (StereoVision::linalg::TensorIndices indices(weights, {0, 0, 0});; indices += 2) {
    std::cout << indices << std::endl;
  }*/
  /*{
    StereoVision::linalg::IndexSlice slice = {2, -1, -1};
    StereoVision::linalg::IndexSlice slice2 = {2, -1};
    StereoVision::linalg::Tensor<int> tensor({3, 4, 2});
    typeof(tensor) t = tensor[slice];
    typeof(tensor) t2 = t[slice2];
  }*/

//  StereoVision::linalg::Shape shape1 = {4, 3};
//  StereoVision::linalg::Shape shape2 = {3, 3};
//  StereoVision::linalg::TensorIndexPair pair(shape1, shape2, {{1, 0}});
//  int count = 0;
//  for (; pair.IsValid(); ++pair) {
//    ++count;
//    std::cout << pair.First() << "  ====  " << pair.Second() << std::endl;
//  }
//  std::cout << count;
//  return 0;

//  StereoVision::linalg::Shape shape1 = {4, 3};
//  StereoVision::linalg::Shape shape2 = {3, 3};
//  StereoVision::linalg::SumIndexPair pair(shape1, shape2, {{1, 0}});
//  int count = 0;
//  for (; pair.IsValid(); ++pair) {
//    ++count;
//    std::cout<< pair << "  ====  " << pair.First() << "  ====  " << pair.Second()  << "\n" << std::endl;
//  }
//  std::cout << count;
//  return 0;

//  StereoVision::linalg::Matrix<float> matrix(7, 6);
//  StereoVision::linalg::Shape shape1 = {3, 3};
//  StereoVision::linalg::Shape shape2 = {3, 4};
//  StereoVision::linalg::Tensor<int> dot1(shape1);
//  dot1 = 1;
//
//  StereoVision::linalg::Tensor<int> dot2(shape2);
//
//  for (auto index = dot2.GetIndex(); index.IsValid(); ++index) {
//    dot2[index] = index[0];
//  }
//  std::cout << "Dot 1 : \n" << dot1 << "Dot 2 : \n" << dot2 << std::endl;
//  std::cout << dot1.Dot(dot2) << std::endl;
//  dot1 = dot2;
//  return 0;


  StereoVision::linalg::Shape s(4, 4);
  StereoVision::linalg::MinorIndex minorIndex(4, 1, 2);
  for (; minorIndex.IsValid(); ++minorIndex) {
    std::cout << minorIndex << std::endl;
    std::cout << minorIndex.GetMinorIndex() << std::endl << std::endl;
  }
  return 0;
  int counter = 0;
  StereoVision::linalg::Matrix<int> m(3, 3);
  for (StereoVision::linalg::SimpleIndex index = m.GetIndex(); index.IsValid(); ++index) {
//      std::cout << index << std::endl;
    m[index] = ++counter;
    m[index] = ++counter + 1;
    if (counter == 1000)
      break;
  }
  m[m.GetIndex()({0, 2})] = 4;

  m.Det();
  {
    StereoVision::linalg::Shape shape = {9, 4};
    StereoVision::linalg::Tensor<int> tensor(shape);

    StereoVision::linalg::Tensor<int> tensor2(shape);

    for (StereoVision::linalg::SimpleIndex index = tensor.GetIndex(); index.IsValid(); ++index) {
//      std::cout << index << std::endl;
      tensor[index] = ++counter;
      tensor2[index] = ++counter + 1;
      if (counter == 1000)
        break;
    }

    int m = 2;
    tensor *= m;
    std::cout << "Tensor\n" << tensor << std::endl;
    std::cout << "Tensor 2\n" << tensor2 << std::endl;
//    std::cout << (tensor - tensor2).Transpose().As<float>() << std::endl;
//    std::cout << (tensor + tensor2).Transpose().As<float>() << std::endl;

    auto t3 = (tensor + tensor2).As<float>();

    std::cout << "T1 x T2\n" << t3 << std::endl;

//    auto t2 = tensor[1];
//    t2 = t2.Transpose({1,0});
//    std::cout << t2 << std::endl;
    auto ind = tensor.GetIndex();
    std::cout << tensor[{1, 0}] << std::endl;
    std::cout << tensor[ind({1, 0})] << std::endl;

    //std::cout << tensor[{1, -1, -1, -1}] << std::endl;


    /*StereoVision::linalg::Shape shape2 = {3};
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
*/
  }

  return 0;
}