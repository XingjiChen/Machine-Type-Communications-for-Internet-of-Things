#include "dragon.hpp"
Dragon::Dragon(const std::string& name, size_t age, size_t size): name_(name), age_(age), size_(size){}

const std::string Dragon::GetName() const{
    return name_;
}

size_t Dragon::GetAge() const{
    return age_;
}

size_t Dragon::GetSize() const{
    return size_;
}

const std::list<Treasure> Dragon::GetTreasures() const{
    return treasureList_;
}

std::ostream& operator<<(std::ostream& out, const Dragon& cave){
    out << "Dragon named: " << cave.GetName() << ", age: " << cave.GetAge() << ", size: " << cave.GetSize() <<std::endl;
    out << "Treasures:" << std::endl;
    std::list<Treasure> treasureList = cave.GetTreasures();
    for(auto i = treasureList.begin(); i != treasureList.end(); i++){
        out << i->name << std::endl;
    }
    return out;
}

/*
* A Dragon should be printed to the parameter ostream in the following format:
 * Dragon named: <Dragon's name>, age: <Dragon's age>, size: <Dragon's size>\n
 * Treasures:\n
 * <First Treasure's name in the Dragon's treasures list>\n
 * <Second Treasure's name in the Dragon's treasures list>\n
 * ...
 * <Last Treasure's name in the Dragon's treasures list>\n
 *
 * NOTE: The dragons in the dragon list are printed in the same format as the
 *       overloaded << stream operator for Dragons prints them. Also note
 *       that there is an additional
 *       end of line character '\n' after each dragon except for the last one.

 * \param os reference to the output stream to which the information is printed
 *           (ostream&).
 * \param cave the Dragon whose information should be printed (const Dragon&).
 *
 * \return The output stream given as one of the arguments.
 */