**Objective:** Learn to construct a class declaration by fixing a broken class

In this task, you are required to fix `Dog` class so that the provided 
template can be compiled. The class has
(or is supposed to have) a constructor and a few member functions for
setting and returning the age and the name of a dog.

1. Declare `Dog` class in `dog_class.hpp`.

2. Check `main.cpp` file. In `main` function, a `Dog` object, `dog`, 
is instantiated. Declare a constructor of `Dog` class accordingly, and 
fix its definition in `dog_class.cpp`.

2. In `main` function `dog` object is used for calling the member 
functions functions of `Dog` class. Declare the member functions of 
`Dog` class accordingly. 

3. In `dog_class.cpp` some attributes of `Dog` class are used. Declare the 
attributes of `Dog` class accordingly.

4. The class implements information hiding normally:
The class member variables should not be accessible directly from
outside the class, but the class state should be altered using the
functions that are accessible from elsewhere.

The main function should print the following output when everything works.

```
The dog is called Mr. Wuf and it is 5 years old!
```