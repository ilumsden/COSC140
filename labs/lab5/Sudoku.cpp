#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/* Sudoku.cpp
 * Author: Ian Lumsden
 * Date: October 24, 2017
 *
 * This program reads a TXT file containing the data
 * for an unsolved sudoku puzzle and prints it to the console.
 * Then, it solves the puzzle using a recursive solve algorithm.
 * After solving the puzzle, the program will print the solution
 * to the console. Finally, the solution will be outputted to a
 * different TXT file in the same format. During reading of the input
 * and before writing of the solution, two functions are used to confirm
 * that the puzzle contains valid, unique values.
 */

using namespace std;

// The class for defining, reading, and solving the Sudoku game.
class sudoku {
    public:
	sudoku();

	void solve();

        void read(const char *);
        void write(const char *);
        void write(const char *, const char *);

    private:
        int solve(int, int);
        
        void valid_values(int, int, vector<int> &);
        bool error_check_value(int, int);
        bool error_check_uniqueness();

        void display();

        /* An array of ints to store the current values
         * in the Sudoku game.
         */
        int game[9][9];
};

/* This is the sudoku class constructor.
 * It simply sets all the values of the 
 * member `game` array to 0.
 */
sudoku::sudoku() { 
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++)
            game[i][j] = 0;
    }
}

/* This function is the driver for solving
 * the Sudoku puzzle. It calls the recursvie
 * `solve` function to solve the puzzle, and, then,
 * it error checks the values of the solution and the
 * uniqueness of those values.
 */
void sudoku::solve() {
    cout << "SOLVE\n";
    /* This call to the recursive `call` function is
     * used to actually solve the puzzle.
     */
    int solve_success = solve(0, 0);
    /* This if statement provides an error check to
     * insure that the recursive `solve` function worked
     * as intended. If 0 was returned, something did not
     * work correctly, and the error meesage below is printed
     * to stderr before bailing out.
     */
    if (solve_success == 0) {
        cerr << "There's an issue with the recursive solve function.\n"
             << "It failed to successfully solve this problem.\n";
        exit(-7);
    }
    /* This call to `display` prints the solution out to
     * the console.
     */
    display();
  
    /* These if statements cause the program to exit with
     * the correct error codes if the values in the solution
     * are not valid or unique.
     */
    if (!error_check_value(1, 9)) {
        exit(-5);
    }
    if (!error_check_uniqueness()) {
        exit(-6);
    }
}

/* This function is used to help the recursive `solve` function
 * by generating a list of valid, unique values for the cell at
 * (row, col) based on the current contents of the `game` array.
 */
void sudoku::valid_values(int row, int col, vector<int> &valid) {
    /* This iterator is used to store the results
     * of calls to the STL `find` function.
     */
    vector<int>::iterator found;
    /* If the cell already has a value, the rules of Sudoku
     * prevent its value from changing. Therefore, the `valid`
     * vector is cleared, and the only possible value for this
     * cell is pushed back. This insures that the only 
     * valid value for this cell is its current value.
     */
    if (game[row][col] != 0) {
        valid.clear();
        valid.push_back(game[row][col]);
        return;
    }
    /* This for loop goes through every element in the same
     * row or column as the current cell and determines if
     * any of these elements are non-zero. If the code
     * encounters a non-zero value, it removes that value
     * from `valid` if the value was previously present.
     */
    for (int j = 0; j < 9; j++) {
        if (j != col && game[row][j] != 0) {
            found = std::find(valid.begin(), valid.end(), game[row][j]);
            if (found != valid.end()) {
                valid.erase(found);
            }
        }
        if (j != row && game[j][col] != 0) {
            found = std::find(valid.begin(), valid.end(), game[j][col]);
            if (found != valid.end()) {
                valid.erase(found);
            }
        }
    }
    /* The rest of the code in this function goes through every
     * element in the 3x3 block that contains the current cell.
     * As above, if the code encounters an element with a non-zero
     * value, it removes that value from `valid` if the value was
     * previously present.
     */
    int row_groupcheck = row - (row % 3);
    int col_groupcheck = col - (col % 3);
    for (int k = row_groupcheck; k < row_groupcheck + 3; k++) {
        for (int l = col_groupcheck; l < col_groupcheck + 3; l++) {
            if (k != row && l != col && game[k][l] != 0) {
                found = std::find(valid.begin(), valid.end(), game[k][l]);
                if (found != valid.end()) {
                    valid.erase(found);
                }
            }  
        }
    }
}

/* This function checks to make sure that all elements
 * in the Sudoku puzzle are wihin the range [min, max].
 */
bool sudoku::error_check_value(int min, int max) {
    /* valid stores the overall validity
     * of all the elements. If any value is not valid, valid
     * will be `false`. Otherwise, it will be `true`.
     */
    bool valid = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            //valid = (game[i][j] >= min && game[i][j] <= max)?true:false;
	    if (game[i][j] < min || game[i][j] > max) {
		cerr << i << " " << j << " " << game[i][j] << " illegal value\n";
		valid = false;
	    }
	}
    }
    return valid;
}

/* This function checks that all the values currently in
 * the Sudoku puzzle follow the game's rules of uniqueness.
 * Those rules are as follows:
 *     1) In a single row or column, there may only be one
 *        instance of each number between 1 and 9.
 *     2) In a single 3x3 block, there may only be one
 *        instance of each number between 1 and 9.
 * This function can also deal with a value being 0, as, for this
 * code, a value of 0 is the equivalent of an empty cell.
 */
bool sudoku::error_check_uniqueness() {
    /* unique will be true if all values in the
     * puzzle are unique. It will be false otherwise.
     */
    bool unique = true;
    // These two for loops go through every element in the puzzle.
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // If the element is empty (value = 0), just move to the next element.
            if (game[i][j] == 0) {
                continue;
	    }
            // This else block only runs if the current element's value != 0.
	    else {
                /* This block of code goes through every element in the same
                 * row or column as the current element. If any of these elements
                 * have the same value as the current element, an error message is
                 * printed to stderr and unique is set to `false`.
                 */ 
                for (int k = 0; k < 9; k++) {
                    if (game[i][k] == game[i][j] && k != j) {				    	
                        cerr << i << " " << j << " " << game[i][j] << " illegal non-unique value\n";
			unique = false;
		    }
		    if (game[k][j] == game[i][j] && k != i) {
                        cerr << i << " " << j << " " << game[i][j] << " illegal non-unique value\n";
			unique = false;
		    }
		}
                /* This block of code goes through every element in the same
                 * 3x3 grouping as the current element. If any of these elements
                 * have the same value as the current element, an error messsage is
                 * printed to stderr and unique is set to `false`. `unique_cell` is
                 * also set to `false` to trigger the `break` statement.
                 */
	        int row_groupcheck = i - (i % 3);
	        int col_groupcheck = j - (j % 3);
		bool unique_cell = true;
	        for (int l = row_groupcheck; l < row_groupcheck + 3; l++) {
                    for (int m = col_groupcheck; m < col_groupcheck + 3; m++) {
                        if (game[l][m] == game[i][j] && l != i && m != j) { 
                            cerr << i << " "  << j << " " << game[i][j] << " illegal non-unique value\n";
			    unique = false;
			    unique_cell = false;
			    break;
			}
		    }
		    if (!unique_cell) {
                        break;
		    }
	        }
	    }
	}
    }
    return unique;
}

/* This function reads the input from the file
 * specified by `fname` and stores it into the
 * sudoku object.
 */
void sudoku::read(const char *fname) {
    cout << "READ\n";

    ifstream fin(fname);
    
    int i, j, v;
    bool kill = false;

    /* This while loop will read in the contents
     * of the input file 3 integers at a time.
     * For each set of 3 integers, the code will
     * confirm that the first two integers (representing
     * the indices) are valid. If the integers are valid,
     * the value (third integer) will be added to the `game`
     * array. Otherwise, an error message will be printed to
     * stderr, and `kill` will be set to `true`.
     */
    while (fin >> i >> j >> v) {
        if (i < 0 || i > 8 || j < 0 || j > 8) {
            cerr << i << " " << j << " " << v << " illegal grid index\n";
	    kill = true;
	}
	else {
            game[i][j] = v;
	}
    }

    fin.close();

    /* If `kill` is `true`, the code is terminated with
     * error code -2.
     */
    if (kill) {
        exit(-2);
    }

    /* This block will run the `error_check_value` function.
     * If this function returns `false`, the code is terminated
     * with error code -3.
     */
    kill = error_check_value(0, 9);
    if (!kill) {
        exit(-3);
    }

    /* This block will run the `error_check_uniqueness` function.
     * If this function returns `false`, the code is terminated
     * with error code -4.
     */
    kill = error_check_uniqueness();
    if (!kill) {
        exit(-4);
    }
    display();
}

/* This function writes the data for the solved Sudoku
 * puzzle to an external file (based on `fname`).
 * The output is formated so that each line represents
 * a single element. For each element, you have three integers:
 * the row number, the column number, and the element value.
 */
void sudoku::write(const char *fname) {
    ofstream fout(fname);

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (0 < game[i][j]) {
                fout << i << " "
	             << j << " "
		     << game[i][j] << "\n";
            }
        }
    }

    fout.close();
}

/* This function drives the writing of the solution to
 * an external TXT file. It takes the initial file name (`fname`)
 * and adds "_solved.txt" to the end. Then, it calls the `write`
 * function above to actually perform the writing.
 */
void sudoku::write(const char *fname, const char *addon) {
    int N1 = strlen(fname);
    int N2 = strlen(addon);

    char *n_fname = new char[N1+N2+2];

    // strip .txt suffix, then concatenate _addon.txt
    strncpy(n_fname, fname, N1-4);
    strcpy(n_fname+N1-4, "_");
    strcpy(n_fname+N1-3, addon);
    strcpy(n_fname+N1-3+N2, ".txt");

    write(n_fname);

    delete [] n_fname;
}

/* This function displays the current contents of the
 * `game` array on the console with the appropriate formatting to make
 * the output look like a Sudoku puzzle.
 */
void sudoku::display() {
    cout << "| ----------------------------- |\n";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
	    if (j%3 == 0) 
	        cout << "|";
                cout << "  " << game[i][j];
	}
        cout << "  |\n";
	    if (i%3 == 2)
                cout << "| ----------------------------- |\n";
    }
}

/* This function uses recursion to actually solve
 * the Sudoku puzzle.
 */
int sudoku::solve(int row, int col) {
    /* If the element at (row, col) already has a value,
     * one of the following will happen.
     *
     * 1) If (row, col) is the final element in the puzzle,
     *    the function will return 1.
     * 2) Else, if the current element is not the last element
     *    in its row, a recursive call to `solve` is made with parameters
     *    row and col+1. If this returns 1, return 1.
     * 3) Else, if the current element is the last element in its
     *    row, a recursive call to `solve` is made with parameters
     *    row+1 and 0. If this returns 1, return 1.
     * 4) If none of these previous cases occur, return 0.
     */ 
    if (game[row][col] != 0) {
        if (row == 8 && col == 8) {
            return 1;
        }
        else if (col < 8) {
            if (solve(row, col+1) == 1) {
                return 1;
            }
        }
        else {
            if (solve(row+1, 0) == 1) {
                return 1;
            }
        }
        return 0;
    }
    /* vvals is a vector of ints that is used to
     * store the output of the `valid_values` function.
     * The for loop is used to set the initial values of vvals.
     * The `valid_values` function is used to update vvals so that
     * it stores the values that are valid according to the rules of
     * Sudoku.
     */
    vector<int> vvals;
    for (int i = 1; i <= 9; i++) {
        vvals.push_back(i);
    }
    valid_values(row, col, vvals);
    /* If there are no valid values for the current element,
     * a mistake was made earlier, and the code needs to backtrack
     * (done by returning 0).
     */
    if (vvals.empty()) {
        return 0;
    }
    /* This is the recursion escape condition. If you have only
     * one valid value for the final element in the puzzle,
     * the puzzle is solved, and the code needs to backtrack out of
     * the recursion. This is done by returning 1 here.
     */
    if (row == 8 && col == 8 && vvals.size() == 1) {
        game[row][col] = vvals.at(0);
        return 1;
    }
    // loop_vals is an iterator that is used to loop through the valid values.
    vector<int>::iterator loop_vals = vvals.begin();
    /* For each valid value (produced by `valid_values`), the current element
     * is set to that value, and the recursive `solve` function is called on
     * the next element. If this recursive `solve` function returns 1, this 
     * function returns 1. Otherwise, the value at the current element is reset,
     * and the next valid value is tested.
     */
    while (loop_vals != vvals.end()) {
        game[row][col] = *loop_vals;
        if (col < 8) {
            if (solve(row, col+1) == 1) {
                return 1;
            }
        }
        else {
            if (solve(row+1, 0) == 1) {
                return 1;
            }
        }
        game[row][col] = 0;
        ++loop_vals;
    }
    /* If the above loop does not result in a
     * successful solution, 0 is returned to show
     * that this path failed.
     */
    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if ((argc != 3) || (strcmp(argv[1], "-s") != 0) || strstr(argv[argc-1], ".txt") == NULL) {
        cerr << "usage: Sudoku -s game.txt\n";
	    exit(-1);
    }

    sudoku sudoku_game;

    if (strcmp(argv[1], "-s") == 0) {
        sudoku_game.read(argv[2]);
        sudoku_game.solve();
        sudoku_game.write(argv[2], "solved");
    }
}
