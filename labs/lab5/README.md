# Lab 5

## Instructions:

Augment the source code file `Sudoku.cpp` with code for error checking games that you read and solutions that you (utlimately) produce. Specifically, update private member function `sudoku::read()` to check that grid indices and values are valid when reading a new game. Grid indices must be in the range 0-8, while grid values must either be in the range 0-9 (for reading games) or 1-9 (for solutions). The value check should be placed in its own private member function called `sudoku::error_check_value()` as it must be performed on solutions before displaying them and writing them to file. Be forewarned that while 0 is a valid grid value for a new game when it is read from file, it is not a valid grid value after the game has been solved as it indicates a blank cell. You may consequently want `sudoku::error_check_value()` to take arguments that define the value range checked. Then, create and use private member function `sudoku::error_check_uniqueness()` to make sure solutions are valid; the grid values must be unique for each row, column, and block. All error checking should print offending data to stderr before bailing out (`exit()`).

Then, update `Sudoku.cpp` to solve the commandline specified game. Let public member function `sudoku::solve()` start the computation and carry out the error checking described above. Have private member function `sudoku::solve(arguments)` carry out the recursion. This function takes arguments that tells it what to do and on what data. What the arguments are depends on your choice of implementation.

Pseudo-code for the recursive `solve()` function looks as follows:

```
solve(arguments) {
    if solution found,
        return solution-found
 
    set cell index(i, j)
    determine valid values
    if no valid values left,
        return road-to-nowhere

    iterate thru valid values {
        game[i][j] = next value
        if solve(arguments) == solution-found
            return solution-found
    }

    reset: game[i][j] = 0
    return road-to-nowhere
} 
```

In words, the recursive search for the solution is based on enumerating valid values for each empty cell in numerical order. When a particular sequence of choices makes it impossible to continue, backtracking is used to return to the last variable configuration and try the next value. As you have seen in class, recursion is a deceptively simple way to solve a problem and it is easy to not do it right. Pay attention to your base cases as they stop teh recursion. Likewise, pay attention to the code that advances you toward the base cases since if this doesn't work, your code will either stop prematurely or not at all!

## Provided Materials:

A makefile, solution executable, and the `game.txt`, `badgame1.txt` and `badgame2.txt` files were included.

Also included was the source code in `Sudoku.cpp`. More specifically the following parts of Sudoku.cpp were already written for us:
* The contents of the `sudoku` class declaration (excluding the `valid_values()` function and the parameters of the private `solve()` function)
* The `sudoku` class's constructor
* Everything in the `sudoku::read()` function except the error checking
* Both `sudoku::write()` functions
* The `sudoku::display()` function
* The `main()` function

## Note about the TXT files:

The TXT files in this repository are used for inputing the puzzle data into the `Sudoku` executable and storing the solution for the puzzle produced by the executable.

The naming conventions of the TXT files are as follows:
* Input Files: `gamename.txt`
* Output Files: `gamename_solved.txt`

The contents of both types of files are lines of 3 integers representing the row number, column number, and value of the cell the line is representing. Note that the row and column numbers start at 0 and go to 8.
