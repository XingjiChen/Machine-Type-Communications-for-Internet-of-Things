#include "dog_class.hpp"

// Constructor
Dog::Dog(int a, std::string n) : age_(a), name_(n) { }

// SetAge
void Dog::SetAge(int a) {
    age_ = a;
}

// GetAge
int Dog::GetAge() const {
    return age_;
}

// SetName
void Dog::SetName(std::string n) {
    name_ = n;
}

// GetName
std::string Dog::GetName() const {
    return name_;
}
