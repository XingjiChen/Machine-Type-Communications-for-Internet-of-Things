#ifndef AALTO_ELEC_CPP_DRAGON_CLASS
#define AALTO_ELEC_CPP_DRAGON_CLASS

#include "creature.hpp"

/**
 * \brief Inherits class Creature.
 *
 * Here, you will need to define the necessary
 * features that support the required functionalities outlined in the given
 * main function.
 */
class Dragon : public Creature {
public:
    Dragon(const std::string& name, int hitpoints);
  
};

#endif