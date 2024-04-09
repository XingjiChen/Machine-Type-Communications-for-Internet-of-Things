#ifndef AALTO_ELEC_CPP_DOG_CLASS
#define AALTO_ELEC_CPP_DOG_CLASS

#include "mammal.hpp"

/**
 * \brief Inherits class Mammal.
 *
 * Class Dog implements additionally the following features:
 *
 * 1. a constructor with two arguments, first being the name of the animal and
 * the second its weight.
 *
 * 2. an accessor function **GetName** that returns the name of the creature.
 *
 * 3. a static function **MakeSound** that returns a string that contains the
 * sound that the creature makes. For a dog, the function should return the
 * string `Wuff!`.
 *
 */
class Dog : public Mammal {
public:
    Dog(std::string name, double weight);

    std::string GetName();

    static std::string MakeSound();

private:
    std::string name_;
};
#endif
