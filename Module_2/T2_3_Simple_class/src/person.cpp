#include "person.hpp"

// define your Person class' functions here

// Constructor
Person::Person(const std::string& name, int birthYear) : Name(name), birthyear(birthYear) {}

// GetName member function
std::string Person::GetName() const {
    return Name;
}

// GetAge member function
int Person::GetAge(int year) const {
    return year - birthyear;
}