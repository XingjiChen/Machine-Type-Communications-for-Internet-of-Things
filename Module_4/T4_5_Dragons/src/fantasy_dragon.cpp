#include "fantasy_dragon.hpp"

// Define FantasyDragon's methods here
/*
 Eat: an override of Dragon's Eat.
 *  FantasyDragons only eat Food whose type is either People or PeopleFood.
 *  Each eaten Food item increases the dragon's size by one.
 *
 *  The food that the dragon eats is removed from the parameter food list and
 *  each time the dragon feasts upon something you should print information of
 *  the Food that is being eaten to standard output in the following format:
 *  Fantasy dragon ate: <Food's name>\n
 *
 *  The food should be eaten in the order from the list's beginning to end.
 */

void FantasyDragon::Eat(std::list<Food> &foodList){
    for(auto i = foodList.begin(); i != foodList.end();){
        if(i->type == People or i->type == PeopleFood){
            size_ = size_ + 1;
            std::cout << "Fantasy dragon ate: ";
            std::cout << i->name << std::endl;
            //delete (*i);
            i = foodList.erase(i);
        }
        else i++;
    }
}

/*
 *  * Hoard: an override of Dragon's Hoard.
 *  FantasyDragons hoard only Treasures whose type is Jewellery. Each hoarded
 *  treasure is added to the dragon's treasure list and is removed from
 *  the parameter treasure list.
 *
 *  Each time the FantasyDragon hoards an item you should print information
about the hoarded
 *  item to standard output in the following format:
Fantasy dragon received: <Treasure's name>\n
 *
 *  The treasures should be received in the order from the list's beginning to
end.
 */

void FantasyDragon::Hoard(std::list<Treasure>& treasureList){
    for(auto i = treasureList.begin(); i != treasureList.end();){
        if(i->type == Jewellery){
            treasureList_.push_back(*i);
            std::cout << "Fantasy dragon received: ";
            std::cout << i->name << std::endl;
            i = treasureList.erase(i);
        }
        else i++;
    }
}