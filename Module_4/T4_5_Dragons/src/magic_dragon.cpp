#include "magic_dragon.hpp"

// Define MagicDragon's methods here

void MagicDragon::Eat(std::list<Food> &foodList){
    for(auto i = foodList.begin(); i != foodList.end();){
        if(i->type == Herbs){
            size_ = size_ + 1;
            std::cout << "Magic dragon ate: ";
            std::cout << i->name << std::endl;
            i = foodList.erase(i);
        }
        else i++;
    }
}

void MagicDragon::Hoard(std::list<Treasure>& treasureList){
    for(auto i = treasureList.begin(); i != treasureList.end();){
        if(i->type == Potions){
            treasureList_.push_back(*i);
            std::cout << "Magic dragon received: ";
            std::cout << i->name << std::endl;
            i = treasureList.erase(i);
        }
        else i++;
    }
}