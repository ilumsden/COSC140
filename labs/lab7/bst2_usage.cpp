#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

#include "BST.h"

template <typename Iterator>
void print(Iterator i0, Iterator i1)
{
  while (i0 != i1) {
    cout << " " << *i0;
	++i0;
  }

  cout << "\n";
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cerr << "usage: bst2 datafile\n";
	exit(0);
  }

  int key;
  bst<int> T;

  ifstream fin(argv[1]);

  while (fin >> key)
    T.insert(key);

  fin.close();

  print(T.begin(), T.end());
}
