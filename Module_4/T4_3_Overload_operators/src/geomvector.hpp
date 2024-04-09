#ifndef AALTO_ELEC_CPP_GEOMVECTOR_CLASS
#define AALTO_ELEC_CPP_GEOMVECTOR_CLASS

#include <cmath>
#include <iostream>

class GeomVector {
 public:
  GeomVector(double x, double y, double z) : x_(x), y_(y), z_(z) {}

  /**
   * \brief Get the vector length
   *
   * \return the length of the vector as a double precision floating point value
   */
  double Length() const;

  /**
   * \brief Overload operator for the vector sum of two GeomVector objects.
   *
   * This is a member function of the class.
   *
   * \param a the GeomVector object to be summed with the invoking object
   * \return a new GeomVector object with the vector sum of the invoking
   * object and the object given as an argument.
   */
  GeomVector operator+(const GeomVector& a);

  // Define the remaining operators here
  GeomVector operator/(double scalar) const; // Division by a scalar
  bool operator<(const GeomVector& other) const; // Smaller than
  bool operator>(const GeomVector& other) const; // Greater than
  bool operator==(const GeomVector& other) const; // Equal to
  bool operator!=(const GeomVector& other) const; // Not equal to

  /**
   * \brief Overload operator for the scalar multiplication of a GeomVector
   * object (not to be confused with dot product).
   *
   * This is an external function, but has access to the private parts of the
   * object, as it is declared as a 'friend'.
   *
   * \param a scalar value to be used as the multiplier as a double-precision
   * floating point value
   * \param b the GeomVector object to be multiplied by the scalar value.
   * \return the scalar multiplied vector as a new GeomVector object.
   */
  friend GeomVector operator*(double a, const GeomVector& b);

  /**
   * \brief Overload operator for printing the components of the vector to the
   * an output stream.
   *
   * \param out output stream to be used
   * \param a GeomVector object to be printed
   * \return reference to the output stream
   */
  friend std::ostream& operator<<(std::ostream& out, const GeomVector& a);

 private:
  double x_, y_, z_;
};

#endif