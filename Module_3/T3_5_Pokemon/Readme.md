**Objective:** Practice use of algorithms together with a list
  container.

Pokemon is an information entity with a name (string) and an
identifier. Therefore the **pair** type can be used to store one such
element. This exercise operates on lists that consist of (string,
size_t) pairs. You should review the function interfaces and respective 
descriptions there.

You will need to implement the following methods for the *PokemonCollection* class:

  * **Add(name, id)**: adds a new Pokemon with
    given name/id pair at the end of list *pokemon_*.

  * **Remove(name, id)**: removes the first Pokemon with matching name and id.

  * **Print**: prints the Pokemons.
    See the example in *pokemon.hpp* for the required print format.

  * **SortByName**: sorts the Pokemon collection by their name. 
    If two names are equal, their order is determined by their ids.

  * **SortById**: sorts the Pokemon collection by their id. 
    If two ids are equal, their order is determined by their names.

And the following constructor:

  * **PokemonCollection(c1, c2)**: merges the contents of the two
    collections. Duplicate elements must be removed.

The grading weight is 1 for 
**Add**, **Remove**, **Print**, **SortByName** and **SortById**, and 2
for the merge constructor. Especially for the last three functions it is
recommended that you familiarize yourself with the algorithms and
functions available for list container (such as **sort** and
**unique**).

**Note:** You need full points from the Add and Print methods for the rest of 
the tests to be run. In addition, the sort methods need full points for the 
constructor to be tested.

Instructions on how to run and test your programs locally are available
in Module 0.
