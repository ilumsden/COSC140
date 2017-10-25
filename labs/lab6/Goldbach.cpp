#include <...>
using namespace std;

typedef enum { FIRST_SOLUTION, ALL_SOLUTIONS } program_mode_t;

class prime_partition {
  public:
      prime_partition
	// function operator

  private:
    // miscl member functions
    void expand_plist(int);

	program_mode_t mode;

    // miscl member data
    vector<int> plist;
};


int main(int argc, char *argv[])
{
  // commandline argument parsing

  program_mode_t mode;

  // set mode

  prime_partition goldbach(mode);

  int number;
  while (1) {
	cout << "number = ";
    cin >> number;
	if (cin.eof())
	  break;
	
	goldbach(number);
  }

  cout << "\n";
}
