# Lab 4

## Instructions

First, implement hashtable_qp.cpp from the hashtable2_handout. This will form the base for your work. Make sure the code compiles and runs as expected. You only need the hash function for string data.

Then, modify the hash_table class code as follows.

Augment the hash_table class with a private subclass called `key_line` which uses a string to hold a key (word) and a vector of integers to keep track of all the line numbers where the key is found in the input file. You will neither need a constructor nor a destructor (the defaults will do fine), but you must implement a `key_line::inuse()` member function that indicates whether the object holds a key or not. You will also need to overload the comparison operator (i.e., `operator==()`). That's it for key_line which can be based on a struct instead of a class if you like.

Remove all template references used by the hash_table class which should be modified to explicity use the key_line subclass. This includes making member functions `qprobe()`, `insert()`, and `resize()` use `key_line::inuse()` when checking to see if an entry exists.

Modify the `hash_table::insert()` function to add a key if not present in the hash table. Update each `key_line` object to have it maintain a sorted list of all unique line numbers for it. That is, search the line number vector mentioned above and if not found, add the new line number at the end of the list. Use the std::find() function to carry out the search.

Add a public member function `hash_table::find()` that returns a constant reference to the vector of line numbers associated with the hash table entry for a given key. If the key is not found, a reference to an empty vector is returned. You deal with this in the main program.

Finally, modify the main program as follows.

Check the command line arguments. If a file has not been specified, exit the program with a meaningful error message.

Open the input file specified by `argv[1]`, then enter an endless loop reading and processing text lines. Save each text line in a cache (e.g. `vector<string>`) for retrieval later on. Then, change all so-called punctuation characters using `std::ispunct();` e.g. (, ), {, }, and . -- run `man ispunct` on a Hydra machine to see the full list. Use a `string::iterator` based loop to sweep through and change the punctuation characters in the text line. Alternatively, use the transform algorithm from STL to sweep through the text line along with a function called `punct_to_blank()` that does the check as well as the conversion. Finally, use a string stream to parse the resulting text line into words which you insert into a hash table along with the current line number. Close the input file when EOF is reached.

Add a second endless loop where you prompt the user for words to search for. Print all the line numbers and the corresponding text for each successfull search. Print nothing for an unsuccessfull search. Use the vector of line numbers returned by `hash_table::find()` to do this.

Make no assumptions about the number of lines in the input file. Make no assumptions about the number of characters or words on each line. The test files may be pure ascii text, html code, or even a C++ program. Your code should work regardless of the type of ascii data stored in the file.

## Provided Materials:

The basic templated code for a hash table that was used in lecture is provided in the hashtable2_handout.

Also, a solution executable (hashtable) and a makefile are provided.
