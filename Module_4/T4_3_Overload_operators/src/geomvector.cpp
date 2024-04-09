#include "geomvector.hpp"

// Implement the addition operator
GeomVector GeomVector::operator+(const GeomVector& a) {
    return GeomVector(x_ + a.x_, y_ + a.y_, z_ + a.z_);
}

// Implement the division by a scalar operator
GeomVector GeomVector::operator/(double scalar) const {
    return GeomVector(x_ / scalar, y_ / scalar, z_ / scalar);
}

// Implement the less than operator
bool GeomVector::operator<(const GeomVector& other) const {
    return this->Length() < other.Length();
}

// Implement the greater than operator
bool GeomVector::operator>(const GeomVector& other) const {
    return this->Length() > other.Length();
}

// Implement the equality operator
bool GeomVector::operator==(const GeomVector& other) const {
    return (x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_);
}

// Implement the not equal operator
bool GeomVector::operator!=(const GeomVector& other) const {
    return !(*this == other);
}

// Implement the scalar multiplication operator
GeomVector operator*(double a, const GeomVector& b) {
    return GeomVector(a * b.x_, a * b.y_, a * b.z_);
}

// Implement the output stream operator
std::ostream &operator<<(std::ostream& out, const GeomVector& a) {
    out << "(" << a.x_ << ", " << a.y_ << ", " << a.z_ << ")";
    return out;
}

// Length function implementation
double GeomVector::Length() const {
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}
