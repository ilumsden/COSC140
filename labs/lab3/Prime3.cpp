#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>

/* Prime3.cpp
 * Author: Ian Lumsden
 * Date: October 4, 2017
 *
 * This program produces a list of N random numbers
 * (N is either 10 or a user-specified value) and
 * determines how many of those numbers are prime.
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
     * is present in the list of primes by using a binary search. 
     * If it is not, this function returns false. Otherwise, it returns true.
     */
    bool exists = binary_search(v.begin(), v.end(), number);
    if (exists) {
        return true;
    }
    return false;
}

/* This function returns a random number between
 * 1 and 100.
 */
int random_number() {
    return ((rand() % 100) + 1);
}

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

int main(int argc, char *argv[]) {
    /* This code block determines if
     * there is a user-defined command-line
     * argument. If there is, the argument at
     * argv[1] is used to set the value of N.
     * Otherwise, N is set to 10. N is then used
     * to seed a random number generator.
     */
    int N = 10;
    if (argc == 2) {
        N = atoi(argv[1]);
    }

    srand(N);

    /* num_list is a vector used to store all the randomly
     * generated numbers produced by the random_number function.
     * prime_list is a vector used to store bools representing
     * whether the numbers in num_list are prime or not.
     * pfunc is a functor (isprime object) used to determine if
     * a number is prime.
     */
    vector<int> num_list(N);
    vector<bool> prime_list(N);
    isprime pfunc;

    /* The generate function will fill num_list with random numbers
     * produced by the random_number() function. The transform
     * function will fill prime_list with bools produced by the 
     * function operator overload represented by pfunc.
     */
    generate(num_list.begin(), num_list.end(), random_number);
    transform(num_list.begin(), num_list.end(), prime_list.begin(), pfunc);

    /* The rest of this code determines how many numbers in
     * num_list are prime (using prime_list). Then, it prints
     * out a statement saying how many primes are present.
     */
    int c = count(prime_list.begin(), prime_list.end(), true);
	
    cout << "Sequence contains " << c << " prime numbers.\n";
}
