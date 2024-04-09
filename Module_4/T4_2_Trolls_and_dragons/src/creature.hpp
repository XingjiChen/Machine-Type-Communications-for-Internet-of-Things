#ifndef AALTO_ELEC_CPP_CREATURE_CLASS
#define AALTO_ELEC_CPP_CREATURE_CLASS

#include <iostream>
#include <string>
#include <vector>

/**
 * \brief Parent class for classes troll and dragon
 */
class Creature {
 public:
  /**
   * \brief Construct a new Creature object
   *
   * \param name name of the creature as a std::string
   * \param type type of the creature as a std::string
   * \param hitpoints hitpoints of the creature as an integer value
   */
  Creature(const std::string& name, const std::string& type, int hitpoints);

  /**
   * \brief Get the name of the creature
   *
   * \return a reference to the string describing the name of the creature
   */
  const std::string& GetName() const;

  /**
   * \brief Get the type of the creature
   *
   * \return a reference to the string describing the type of the creature
   */
  const std::string& GetType() const;

  /**
   * \brief Get remaining hitpoints of the creature
   *
   * \return the remaining hitpoints as an integer
   */
  int GetHitPoints() const;

 private:
  std::string name_;
  const std::string type_;
  int hitpoints_;
};

// Declare the '<<' operator here

std::ostream& operator<<(std::ostream& os, const Creature& creature);
#endif