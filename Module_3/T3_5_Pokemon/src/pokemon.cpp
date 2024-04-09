#include "pokemon.hpp"
#include <algorithm>

// Merge constructor
PokemonCollection::PokemonCollection(PokemonCollection collection1, PokemonCollection collection2) {
    // Add elements from both collections
    pokemons_.insert(pokemons_.end(), collection1.pokemons_.begin(), collection1.pokemons_.end());
    pokemons_.insert(pokemons_.end(), collection2.pokemons_.begin(), collection2.pokemons_.end());

    // Sort and remove duplicates
    pokemons_.sort();
    pokemons_.unique();
}

// Add method
void PokemonCollection::Add(const std::string &name, size_t id) {
    pokemons_.push_back(std::make_pair(name, id));
}

// Remove method
bool PokemonCollection::Remove(const std::string &name, size_t id) {
    for (auto it = pokemons_.begin(); it != pokemons_.end(); ++it) {
        if (it->first == name && it->second == id) {
            pokemons_.erase(it);
            return true;
        }
    }
    return false;
}

// Print method
void PokemonCollection::Print() const {
    for (const auto &pokemon : pokemons_) {
        std::cout << "id: " << pokemon.second << ", name: " << pokemon.first << std::endl;
    }
}

// Sort by name method
void PokemonCollection::SortByName() {
    pokemons_.sort([](const std::pair<std::string, size_t> &a, const std::pair<std::string, size_t> &b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });
}

// Sort by ID method
void PokemonCollection::SortById() {
    pokemons_.sort([](const std::pair<std::string, size_t> &a, const std::pair<std::string, size_t> &b) {
        return a.second < b.second || (a.second == b.second && a.first < b.first);
    });
}
