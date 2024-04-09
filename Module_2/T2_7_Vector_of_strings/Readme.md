**Objective:** Practice `string` and `vector` classes of C++ standard library.

In this task, you are required to implement a program that appends and 
removes the given strings to/from a vector, as commanded by the user. 
You should implement a simple command line interface in `CMDReader` function 
that implements the following.

1. At the beginning, the program should print 
    
    ```
    Commands: ADD, PRINT, REMOVE,QUIT<newline>
    ```

    where `<newline>` is the newline character.
    
2. Then, it should print 
    
    ```
    Enter a command:<newline>
    ```
    
    where `<newline>` is the newline character.

3. The program should read the command from the user in a loop in `CMDReader` function.

    * If user command is **ADD**, `CMDReader` function should call `Adder` 
    function, which implements the following.
    
      i. The program should first prompt: 
    
      ```
      Enter a name:<newline>
      ```
        
         where `<newline>` is the newline character.
    
      ii. Then it reads the name from the user and adds it to a vector. 
    
      iii. Finally, it prints 
        ```
        Number of names in the vector:<newline>
        <vector size><newline>
        ```

     where `<newline>` is the newline character and `<vector size>` is the number 
    of elements in the specified vector. 

    * If user command is **REMOVE**, `CMDReader` function should call `Remover` 
    function, which removes the last string from the specified vector. Then, 
    it outputs the removed string in the following way.

      ``` 
      Removing the last element:<newline>
      <removed string><newline>
      ```
    
      where `<newline>` is the newline character and `<removed string>` is the last 
    element of the vector.

* If user command is **PRINT** function should call `Printer` 
function, which outputs all stored strings, each on a separate line
(i.e., followed by newline character). 

* If user command is **QUIT**, `CMDReader` function should exit the program.

> **IMPORTANT**
>    
> `Adder` function needs to be implemented and get full points before
> any other tests can be run for grading.

Here is an example of an session:

```
Commands: ADD, PRINT, REMOVE, QUIT
Enter a command: 
    ADD
Enter a name:
    Erkki
Number of names in the vector:
    1
Enter a command:
    ADD
Enter a name:
    Tiina
Number of names in the vector:
    2
Enter a command:
    PRINT
Erkki
Tiina
Enter a command:
    REMOVE
Removing the last element:
Tiina
Enter a command:
    QUIT
```