#include "pokemon.hpp"

#include <vector>

int main() {
    using namespace std;

    /* collections of few pokemons */
    PokemonCollection collection({pair<string, size_t>("Pikachu", 25), pair<string, size_t>("Raticate", 20), pair<string, size_t>("Raticate", 20), pair<string, size_t>("Bulbasaur", 1), pair<string, size_t>("Pikachu", 25), pair<string, size_t>("Diglett", 50)});
    PokemonCollection collection2({pair<string, size_t>("Venomoth", 49), pair<string, size_t>("Oddish", 43)});

    cout << "*** Test Print.." << endl;
    collection.Print();
    
    cout << "*** Test Add.." << endl;
    collection.Add("Meowth", 52);
    collection.Add("Arcanine", 59);
    collection.Print();

    cout << "*** Test Remove.." << endl;
    bool ret;

    ret = collection.Remove("Raticate", 20);
    cout << (ret ? "Remove returned true. CORRECT!" : "Remove returned false. FAILED!") << endl;;

    ret = collection.Remove("Ivysaur", 2);
    cout << (ret ? "Remove returned true. FAILED!" : "Remove returned false. CORRECT!") << endl;

    cout << "*** Test SortByName.." << endl;
    collection.SortByName();
    collection.Print();

    cout << "*** Test SortById.." << endl;
    collection.SortById();
    collection.Print();

    cout << "*** Test MergeCollections.." << endl;
    
    cout << "*** Collection 1:" << endl;
    collection.Print();

    cout << "*** Collection 2:" << endl;
    collection2.Print();

    PokemonCollection merged(collection, collection2);

    cout << "*** Merged collection:" << endl;
    merged.Print();

    return 0;
}
