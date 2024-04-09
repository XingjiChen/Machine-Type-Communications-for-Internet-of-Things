**Objective:** Practice defining inherited classes that contain static
members

The template contains a definition of a **Mammal** class, and a main function
that uses this class along with a **Dog** class and a **Cat** class.
However, definitions of these classes are missing. Implement these classes
according to the following:

* Both classes should inherit the Mammal class.

* Both classes should have a constructor with two arguments. The first
    argument is a string representing the name of the creature, and the second
    argument is the weight. Remember that the weight attribute is common to all
    Mammals, and is stored in the base class.

* Implement accessor function **GetName** that returns the name of the
    creature.

* Implement static function **MakeSound** that returns a string that
    contains the sound that the creature makes. A dog should say `Wuff!`
    and a cat should say `Meow`

* Investigate how the main function is implemented and how it uses
    these classes.
* Define the classes so that they compile together with the main function
    without producing errors or warnings when compiled.
