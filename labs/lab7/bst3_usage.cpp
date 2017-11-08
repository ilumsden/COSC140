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
  bool verbose = true;

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

  int key0, key1;
  bst<int>::iterator p0, p1;

  print(T.begin(), T.end());

  while (!T.empty()) {
    cout << "Print [key0:key1]: ";
    cin >> key0 >> key1; 

	if (cin.eof())
	  break;

	if (key1 < key0)
	  continue;

	p0 = T.lower_bound(key0);
    p1 = T.upper_bound(key1);

	if (verbose) {
	  cout << "*** lower bound ";
      if (p0 != T.end()) cout << *p0;
	  else               cout << "INF";
	  cout << "\n";
  
	  cout << "*** upper bound ";
      if (p1 != T.end()) cout << *p1;
	  else               cout << "INF";
	  cout << "\n";
	}

    print(p0, p1);
  }

  cout << "\n";
}
