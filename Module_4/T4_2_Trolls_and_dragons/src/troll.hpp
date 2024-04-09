#ifndef AALTO_ELEC_CPP_TROLL_CLASS
#define AALTO_ELEC_CPP_TROLL_CLASS

#include "creature.hpp"

/**
 * \brief Inherits class Creature.
 *
 * Here, you will need to define the necessary features that support the
 * required functionalities outlined in the given main function
 */
class Troll : public Creature {
public:
    Troll(const std::string& name, int hitpoints);
};

#endif