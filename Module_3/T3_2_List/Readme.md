**Objective:** Understanding the basic operations of list and using input
stream as a source.

In this exercise, you are required read a series of lines from an input stream 
object [istream](https://en.cppreference.com/w/cpp/io/basic_istream) into 
a **list** container. The **isteram** object can be the standard input, 
or input stream that allows reading from a file. You will implement the 
following functions.

1. **GetLines** that read lines from an input stream  
    
    i. The function declaration is 

    ```
    std::istream& GetLines(std::istream& is, std::list<std::string>& list)
    ```
    
    ii.  It clears the argument `list`.
    
    iii.  It reads lines from the argument stream `is`, and 
    
    iv.  It adds each line into the list `list`. 
        
    > **HINT**
    >   
    > - See [getline](https://en.cppreference.com/w/cpp/string/basic_string/getline)
        function documentation for reading lines from the input stream. The function will
        read as long as the input stream is readable. 
    >    
    > - See [istream](https://en.cppreference.com/w/cpp/io/basic_istream) 
       reference for available options to check the input 
       stream state.

    > **NOTE** 
    >
    >  1. A common problem is to add an extra element to the list after
        a newline character although the end of file is reached. 
        This case should be checked so that there is no empty line when 
        end of file is reached.
    >    
    >  2. The grading tests do not ensure that the list is empty before calling
        the function. Ensure that the list is empty (see `clear()` function)
        before you start reading the lines from the input stream.

2. **Print** that writes each string in the list on a
    separate line on the standard output stream.
    
    i. The function declaration is 

    ```
    void Print(const std::list<std::string>& list)
    ```

    ii.  It prints all lines in the the argument ``list`` on a separate line.

3. **SortAndUnique** that will sort the list into alphabetical
    order and remove duplicate strings. 
    
    i. The function declaration is 

    ```
    void SortAndUnique(std::list<std::string>& list)
    ```

    ii. It sorts the list into alphabetical order.
    iii. It removes the duplicate elements in the list.

    > **HINT**
    > 
    > List class has some very useful functions to handle sorting and removing duplicates.
    See [reference documentation](https://en.cppreference.com/w/cpp/container/list)
    of the list class.