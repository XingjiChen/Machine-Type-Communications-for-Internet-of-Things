#include "troll.hpp"
#include "dragon.hpp"

int main() {
    Troll troll("Diiba", 10), troll2("Urkki", 15);
    Dragon dragon("Rhaegal", 50), dragon2("Viserion", 55);

    std::cout << "Trolls are: " << troll << " and " << troll2 << std::endl;
    std::cout << "Dragons are: " << dragon << " and " << dragon2 << std::endl;
}