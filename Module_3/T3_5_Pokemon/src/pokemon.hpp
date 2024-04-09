#ifndef AALTO_ELEC_CPP_POKEMON
#define AALTO_ELEC_CPP_POKEMON

#include <iostream>
#include <list>
#include <string>
#include <utility>

class PokemonCollection
{
public:
    /**
     * \brief Construct a new Pokemon Collection object
     *
     * initializes the collection to empty.
     *
     * You don't need to define this in the cpp file as the definition is given
     * here
     */
    PokemonCollection() {}
    /**
     * \brief Construct a new Pokemon Collection object
     *
     * initializes the collection to by copying the parameter
     * You don't need to define this in the cpp file as the definition is given
     * here
     *
     * \param pokemons list of pokemeons
     */
    PokemonCollection(const std::list<std::pair<std::string, size_t>> &pokemons)
        : pokemons_(pokemons) {}

    /**
     * \brief Construct a new Pokemon Collection object
     *
     * initializes the collection to contain all the pokemons from the two
     * collections given as parameters and removes all duplicates
     *
     * HINT: sorting might be helpful
     *
     * \param collection a PokemonCollection
     * \param collection2 a PokemonCollection
     */
    PokemonCollection(PokemonCollection collection,
                      PokemonCollection collection2);

    /**
     * \brief adds a pokemon to the end of the collection
     *
     * \param name the pokemon's name,
     * \param id the pokemon's id,
     */
    void Add(const std::string &name, size_t id);

    /**
     * \brief  removes a pokemon to the collection
     *
     * \param name the pokemon's name,
     * \param id the pokemon's id
     *
     * \return true if the pokemon was found and removed
     * \return false otherwise
     */
    bool Remove(const std::string &name, size_t id);

    /**
     * \brief  Prints the collection to the standard output stream.
     * The format of the print should be as below:
     * id: <id>, name: <name>\n
     *
     */
    void Print() const;

    /**
     * \brief sorts the collection by pokemons' name.
     *
     * If two names are equal, their order is determined by their ids
     *
     * Hint: A list only has bidirectional iterators, which might narrow your
     * sorting solutions. However a valid and easy solution does exist!
     */
    void SortByName();

    /**
     * \brief sorts the collection by id
     * If two ids are equal, their order is determined by their names
     *
     * HINT: A list only has bidirectional iterators, which might narrow your
     * sorting solutions down a bit. However a valid and easy solution does exist!
     *
     */
    void SortById();

    /* These are for the tests to use. Do not modify */
    auto begin() { return pokemons_.begin(); }
    auto end() { return pokemons_.end(); }
    auto size() { return pokemons_.size(); }

private:
    std::list<std::pair<std::string, size_t>> pokemons_;
};

#endif
