#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class isprime {
  public:
    isprime() {v.push_back(2);}
    bool operator()(int);
  private:
    vector<int> v;
	void growlist(int);
};

bool isprime::operator()(int number) {
    if (number > v.back()) {
        growlist(number);
	}
	vector<int>::iterator loc = find(v.begin(), v.end(), number);
	if (loc == v.end()) {
        return false;
	}
	return true;
}

void isprime::growlist(int N) {
	bool prime = false;
	int num = v.back() + 1;
	while (!prime || num < N) {
		prime = true;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                prime = false;
				break;
			}
		}
		if (prime) {
            v.push_back(num);
		}
		num++;
	}
}

int main()
{
	isprime pcheck;
	int number;

	while (cin >> number) {
	  if (pcheck(number))
	    cout << number << " is a prime number" << endl;
	}
	return 0;
}
