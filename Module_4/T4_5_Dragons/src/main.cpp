#include <vector>
#include <list>
#include <iostream>
#include <cstdlib>

#include "dragon.hpp"
#include "fantasy_dragon.hpp"
#include "magic_dragon.hpp"
#include "dragon_cave.hpp"

std::list<Treasure> CreateRandomTreasures(size_t count) {
    std::list<Treasure> treasures;

    // Jewellery
    std::vector<std::string> j_names = {"Ruby", "Gold bar"};
    // Wisdom
    std::vector<std::string> w_names = {"Scroll of infinite wisdom", "Sun Tzu's Art of War"};
    // Potions
    std::vector<std::string> p_names = {"Cough syrup", "Liquid luck", "Stoneskin potion"};

    std::vector<std::vector<std::string>> names = {j_names, w_names, p_names};

    for(size_t i = 0; i < count; i++) {
        size_t type = rand()%3;
        Treasure t = {((TreasureType)type), names[type][rand()%(names[type].size())]};
        treasures.push_back(t);
    }

    return treasures;
}

std::list<Food> CreateRandomFood(size_t count) {
    std::list<Food> food;

    // PeopleFood
    std::vector<std::string> pf_names = {"Tenderloin steak", "Carnivore pizza"};
    // People
    std::vector<std::string> p_names = {"Raimo", "Petteri"};
    // Herbs
    std::vector<std::string> h_names = {"Arrowroot", "Bay leaves"};

    std::vector<std::vector<std::string>> names = {pf_names, p_names, h_names};

    for(size_t i = 0; i < count; i++) {
        size_t type = rand()%3;
        Food f = {((FoodType)type), names[type][rand()%(names[type].size())]};
        food.push_back(f);
    }

    return food;
}

int main() {
    using namespace std;

    // Seed the random
    srand(time(NULL));

    // Random treasures
    list<Treasure> treasures = CreateRandomTreasures(rand()%10);
    // Random food
    list<Food> food = CreateRandomFood(rand()%10);

    cout << "*** Creating a set of different Dragons.." << endl;
    MagicDragon* mdragon = new MagicDragon("Puff", 976, 20);
    mdragon->Hoard(treasures);

    FantasyDragon* fdragon = new FantasyDragon("Bahamut", (rand()%10000)+900, (rand()%10)+1);
    fdragon->Hoard(treasures);

    cout << "*** END OF READ ***" << endl;

    cout << "*** The dragons need beachside housing, creating a new DragonCave.." << endl;
    DragonCave* cave = new DragonCave();

    cout << "*** Accommodating the different Dragons to the cave.." << endl;
    cave->Accommodate(mdragon);
    cave->Accommodate(fdragon);

    cout << "*** Printing out the cave dwellers.." << endl;
    cout << *cave;
    cout << "*** END OF READ ***" << endl;

    cout << "*** Evicting a few dragons for various reasons.." << endl;
    size_t m_evicted = 0;

    if(rand()%2) {
        m_evicted = 1;
        cout << mdragon->GetName() << " the MagicDragon broke the cave's rules and was evicted.." << endl;
        cave->Evict(mdragon->GetName());
        delete mdragon;
    }

    if(rand()%2) {
        m_evicted = 1;
        cout << fdragon->GetName() << " the FantasyDragon broke the cave's rules and was evicted.." << endl;
        cave->Evict(fdragon->GetName());
        delete fdragon;
    }

    if(rand()%2 && !m_evicted) {
        cout << fdragon->GetName() << " the FantasyDragon framed " << mdragon->GetName() << " and the MagicDragon who was evicted.." << endl;
        cave->Evict(mdragon->GetName());
        delete mdragon;
    }

    cout << "*** END OF READ ***" << endl;

    cout << "*** Printing out the new list of cave dwellers.." << endl;
    cout << *cave;
    cout << "*** END OF READ ***" << endl;

    cout << "*** The cave spontaneously collapsed, killing all the remaining cave dwellers (deleted).." << endl;
    delete cave;

    cout << "*** Test complete, exiting.." << endl;

    return 0;
}
