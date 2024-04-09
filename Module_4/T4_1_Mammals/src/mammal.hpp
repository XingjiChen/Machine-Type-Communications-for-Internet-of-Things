#ifndef AALTO_ELEC_CPP_MAMMAL_CLASS
#define AALTO_ELEC_CPP_MAMMAL_CLASS

#include <iostream>
#include <string>

/**
 * \brief Parent class for dog and cat classes
 */

class Mammal {
 public:
  /**
   * \brief Construct a new Mammal object
   *
   * \param weight weight of the mammal
   */
  Mammal(double weight);

  /**
   * \brief Get the weight of the object
   *
   * \return weight of the animal as a double
   */
  double GetWeight();

 private:
  double weight_;
};

#endif
