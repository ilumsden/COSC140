#include <iostream>
#include <cstdlib>

using namespace std;

/* This is my factorial function for this part.
 * If you have a negative number or 0, the function
 * will return the number inputted.
 * If a positive number is passed as a parameter,
 * the factorial will be calculated by multiplying the
 * input by the result of recursively calling the 
 * factorial function with num - 1.
 */
int factorial(int num) {
    if (num <= 0) {
        return num;
    }
    else if (num == 1) {
        return 1;
    }
    else {
        return num * factorial(num - 1);
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int factorial_n = factorial(n);
    cout << "factorial = " << factorial_n << endl;
}
