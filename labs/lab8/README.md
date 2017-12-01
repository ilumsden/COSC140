# Lab 8:

## Instructions:

### Part 1:
Create `Labscores1.cpp` as follows. Have the main function read an unknown number of lines from a commandline specified file. Each line contains a first name and a last name followed by an unknown number of integers representing fictitious CS140 students and their lab scores. The data is to be reformatted and printed to stdout in sorted order along with simple stats, namely, the median and mean scores.

Create a class called `name_t` which holds and prints the student name. Public members shall include a constructor if needed, an overloaded less-than comparison operator, which returns true if the string "lastname, firstname" is lexicographically less than the corresponding string for a right hand side argument, and a function called `print_name()`, which produces the required output format including the printing of ellipses. Specifically, each "lastname, firstname" output should be followed first by a blank space and then by enough ellipses (...) to the point where the longest name has two ellipses. The first and last name strings must be private data members. Post-instantiation access should be done using public set and get member functions if need be. Any such helper functions must be given and return references to strings instead of copies of strings.

Create a class called `labscores_t` which holds and prints the lab scores and stats. Public members shall include a constructor if needed, a function called `add_data()` for adding a lab score, a function called `set_stats()` for sorting the lab scores and computing the median and mean scores, and a function called `print_labscores()` for printing the lab scores and stats to stdout. Use a vector to hold the lab scores. Make it and the stats private data members. Depending on your overall implementation strategy, this may again necessitate the addition of public set and/or get functions.

The main function shall include command line parsing as well as reading, parsing, and processing of data from a given input file. That is, your program must make sure that two commandline arguments are present where the first argument is "-byname" and the second argument specifies a file. Proper program usage should be printed to stderr if either argument is missing as well as if unknown arguments are specified. Mimic the behavior of the solution executable.

The main function shall use an `std::map` container to store pairs of `name_t` and `labscores_t` objects. The `name_t` object is the key that determines where the data goes in the map. The `labscores_t` object is the data that goes with it. You will not be allowed to change the `name_t` object once it has been inserted into the map. You can change the `labscores_t` object data should you want or need to. Your program must silently reject insertion of new data if the map already contains a node with the same `name_t` object.

For the Labscores1 program, data processing simply means printing the output in alphabetical order. This in turn translates into an inorder traversal of the map (which you may recall is a balanced BST). Use an iterator based loop to achieve this.

Make no assumptions about the number of lines in an input file. You may assume that an input file is structurally consistent in that all students have a firstname and lastname and that they all have the same number of lab scores but make no assumptions what that number is (it may vary from file to file). 

## Part 2:
Create `Labscores2.cpp` as a modified version of `Labscores1.cpp` which handles parsing of more commandline arguments and, most importantly, is able to produce and print sorted listings of the student records based on their scores. You must use a binary heap to achieve the latter functionality.

The main function must be modified to accept either "-byname", "-byrank', or "-top10" as its first argument. You will need to keep track which of the three options is specified, so you can control the program behavior. All options cause data to be read from the given file as before.

Create a class called `heap_t` which implements a heap for map iterators. Public members shall include a constructor if needed, a function called `empty()` which returns true if the heap contains no data, and a function called `add_data()` which adds a map iterator to a vector object; the map iterator should be passed to the function by reference. Public members shall also include a function called `heapify()` which reorganizes the vector object data to produce a binary max-heap, and a function called `extract_top()` which pops and returns a copy of the map iterator stored by the max-element at the top the heap. Private members shall include the aforementioned vector object which holds the map iterators that give you access to the student records stored in the map.

The map iterators must be wrapped in a private subclass called `data_t` which includes an overloaded less-than comparison operator. Doing this makes it easier to use the STL algorithms `std::make_heap()`, which heapifies a vector object, and `std::pop_heap()`, which helps maintain the heap as data is extracted. See cplusplus.com for details.

The max-heap is defined by the following less-than comparision operator. An object specified by a student record map iterator is less than another such iterator if the mean lab score is the smaller of the two. When two objects have the same mean score, use the median score to determine which is less than the other. When two objects have the same mean and median scores, use the name to determine which is less than the other.

Update the main function to choose between printing the contents of the map in sorted order by name or by score rank. Use the same heap based iterator loop to output all student records by rank and just the top 10. That is, set the number of records to be output for option "-byrank" to have an upper limit of `INT_MAX` while option "-top10" should set the upper limit to 10. Other than that, these two modes work and operate in the exact same way. 

## Provided Materials:
