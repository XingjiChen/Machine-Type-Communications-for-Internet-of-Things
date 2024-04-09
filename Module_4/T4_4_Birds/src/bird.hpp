#ifndef AALTO_ELEC_CPP_BIRD_CLASS
#define AALTO_ELEC_CPP_BIRD_CLASS

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

/**
 * \brief Parent class for different bird types.
 *
 * This class does not need modifications.
 */
class Bird {
 public:
  /**
   * \brief Explicit constructor as we want to avoid implicit typecasts from
   * string
   *
   * \param name name of the bird
   */
  explicit Bird(const std::string& name) : name_(name) {}

  // We use implicit copy constructor and assignment operator.

  /**
   * \brief Virtual destructor, this class may be derived from
   */
  virtual ~Bird() {}

  /**
   * \brief method Fly makes the invoking Bird fly. All birds can fly, or at
   * least the birds we are implementing in this exercise.
   *
   * Notice that flying is not a const member function - const birds cannot
   * fly! They can only speak.
   *
   * \param os Reference to the desired ostream
   */
  void Fly(std::ostream& os) { os << name_ << " flies!" << std::endl; }

  /**
   * \brief Virtual method Speak is implemented in the derived bird genus
   * class.
   *
   * \param os Reference to the desired ostream
   */
  virtual void Speak(std::ostream& os) const = 0;

  /**
   * \brief Get the name of a bird object
   *
   * \return the name of the bird as a std::string.
   */
  std::string GetName() const { return name_; }

 private:
  std::string name_;
};

#endif
