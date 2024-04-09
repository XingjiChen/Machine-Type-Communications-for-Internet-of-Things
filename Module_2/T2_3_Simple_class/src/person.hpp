#ifndef AALTO_ELEC_CPP_PERSON
#define AALTO_ELEC_CPP_PERSON

// declare your Person class here
#include <string>

class Person {
private:
    std::string Name;
    int birthyear;

public:
    // Constructor
    Person(const std::string& name, int birthYear);

    // Member functions
    std::string GetName() const;
    int GetAge(int year) const;
};

#endif