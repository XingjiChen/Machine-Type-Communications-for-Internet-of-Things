#include <iostream>

#include "person.hpp"

int main(void) {
    /** Person class' constructor takes two arguments: name and birthyear **/
    Person kalle("Kalle Kankkunen", 1996);
    Person ville("Ville Vinkkunen", 1992);
    Person liisi("Liisi Pirinen", 1950);

    std::cout << kalle.GetName() << " is " << kalle.GetAge(2020) << " years old." << std::endl;
    std::cout << ville.GetName() << " is " << ville.GetAge(2020) << " years old." << std::endl;
    std::cout << liisi.GetName() << " is " << liisi.GetAge(2020) << " years old." << std::endl;
}
