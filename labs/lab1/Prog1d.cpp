/* Prog1d.cpp
 * Author: Ian Lumsden
 * Date: September 6, 2017
 *
 * This program encodes or decodes (based on argv) user input
 * from the terminal using a given shift value (also from argv).
 * For encoding, the program loops through the characters in
 * each line and adds the shift value to the character's ascii
 * value. However, if the character's shifted ascii leaves its
 * character range (capital ascii > 90, lower case ascii > 122),
 * it around to the beginning of the range. Decoding is the same,
 * except it subtracts the shift value from the ascii.
 */

#include<iostream>
#include<string>
#include<cctype>
#include<cstring>
#include<cstdlib>

using namespace std;

//See below
void encode(string&, int);
void decode(string&, int);

int main(int argc, char *argv[]) {
	// Confirms that the command line arguments are valid
    if (argc != 3 || atoi(argv[2]) < 0 || atoi(argv[2]) > 9) {
        cerr << "Usage: ./Prog1d -decode|encode 0-9" << endl;
		return(-1);
	}
	else if (strcmp(argv[1], "-encode")) {
        if (strcmp(argv[1], "-decode")) {
            cerr << "Usage: ./Prog1d -decode|encode 0-9" << endl;
		    return(-1);
		}
	}
	//The shfit for the character ascii value
	int shift_num = atoi(argv[2]);
	//A string to store the current line grabbed by getline()
	string curr_line;
	/* If the first user-given command line argument
	 * is -encode, this block will loop through the lines
	 * of text entered by the user and call the encode function
	 * with them. If the command line argument is -decode, it
	 * will do the same thing, but with the decode function
	 */
	if (!strcmp(argv[1], "-encode")) {
        while (getline(cin, curr_line)) {
            encode(curr_line, shift_num);
			cout << curr_line << endl;
		}
	}
	else {
        while (getline(cin, curr_line)) {
            decode(curr_line, shift_num);
			cout << curr_line << endl;
		}
	}
	return 0;
}

//The function for encoding a string
void encode(string &line, int shift_num) {
	//A string to temporarily store the encoded line
    string enc_line = "";
	//Loops through the characters of the string
	for (int i = 0; i < line.length(); i++) {
		//The current character
        char c = line.at(i);
		//c's ascii value 
		int ascii = (int)c;
		//If the character is not a letter, it's just added back to the encoded string.
        if (!isalpha(ascii)) {
            enc_line += c;
	    }
		/* If the character is an upper case character,
		 * check the following:
		 *   1. If ascii + shift_num > 90, calculate the difference
		 *      between the sum and 90, and store the result in
		 *      new_shift. Then, save the looped ascii to ascii, and
		 *      cast ascii to a char. Finally, add the new char to 
		 *      the end of enc_line.
		 *   2. If not 1, add the shift to the ascii value. Then,
		 *      cast ascii to a string, and add it to enc_line.
		 */
		else if (isupper(ascii)) {
            if ((ascii + shift_num) > 90) {
				int new_shift = (ascii + shift_num) - 90;
				ascii = 64 + new_shift;
				c = static_cast<char>(ascii);
				enc_line += c;
			}
		    else {
                ascii += shift_num;
				c = static_cast<char>(ascii);
				enc_line += c;
			}
		}
		/* Same process as the above code block, but uses the
		 * ascii comparisons for lower case letters instead of
		 * upper case letters.
		 */
		else {
            if ((ascii + shift_num) > 122) {
                int new_shift = (ascii + shift_num) - 122;
				ascii = 96 + new_shift;
				c = static_cast<char>(ascii);
				enc_line += c;
			}
			else {
                ascii += shift_num;
				c = static_cast<char>(ascii);
				enc_line += c;
			}
		}
	}
	//Save enc_line to line to access the encoding in main()
	line = enc_line;
	return;
}

//The function for decoding the string
void decode(string &line, int shift_num) {
	//A string to temporarily store the encoded line
    string dec_line = "";
	//Loops through the characters of the string
	for (int i = 0; i < line.length(); i++) {
		//The current character
        char c = line[i];
		//c's ascii value 
		int ascii = (int)c;
		//If the character is not a letter, it's just added back to the encoded string.
		if (!isalpha(ascii)) {
            dec_line += c;
		}
		/* If the character is an upper case character,
		 * check the following:
		 *   1. If ascii - shift_num < 65, calculate the difference
		 *      between 90 and the difference, and store the result in
		 *      new_shift. Then, save the looped ascii to ascii, and
		 *      cast ascii to a char. Finally, add the new char to 
		 *      the end of enc_line.
		 *   2. If not 1, subtract the shift to the ascii value. Then,
		 *      cast ascii to a string, and add it to enc_line.
		 */

		else if (isupper(ascii)) {
            if ((ascii - shift_num) < 65) {
                int new_shift = 65 - (ascii - shift_num);
				ascii = 91 - new_shift;
				c = static_cast<char>(ascii);
				dec_line += c;
			}
			else {
                ascii -= shift_num;
				c = static_cast<char>(ascii);
				dec_line += c;
			}
		}
         /* Same process as the above code block, but uses the
		 * ascii comparisons for lower case letters instead of
		 * upper case letters.
		 */

		else {
            if ((ascii - shift_num) < 97) {
                int new_shift = 97 - (ascii - shift_num);
				ascii = 123 - new_shift;
				c = static_cast<char>(ascii);
				dec_line += c;
			}
			else {
                ascii -= shift_num;
				c = static_cast<char>(ascii);
				dec_line += c;
			}
		}
	}
	//Save enc_line to line to access the encoding in main()
	line = dec_line;
	return;
}
