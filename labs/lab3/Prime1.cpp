#include <iostream>
#include <cmath>

using namespace std;

bool isprime(int number) {
	if (number < 2) {
        return false;
	}
	for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            return false;
		}
	}
	return true;
};

int main() {
	int number;

	while (cin >> number) {
	    if (isprime(number)) {
            cout << number << " is a prime number." << endl;
		}
	}
	return 0;
}
