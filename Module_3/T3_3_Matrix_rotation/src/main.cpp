#include <iostream>

#include "matrix.hpp"

int main(void) {
  Matrix m;
  int n;
  std::cout << "Give dimension for n x n matrix: " << std::endl;
  std::cin >> n;
  std::cout << "Give numbers to matrix:" << std::endl;
  m = ReadMatrix(n);
  std::cout << "Printing the matrix:" << std::endl;
  Print(m);
  std::cout << "Rotating by 90 degrees!" << std::endl;
  m = Rotate90Deg(m);
  Print(m);
  return 0;
}
