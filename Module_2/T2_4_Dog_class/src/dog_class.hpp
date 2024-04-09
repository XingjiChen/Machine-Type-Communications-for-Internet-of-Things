#ifndef AALTO_ELEC_CPP_DOG_CLASS
#define AALTO_ELEC_CPP_DOG_CLASS

#include <string>

class Dog {
public:
    Dog(int age, std::string name);

    void SetAge(int age);
    int GetAge() const;
    void SetName(std::string name);
    std::string GetName() const;

private:
    int age_;
    std::string name_;
};

#endif // AALTO_ELEC_CPP_DOG_CLASS
