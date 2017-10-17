#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class sudoku {
  public:
	sudoku();

	void solve();

    void read(const char *);
    void write(const char *);
    void write(const char *, const char *);

  private:
    int solve(arguments);

    // various support functions 
    // error_check_value()
    // error_check_uniqueness()

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

  // call recursive computation

  display();
  
  // error check data values
  // error check uniqueness
  // exit if errors detected
}

void sudoku::read(const char *fname) {
  cout << "READ\n";

  ifstream fin(fname);
    
  int i, j, v;

  while (fin >> i >> j >> v) {
    // error check grid indices
    game[i][j] = v;
  }

  fin.close();

  // exit if bad grid indices

  // error check data values
  // error check uniqueness
  // exit if errors detected
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

int sudoku::solve(arguments) {
  // if solution found, 
  //   return solution-found
  //
  // set cell index (i,j)
  // determine valid values 
  // if no valid values left,
  //   return road-to-nowhere
  //
  // iterate thru valid values 
  //   game[i][j] = next value
  //   if solve(arguments) == solution-found
  //     return solution-found
  //
  // reset: game[i][j] = 0
  // return road-to-nowhere
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  if ((argc != 3) ||
      (strcmp(argv[1], "-s") != 0) ||
	  strstr(argv[argc-1], ".txt") == NULL) {
    cerr << "usage: Sudoku -s game.txt\n";
	exit(0);
  }

  sudoku sudoku_game;

  if (strcmp(argv[1], "-s") == 0) {
    sudoku_game.read(argv[2]);
    sudoku_game.solve();
    sudoku_game.write(argv[2], "solved");
  }
}
