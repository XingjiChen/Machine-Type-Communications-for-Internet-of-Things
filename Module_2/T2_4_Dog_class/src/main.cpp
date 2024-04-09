#include <iostream>

#include "dog_class.hpp"

int main(void) {
  // Here we are using initializer list to initialize a new dog
  Dog dog(3, "Mr. Wuf");
  dog.SetAge(5);

  std::cout << "The dog is called " << dog.GetName() << " and it is "
            << dog.GetAge() << " years old!" << std::endl;

  return 0;
}
