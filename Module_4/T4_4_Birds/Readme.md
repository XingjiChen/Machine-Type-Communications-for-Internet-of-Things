**Objective:** Practice abstract classes, inheritance and little bit of
operator overloading.

You will need to implement different kinds of birds that all can fly
(except *const* birds). Birds also speak, but in different languages
specific to the bird type. **Bird** (in *bird.hpp*) is the abstract
base class for birds. You will need to implement **Duck** and **Owl** 
(and define them in *bird.hpp*). To save some
effort, you implement the needed functions inline in the bird-specific
header files together with the the class definitions.

The bird language is simple: duck says ``QUACK`` and owl says
``WHUU``. The speak function should output the name of the bird, colon,
space, followed by one of the above and ended with a newline, e.g.:

``Donald: QUACK\n``

In addition, you will need to implement class **Aviary**, which stores the birds, 
in the *aviary.hpp* file and its member functions in the *aviary.cpp* file.

Note:
    
- The copy constructor is a constructor that takes in a const reference
    to the same type as the class e.g. for Aviary: ``Aviary(const Aviary&)``. The copy
    assignment operator is the ``=`` operator that takes in a reference to a const object
    of the same type and returns a reference to itself i.e. ``*this``, e.g. for Aviary: 
    ``Aviary& operator=(const Aviary&)``. Copying can be disallowed, for example, by
    making these two private, then copies cannot be made from outside the class itself.

- You may ignore throwing ``std::out_of_range`` in the ``[]`` operators, 
    unlike the .hpp file says. Alternatively, if you wish to do it, use 
    ``throw <exception object>`` to throw an exception.

Hint:
    
You will find more instructions in the header files.
