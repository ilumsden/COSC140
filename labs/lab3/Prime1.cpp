#include <iostream>
#include <cmath>

/* Prime1.cpp
 * Author: Ian Lumsden
 * Date: October 2, 2017
 *
 * This program receives integers provided
 * by the user from the terminal, and determines
 * whether or not those integers are prime by performing
 * modulo division between the each number and every number
 * in the range [2, sqrt(number)]. If a number is prime,
 * a message is printed to the console stating that
 * the number is prime. Nothing happens if the number
 * is not prime.
 */

using namespace std;

/* This function determines if a number
 * is prime or not using the following rules:
 *    1) If the number is less than 2, it is
 *       not prime.
 *    2) If the number can be evenly divided
 *       by any number between 2 and its square
 *       root, it is not prime.
 */
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

    /* Every time there is user input from
     * the console, the isprime() function is
     * called, with the user-inputed number as a
     * parameter. If the number is prime, a line
     * is printed to the console that tells the 
     * user that the number is prime.
     */
    while (cin >> number) {
        if (isprime(number)) {
            cout << number << " is a prime number." << endl;
	}
    }
    return 0;
}
