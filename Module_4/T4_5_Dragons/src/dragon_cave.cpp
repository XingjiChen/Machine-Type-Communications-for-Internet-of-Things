#include "dragon_cave.hpp"

// Define DragonCave's methods here

const std::list<Dragon*>& DragonCave::GetDragons() const{
    return dragonList_;
}

void DragonCave::Accommodate(Dragon* dragonPointer){
    dragonList_.push_back(dragonPointer);
}

void DragonCave::Evict(const std::string& name){
    for(auto i = dragonList_.begin(); i != dragonList_.end(); i++){
        if((*i)->GetName() == name){
            dragonList_.erase(i);
            return;
        }
        else i++;
    }
}

std::ostream& operator<<(std::ostream& os, const DragonCave& cave){
    os << "DragonCave dwellers:" << std::endl;
    const std::list<Dragon*>& dragonList = cave.GetDragons();
    for(auto i = dragonList.begin(); i != dragonList.end(); i++){
        os << std::endl;
        os << *(*i);
    }
    return os;
}
/**
*  The DragonCave should be printed to the parameter ostream in the following format:
 *  DragonCave dwellers:\n
 *  \n
 * <First Dragon in the dragons list>\n
 * <Second Dragon in the dragons list>\n
 * ...
 * <Last Dragon in the dragons list>
*/