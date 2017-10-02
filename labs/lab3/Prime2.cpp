#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

/* Prime1.cpp
 * Author: Ian Lumsden
 * Date: October 2, 2017
 *
 * This program receives integers provided
 * by the user from the terminal, and determines
 * whether or not those integers are prime by seeing
 * if it is present in a list of encountered primes. If
 * the current number is greater than the largest prime
 * in the list, the program expands the list by finding
 * all primes between the end of the list and the prime that
 * is greater than or equal to the number. If a number is prime,
 * a message is printed to the console stating that
 * the number is prime. Nothing happens if the number
 * is not prime.
 */

using namespace std;

/* A function class that is used to determine
 * if a number is prime or not.
 */
class isprime {
    public:
        isprime() {v.push_back(2);}
        bool operator()(int);
    private:
        /* This vector stores a list of all
         * previously encountered prime numbers.
         */
        vector<int> v;
	void growlist(int);
};

/* This function determines if a number is prime
 * by seeing if it is present in member v, a list of
 * all previously encountered prime numbers.
 */
bool isprime::operator()(int number) {
    /* If the number being checked is greater than
     * this largest prime in v, the growlist function
     * is called, with number passed as a parameter.
     */
    if (number > v.back()) {
        growlist(number);
    }
    /* This code block determines whether or not number
     * is present in the list of primes. If it is not, this
     * function returns false. Otherwise, it returns true.
     */
    vector<int>::iterator loc = find(v.begin(), v.end(), number);
    if (loc == v.end()) {
        return false;
    }
    return true;
}

/* A function for expanding the list of primes
 * so that it includes all primes up to the prime
 * whose value is greater than or equal to N.
 */
void isprime::growlist(int N) {
    bool prime = false;
    int num = v.back() + 1;
    /* The combination of the while loop and
     * the num++ statement at the end of the while
     * loop causes the code to go through every number
     * between v.back() + 1 and the first prime 
     * greater than or equal to N.
     */
    while (!prime || num < N) {
	prime = true;
        /* This for loop determines whether or not
         * the current value of num is prime. To do so,
         * it loops through every number between 2
         * and sqrt(num) and performs modulo division
         * between num and the current looped number.
         * If the modulo division returns 0, num is
         * not prime, and the variable "prime" is set to 
         * false. Otherwise, "prime" will be true at the
         * end of the loop.
         */ 
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                prime = false;
		break;
	    }
	}
        /* If the current number of num is prime
         * (as stated by the variable "prime"), it is
         * added to v (the list of encountered primes).
         */
	if (prime) {
            v.push_back(num);
	}
	num++;
    }
}

int main() {
    /* "pcheck" is a function object used to
     * determine if a number is prime.
     * "number" stores the current user-inputed
     * value.
     */
    isprime pcheck;
    int number;

    /* While stdin is open, numbers from the console
     * will be read in and stored in "number."
     * The pcheck() function is then called with "number"
     * as a parameter. If this function returns true, 
     * the code prints a message to the console to state
     * that the number is prime. This continues until
     * stdin is closed.
     */
    while (cin >> number) {
	if (pcheck(number)) {
	    cout << number << " is a prime number" << endl;
        }
    }
    return 0;
}
