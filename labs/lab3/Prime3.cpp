#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class isprime {
  public:
    isprime() {v.push_back(2);}
    bool operator()(int);

  private:
    vector<int> v;
    void growlist(int);
};

bool isprime::operator()(int number)
{
    if (number > v.back()) {
        growlist(number);
    }
    bool exists = binary_search(v.begin(), v.end(), number);
    if (exists) {
        return true;
    }
    return false;
}

int random_number()
{
	return ...
}

int main(int argc, char *argv[])
{
	int N = 10;
        if (argc == 2) {
            //Add something here to assert that argv[1] is int
            N = argv[1];
        }

	srand(N);

	vector<int> num_list(N);
	//vector< ? > ...

	generate(num_list.begin(), num_list.end(), random_number());
	transform( ... );

	int c = count( ... );
	
	cout << useful info
}
