**Objective:** Learn using iterators with **vector**.

Implement the following three functions that uses integer vectors. 
You are required to use iterators for walking through the vector.

1. **ReadVector** that will read integer values from user and stores them as
integer vector that is returned by the function. The function stops
reading when a non-numeric value it encounters a non-numeric value.

   > **HINT**
   >
   >    See [C++ Primer: Chapter 1.4.3](<https://learning.oreilly.com/library/view/c-primer-fifth/9780133053043/ch01lev2sec12.html#ch01lev2sec12/?ar>)
        for reading an unknown number of inputs.

2. **PrintSum1** that calculates sums a consecutive pair of numbers in 
the function argument vector of integers and prints them on the standard 
output stream. The function will print the sum of
two consecutive numbers in the vector, separated by space ` `. 

    For example, if the argument vector is composed of 
    `{1, 2, 3, 4}`, the output should be 

    ```
    3 5 7  
    ```

    followed by a space and a newline character.
    Note that the output will have one number less than the input. 

3. **PrintSum2** that calculates sum of the first and last item in the
vector, then the sum of second and second-last item in the vector,
and so on, until all integers in the vector are processed and print them 
on the screen.

    For example, if the input argument vector is `{1, 2, 3, 4}` the output 
    will be 

    ```
    5 5 
    ```    
    followed by a space and a newline.