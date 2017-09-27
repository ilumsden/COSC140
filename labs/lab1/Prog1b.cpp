/* Prog1b.cpp
 * Author: Ian Lumsden
 * Date: August 30, 2017
 *
 * This program reads a series of user-provided
 * integers from the console and calculates the sum
 * of the inputs, the minimum input, the maximum input,
 * and the number of inputs. It then prints these 
 * statistics to the console.
 */

#include<iostream>

using namespace std;

int main() {
    int val; //Stores a single input integer
	int sum = 0;
	int num = 0;
	int min;
	int max;
	/* While the stdin stream (cout/cin) is open,
	 * this block adds the next input to sum. Then,
	 * on the first iteration of the loop, this block
	 * sets min and max equal to the first input.
	 * If the loop is not on its first iteration, this block
	 * will determine if val is less than min or greater than
	 * max, and it will update min and/or max accordingly.
	 * Finally, this block will increment num.
	 */
	while (cin >> val) {
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
	}
	// Prints the calculated stats to the console
    cout << "N   = " << num << "\n";
	cout << "sum = " << sum << "\n";
	cout << "min = " << min << "\n";
	cout << "max = " << max << "\n";
	return(0);
}

