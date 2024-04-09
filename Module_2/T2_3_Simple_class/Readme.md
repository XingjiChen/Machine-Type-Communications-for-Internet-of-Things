**Objective:** Learn how to declare and define a class.

In this task, you are required to 
    
1. Declare `Person` class in `person.hpp` that has 

   i.  two attributes

    - **Name** that stores the of a person,
    - **birthyear** that stores the birth year of a person

    ii.  two member functions

    - **GetName** that returns the name of the person,
        
    - **GetAge** that takes a year as an argument and returns the age 
    of the person on that year.

2.  Define `Person` class in `person.cpp`.
    
    i.  Implement the constructor that has two arguments that initializes **Name** and **birthyear** attributes.
    
    ii. Implement **GetName** member function that returns the name of the person.
    
    iii. Implement **GetAge** member function that returns the age of the person 
    at a given year. In other words, it must have a single argument that 
    specifies the year to calculate the age of the person, and returns the 
    age of the person at that year. 


The provided template has `main.cpp` file with a `main` function 
definition. The template cannot be compiled before you declare `Person` 
class in `person.hpp` and implement the function definition in `person.cpp`
files. 

When your class is implemented properly, the program should output
```
    Kalle Kankkunen is 24 years old.
    Ville Vinkkunen is 28 years old.
    Liisi Pirinen is 70 years old.
```

> **HINT**
>    1.  You should investigate the linker 
>        error (if you encounter one) very carefully. For example, if you receive an error
>        similar to
>
>        ```
>            undefined reference to function Person::Person(std::string, int)
>        ```
>        
>        it means that the linker is searching for a constructor with exact 
>        signature `Person(std::string, int)`. 
>        
>        >  **IMPORTANT**
>        >        
>        >   In C++, function overloading permits 
>        >   us to declare and define ``Person(const std::string&, int)`` and 
>        >   ``Person(std:string&, int)`` at the same time. If a caller assumes a specific
>        >   signature, and you do not have a definition for that function, the linker 
>        >   will produce an ``undefined reference`` error. Therefore, you are expected to
>        >   interpret such errors correctly.
>
>    2.  Due to an error in the grader, you might receive  ``timed out or crashed`` 
>        as a feedback. This error indicates a possible ``segmentation fault``, which 
>        should not happen. The error occurs when 
>
>        >    `GetName` function returns `std::string`. 
>        
>        In the grader, the string returned by ``GetName`` function is used 
>        for constructing another string object. Although in general this 
>        should not be a problem, as you can check from 
>        [documentation of std::string](http://www.cplusplus.com/reference/string/string/string/) 
>        (c++11 version), there is no overload of `string` constructor that 
>        accepts `std::string` argument. A solution is to declare `GetName` 
>        function such that it returns a reference to the `name_` member of `Person` class.