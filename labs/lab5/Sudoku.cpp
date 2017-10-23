#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

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

        int game[9][9];
};

sudoku::sudoku() { 
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++)
            game[i][j] = 0;
    }
}

void sudoku::solve() {
    cout << "SOLVE\n";
    int solve_success = solve(0, 0);
    if (solve_success == 0) {
        cerr << "There's an issue with the recursive solve function.\n"
             << "It failed to successfully solve this problem.\n";
        exit(-7);
    }
    display();
  
    if (!error_check_value(1, 9)) {
        exit(-5);
    }
    if (!error_check_uniqueness()) {
        exit(-6);
    }
}

void sudoku::valid_values(int row, int col, vector<int> &valid) {
    vector<int>::iterator found;
    if (game[row][col] != 0) {
        valid.clear();
        valid.push_back(game[row][col]);
        return;
    }
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

bool sudoku::error_check_value(int min, int max) {
    bool valid = true;
    bool final_valid = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            valid = (game[i][j] >= min && game[i][j] <= max)?true:false;
	    if (valid == false) {
		cerr << i << " " << j << " " << game[i][j] << " illegal value\n";
		final_valid = false;
	    }
	}
    }
    return final_valid;
}

bool sudoku::error_check_uniqueness() {
    bool unique = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (game[i][j] == 0) {
                continue;
	    }
	    else {
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

void sudoku::read(const char *fname) {
    cout << "READ\n";

    ifstream fin(fname);
    
    int i, j, v;
    bool kill = false;

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

    if (kill) {
        exit(-2);
    }

    kill = error_check_value(0, 9);
    if (!kill) {
        exit(-3);
    }

    kill = error_check_uniqueness();
    if (!kill) {
        exit(-4);
    }
    display();
}

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

int sudoku::solve(int row, int col) {
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
    vector<int> vvals;
    for (int i = 1; i <= 9; i++) {
        vvals.push_back(i);
    }
    valid_values(row, col, vvals);
    if (vvals.empty()) {
        return 0;
    }
    if (row == 8 && col == 8 && vvals.size() == 1) {
        game[row][col] = vvals.at(0);
        return 1;
    }
    vector<int>::iterator loop_vals = vvals.begin();
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
