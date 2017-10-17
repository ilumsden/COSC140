#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>

/* Hashtable.cpp
 * Author: Ian Lumsden
 * Date: October 16, 2017
 *
 * This program reads an ascii text file an stores each word
 * and their line numbers in a hash table. It then allows the
 * user to enter words in the terminal. The program searches
 * the hash table for the word, and it uses the line numbers
 * stored in the hash table to print out every line that
 * contains the searched word.
 */

using namespace std;

/* The isstream and uint typedefs are used to shorten the 
 * declaration of an input string stream and an unsigned
 * integer respectively.
 */
typedef istringstream isstream;
typedef unsigned int uint;

// The class for defining a hash table to store the words and line numbers.
class hash_table {
    public:
        hash_table(int N=23);
	void insert(const string &, int);
	const vector<int> & find(const string &);
    private:
        /* This struct is what is actually
         * stored at each element in the hash table.
         * It consists of a string that stores the key and
         * a vector of ints to store the line numbers where
         * the key appears.
         */
	struct key_line {
            string key;
	    vector<int> line_nums;
            /* The inuse() function determines if
             * this key_line object contains data or
             * not. If data is stored, returns true.
             * Otherwise, returns false.
             */
	    bool inuse() {return (key == string())?false:true;}
            /* The == operator overload determines if
             * the string passed as an operator to the
             * argument is the same as the key.
             */
	    bool operator==(const string &s) {return (key == s);}
        };
	int hash(const string &);
	int nextprime(int);
	int qprobe(const string &);
	void resize();

        /* num_inuse stores the number of key_line elements
         * in the hash table. max_inuse stores the maximum
         * number of elements that the hash table can store
         * before needing to be resized.
         *
         * table is the variable used to store the data for 
         * the hash table.
         */ 
	int num_inuse;
	int max_inuse;

	vector<key_line> table;
};

/* Constructor for the hash table.
 * Fills the hash table with default
 * key_line objects, and sets the
 * values of num_inuse and max_inuse.
 */
hash_table::hash_table(int N) {
    table.assign(N, key_line());
    num_inuse = 0;
    max_inuse = N/2;
}

/* If the key (word) is already in the hash table,
 * this function adds the line number (passed as a parameter)
 * to the end of the list for the key. If the key isn't in
 * the hash table, the key variable at the correct table index
 * is set to the `key` parameter, and the line number is added
 * to the "end" of that index's list.
 */
void hash_table::insert(const string &key, int lnum) {
    /* The hash table index for the key is calculated
     * using a quadratic probe.
     */
    int index = qprobe(key);
    /* If the key is not already in the list, it is
     * added by setting the key variable at index to 
     * the key parameter and adding the line number to
     * the end of the vector at index.
     */
    if (!(table.at(index).inuse())) {
        table.at(index).key = key;
        table.at(index).line_nums.push_back(lnum);
        /* If adding a new element to the hash table
         * causes the number of elements in the table to be
         * greater than or equal to max_inuse, the hash table
         * is resized to insure that the quadratic probe will
         * always produce a unique index.
         */
	if (++num_inuse >= max_inuse) {
            resize();
	}
        return;
    }
    /* If the key is already present in the hash table,
     * the STL find() function is first used to insure that
     * the line number passed is not already in the key's
     * line number vector. If the line number is not
     * already present, it is added to the end of the vector.
     */
    if (table.at(index) == key) {
        vector<int>::iterator found = std::find(table.at(index).line_nums.begin(), table.at(index).line_nums.end(), lnum);
	if (found == table.at(index).line_nums.end()) {
            table.at(index).line_nums.push_back(lnum);
	}
    }
    return;
}

/* This function hashes the string key into an
 * index in the hash table using bit shifting on each
 * character in the string.
 */
int hash_table::hash(const string &key) {
    int index = 0;
    const char *c = key.c_str();
    while (*c) {
        index = ((index << 5) | (index >> 27)) + *c++;
    }
    return (uint)index % table.size();
}

/* This function calculates the first
 * prime number greater than N.
 */
int hash_table::nextprime(int N) {
    int i = 2;
    while (i*i <= N) {
        if (N % i == 0) {
            N++;
            i = 1;
	}
	i++;
    }
    return max(3, N);
}

/* This function performs a quadratic probe of
 * hash table indexes to either locate an empty index
 * for the key or to locate the key if it is already
 * in the hash table.
 */
int hash_table::qprobe(const string &key) {
    /* Determines a starting index for 
     * the probe using the hash() function.
     */
    int index = hash(key);
    int k = 0;
    /* While the current index isn't occupied
     * and doesn't contain the key, the index is
     * increased according to the rules for 
     * quadratic probing. Modulo division with the
     * table's size is done to insure the probe
     * always produces an index within the table's
     * size. Once the probe finds an empty index
     * or the key, it returns the current value of index.
     */
    while (table.at(index).inuse() && !(table.at(index) == key)) {
        index += 2*(++k) - 1;
	index = index % table.size();
    }
    return index;
}

// This function resizes the hash table.
void hash_table::resize() {
    /* First, the occupied contents of the hash
     * table are copied into a temporary vector.
     */
    vector<key_line> tmp;
    for (int i = 0; i < (int)table.size(); i++) {
        if (table.at(i).inuse()) {
            tmp.push_back(table.at(i));
	}
    }
    /* Then, the original table is resized to the
     * value returned by nextprime(). Also, num_inuse
     * is reset, and max_inuse is set to equal half of
     * the new table size.
     */
    int N = nextprime(2*table.size());
    table.assign(N, key_line());
    num_inuse = 0;
    max_inuse = N/2;
    /* Finally, the contents of the temporary vector
     * are copied back into the main hash table.
     */
    for (int i = 0; i < (int)tmp.size(); i++) {
        key_line &key = tmp.at(i);
	table[qprobe(key.key)] = key;
	num_inuse++;
    }
}

/* This function searches for the hash table element
 * represented by `key` and returns that element's
 * line number vector. If the key is not in the table,
 * an empty vector of ints is returned.
 */
const vector<int> & hash_table::find(const string &key) {
    const vector<int> lnums;
    int index = qprobe(key);
    return table.at(index).line_nums;
}

int main(int argc, char* argv[]) {
    /* This block of code ensures that the correct
     * number of command line arguments have been
     * provided.
     */
    if (argc < 2) {
        cerr << "Usage: ./Hashtable textfile" << endl;
	return -1;
    }
    hash_table tbl; //The hash table for storing lookup data for words
    ifstream fin; //An input file stream for reading the text file
    fin.open(argv[1]);
    isstream sin; //An input string stream for reading words from text lines
    vector<string> lines; //A vector of strings for storing the unedited text lines
    string line; //A string for using the current line.
    int line_num = 1; //An int representing the line number to be stored in the table
    /* This block of code reads through the ascii
     * text file (provided by argv[1] and read with
     * an input file stream) line by line. It first adds
     * the current line to the `lines` vector. Then,
     * it replaces all punctuation with spaces. The ispunct()
     * function is used to determine if a character is punctuation
     * or not. Then, a string stream is used to read each word
     * from the current line. Each word is added to the hash table
     * object `tbl` using the insert() function. 
     */
    while (getline(fin, line)) {
	lines.push_back(line);
        string::iterator start = line.begin();
	string::iterator end = line.end();
	while (start != end) {
            if (ispunct(*start)) {
                *start = ' ';
	    }
	    ++start;
	}
	sin.clear();
	sin.str(line);
	string word;
	while (sin >> word) {
            tbl.insert(word, line_num); 
	}
	line_num++;
    }
    fin.close();
    cout << "find> ";
    string input; //A string for storing the search word
    /* A vector of ints for storing the 
     * result of the hash table's find() function.
     */
    vector<int> lnums;
    /* This code block first receives a search term from the
     * console. Then, it obtains the line numbers where the
     * search term appears (saved to lnums). If the term is
     * in the hash table (and thus the text file), it prints out
     * the line numbers and actual lines where the term appears.
     * If the term is not in the table, nothing is printed. This
     * block exits only once stdin is closed (using CTRL-D).
     */
    while (cin >> input) {
        lnums = tbl.find(input);
        if (!lnums.empty()) {
            for (uint i = 0; i < lnums.size(); i++) {
                cout << setw(4) << lnums.at(i) << ":";
		cout << lines.at(lnums.at(i) - 1) << endl; 
	    }
	    cout << endl;
	}
	cout << "find> ";
    }
    return 0;
}
