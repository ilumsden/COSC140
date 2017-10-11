# Lab 3

## Part 1
### Instructions:

Write a program called Prime1 which reads an endless sequence of integers from stdin and tests whether each number is prime or not and prints a meaningful message to stdout if it is.

### Provided Materials
A solution executable was provided for this lab. It can be found in the `solutions` directory under the name `prime1`.

## Part 2
### Instructions:

Write a modified version of Prime1 called Prime2. Move the `isprime(int)` code into a class called `isprime` that overloads its function operator to act as a function object. Instantiate an `isprime` object in the main program and use it to test the input data.
To avoid having to iteratively test each new input against all possible numbers smaller than its square root, create an increasingly larger list of prime numbers and use a linear search to see if the number in question is listed or not. Initially, the list should only contain the number 2. If you want to see if N is a prime number, have the overloaded function operator call a private member function that expands the list of known prime numbers to cover N. Base this "magic" function on the code from Prime1 to grow the list such that the largest prime number known is greater than N. Then test if N is in the list by traversing the list. You are encouraged to use `find()` from STL to do the traversal, but you don't have to. Note that `find()` returns an iterator to the element if it was in the list and the end-iterator if it wasn't found. You must translate this into a boolean variable that indicates whether the number N was found in the list of not.

### Provided Materials:
A solution executable was provided. As with Part 1, it is in the `solutions` directory under the name `prime2`.

## Part 3
### Instructions: 
Write a modified version of Prime2 called Prime3. Change `isprime::operator()` to use a binary search instead of the linear search implemented by `find()` to determine if input N is a prime number. You are encouraged to use `binary_search()` from STL to do the job. Note that this algorithm returns a boolean that indicates whether the number N was found or not.
Now change the driver code in the main program. First, have it use an optional command line argument to set the number of integers to test. Call this number N. If no command line argument is present, use `N=10` as the default. Seed the random number generator with N. Second, generate a list of N random numbers in the range 1-100. As a suggestion, write a function object for producing each random number using `rand()` while letting `generate()` from STL fill in the list. Feel free to represent the list using a "vector" which you may recall is an array-based sequence container. Third, use `transform()` from STL along with function object `isprime` to obtain a boolean array that indicates which random number is prime. Feed this array to `count()` from STL to determine how many prime numbers there are. Print the result to stdout. 

### Provided Materials:
As with the previous two parts, a solution executable (`prime3`) was provided and can be found in `solutions`.

## Part 4
### Instructions:
Write a modified version of Prime3 called Prime4. This time all changes are with respect to the main program.
Write a function called `extract_prime()` that takes the two vector arrays holding all the random numbers and the boolean variables indicating which are primes as input and produces a new vector of just the prime numbers.
Write a function called `print()` which prints the contents of an array in a formatted fashion. Specifically, print 10 integers per line in a 4-character wide field with a space separating the numbers.
Add code that calls these two functions to output the prime numbers in their order of appearance. Then sort the data and eliminate any multiples of the same number. Output the result. Consider using `sort()` and `unique()` from STL to do the heavy lifting. 

### Provided Materials:
As with the previous parts, a solution executable (`prime4`) was provided and can be found in `solutions`.
