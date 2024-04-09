#pragma once

#include <iostream>
#include <list>
#include <string>

/* Enumeration types for the different treasures */
enum TreasureType
{
    Jewellery,
    Wisdom,
    Potions
};

/* Implementation of Treasure */
struct Treasure
{
    TreasureType type;
    std::string name;
};

/* Enumeration types for the different foods */
enum FoodType
{
    PeopleFood,
    People,
    Herbs
};

/* Implementation of Food */
struct Food
{
    FoodType type;
    std::string name;
};

/**
 * \brief class Dragon is an abstract class that describes a dragon.
 *
 * Each Dragon object has a name (string), age (size_t), size (size_t) and a
 * list of Treasure objects that the Dragon has hoarded.
 *
 * The class has the following protected members, which means they are
 * accessible to classes which inherit this class: name (std::string), age
 * (size_t), size (size_t), treasures (std::list<Treasure>).
 *
 * Functions:
 *
 * The constructor takes the Dragon's name (const std::string&), age (size_t)
 * and size (size_t) as a parameter and initializes them to the parameter values.
 *
**/
class Dragon{
public:
    Dragon(const std::string& name, size_t age, size_t size);
    // Destructor: To Be Done Think about how it should be implemented!
    virtual ~Dragon() {};
    Dragon(const Dragon& other) = delete;
    Dragon& operator=(const Dragon& other) = delete;
/*
    * GetName: the function returns a constant reference to the Dragon's name and
    * takes no parameters. This function does not change the state of the Dragon
    * object, i.e. the function should be const.
    *
    * GetAge: the function returns the Dragon's age as a size_t and takes no
    * parameters. This function does not change the state of the Dragon object,
    * i.e. the function should be const.
    *
    * GetSize: the function returns the Dragon's size as a size_t and takes no
    * parameters. This function does not change the state of the Dragon object,
    * i.e. the function should be const.
*/
    const std::string GetName() const;
    size_t GetAge() const;
    size_t GetSize() const;
/*
 * GetTreasures: the function returns a constant reference to the Dragon's
 * treasures list and takes no parameters. This function does not change the
 * state of the Dragon object, i.e. the function should be const.
 */
    const std::list<Treasure> GetTreasures() const;
    /*
    Eat: a pure virtual function, which returns nothing and takes a reference to
    a list of Food objects as a parameter.
     */
    virtual void Eat(std::list<Food>& foodList) = 0;
/*
    Hoard: a pure virtual function, which returns nothing and takes a reference
    * to a list of Treasure objects as a parameter.
*/
    virtual void Hoard(std::list<Treasure>& treasureList) = 0;

    friend std::ostream& operator<<(std::ostream& out, const Dragon& cave);

protected:
    std::string name_;
    size_t age_;
    size_t size_;
    std::list<Treasure> treasureList_;
};

std::ostream& operator<<(std::ostream& out, const Dragon& cave);
/**
 * \brief TODO: operator << overloads the << stream operator for printing
 * Dragons to a desired ostream.
 *
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
 *
 */
