#include <iostream>
#include <vector>

#include "vector.hpp"

int main(void) {
  std::cout << "Please enter the integer values. When you are finished, write "
               "something else."
            << std::endl;

  int i;
  std::vector<int> v;
  while (std::cin >> i) v.push_back(i);

  std::cout << "min: " << GetMin(v) << " max: " << GetMax(v)
            << " avg: " << GetAvg(v) << std::endl;

  return 0;
}
