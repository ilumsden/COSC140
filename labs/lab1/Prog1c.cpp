/* Prog1c.cpp
 * Author: Ian Lumsden
 * Date August 30, 2017
 *
 * This program is the same as Prog1b.cpp.
 * It reads user input (ints) from the console and
 * calculates the sum, min, max, and number of the inputs.
 */

#include<iostream>

using namespace std;

/* This class handles all stat calculations 
 * (sum, min, max, num), and it contains a function
 * to print these stats to the console.
 */
class Stats {
    public:
		Stats();
        void push(int);
		void print();
	private:
		int min, max;
		int sum;
		int num;
};

/*Constructor for the Stats class.
 * This sets sum and num to 0.
 */
Stats::Stats() {
    sum = 0;
	num = 0;
}

/* This function takes an integer (one of the
 * user inputs) and uses it to update sum, min,
 * max, and num.
 */
void Stats::push(int val) {
    sum += val;
	if (num == 0) {
        min = val;
		max = val;
	}
	else {
        if (val < min) {
            min = val;
		}
		else if (val > max) {
            max = val;
		}
	}
	num++;
	return;
}

/* This function formats and prints
 * all the calculated stats (member 
 * variables) to the console.
 */
void Stats::print() {
    cout << "N   = " << num << endl;
	cout << "sum = " << sum << endl;
	cout << "min = " << min << endl;
	cout << "max = " << max << endl;
	return;
}

int main() {
    int num; // A variable to store a single user input
	Stats s1; // A Stats object to calculate the desired statistics
	/* While stdin is open, this block
	 * reads integers one at a time from
	 * the console and passes each one to the
	 * Stats object
	 */
	while (cin >> num) {
        s1.push(num);
	}
	s1.print();
	return 0;
}
