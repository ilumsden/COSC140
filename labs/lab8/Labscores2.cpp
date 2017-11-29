#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <map>
#include <fstream>
#include <utility>
#include <cstring>

/* Labscores2.cpp
 * Author: Ian Lumsden
 * Date: 11/28/17
 *
 * Summary
 */

using namespace std;

class name_t {
    public:
        bool operator<(const name_t&) const;
        void print_name(int) const;
        const string & get(const string&) const;
        void set(const string &, const string&);
    private:
        // These strings store the first and last names for the "person" it
        // refers to.
        string lastname, firstname;
};

class labscores_t {
    public:
        labscores_t();
        void add_data(int);
        void set_stats();
        void print_labscores() const;
        void clear();
		const vector<float> get_stats() const;
    private:
        /* `scores` stores all the labscores for the corresponding "person".
         * `median` is an integer that stores the median of the sorted
         *     content of `scores`. If there are an even number of elements in
         *     `scores`, the last number of the first half of the vector is
         *     chosen for `median`.
         * `mean` is the arithmetic average of the integers in `scores`.
         *     It is stored as a float to ensure that data is not lost.
         */ 
        vector<int> scores;
        int median;
        float mean;
};

/* These typedefs are used to simplify the syntax for referring to
 * `map<name_t, labscores_t>` and `stringstream`.
 */
typedef map<name_t, labscores_t> map_t;
typedef stringstream sstream;

class heap_t {
	public:
        bool empty() const;
	    void add_data(const map_t::iterator&);
	    void heapify();
	    const map_t::iterator extract_top();
    private:
        struct data_t {
            bool operator<(const data_t&) const;
            map_t::iterator it;
		};
		vector<data_t> data;
};

/* This function allows for comparison between two name_t objects.
 * It will be used by the insert function for STL maps to order the
 * map content.
 */
bool name_t::operator<(const name_t& rhs) const {
    /* `this_name` and `rhs_name` are the formatted names stored in the
     * two `name_t` objects being compared (lastname, firstname).
     */
    string this_name = lastname + ", " + firstname;
    string rhs_name = rhs.get("last") + ", " + rhs.get("first");
    // These two strings are lexographically compared using the string's
    // less-than operator. The result of this comparison is returned.
    return (this_name < rhs_name);
}

/* This function prints the content of the name_t object with the 
 * desired formatting. This field will have a set width that will be
 * specified in `main`.
 */
void name_t::print_name(int name_width) const {
    string formated = lastname + ", " + firstname + " ..";
    cout << setfill('.') << setw(name_width) << left
         << formated << setfill(' ');
    return;
}

/* This function will access the name data specified by the parameter.
 * If the parameter is the string "last" or "lastname", the lastname data
 * will be returned. If the parameter is the string "first" or "firstname",
 * the firstname data will be returned. If parameter is neither of these,
 * an empty string is returned.
 */
const string & name_t::get(const string& field_name) const {
    if (field_name == "last" || field_name == "lastname") {
        return lastname;
    }
    else if (field_name == "first" || field_name == "firstname") {
        return firstname;
    }
    else {
        static const string str = "";
        return str;
    }
}

/* This function sets the member of the name_t object corresponding to
 * `field_name`. If `field_name` is the string "last" or "lastname", the
 * `lastname` member is set to `setter`. If `field_name` is the string
 * "first" or "firstname", the `firstname` member is set to `setter`.
 * If `field_name` is neither, nothing happens.
 */
void name_t::set(const string& setter, const string& field_name) {
    if (field_name == "last" || field_name == "lastname") {
        lastname = setter;
        return;
    }
    else if (field_name == "first" || field_name == "firstname") {
        firstname = setter;
        return;
    }
    else {
        return;
    }
}

// The labscores_t constructor. Simply sets everything to defaults.
labscores_t::labscores_t() {
    scores = vector<int>();
    median = 0;
    mean = 0;
}

/* This function adds a new peice of data (int) to the `labscores_t`
 * object. This is simply done by pushing back the data into the
 * `scores` vector. Sorting the data is NOT done in this function.
 */
void labscores_t::add_data(int data) {
    scores.push_back(data);
}

/* This function sorts the contents of `scores`. Then, it determines the
 * median (the process depends on whether the size of `scores` is even or
 * odd). Finally, it sums the contents of `scores` (with the STL
 * `accumulate` function) and calculates the mean.
 */
void labscores_t::set_stats() {
    sort(scores.begin(), scores.end());
    int N = scores.size();
    if (N % 2 != 0) {
        median = scores[(N/2) + 1];
    }
    else {
        median = scores[(N-1)/2];
    }
    int sum = accumulate(scores.begin(), scores.end(), 0);
    mean = (float)sum / scores.size();
}

/* This function prints the `labscores_t` object's data with the
 * desired formatting. The formatting is as follows:
 * "content_of_scores_vector : median mean" (with only one digit beyond
 * the decimal point displayed).
 */
void labscores_t::print_labscores() const {
    for (int i = 0; i < (int)scores.size(); i++) {
        cout << " " << scores[i];
    }
    cout << " : " << median << " " << fixed << setprecision(1) << mean;
    return;
}

// This function resets the `labscores_t` object so that it may be reused.
void labscores_t::clear() {
    scores.clear();
    median = 0;
    mean = 0;
}

const vector<float> labscores_t::get_stats() const {
    vector<float> stats;
	stats.push_back((float) median);
	stats.push_back(mean);
	return stats;
}

bool heap_t::empty() const {
    return (data.size() == 0);
}

void heap_t::add_data(const map_t::iterator& newdata) {
    data_t newelem;
	newelem.it = newdata;
	data.push_back(newelem);
	return;
}

void heap_t::heapify() {
    make_heap(data.begin(), data.end());
    return;
}

const map_t::iterator heap_t::extract_top() {
	map_t::iterator top = data[0].it;
    pop_heap(data.begin(), data.end());
	data.pop_back();
	return top;
}

bool heap_t::data_t::operator<(const data_t& rhs) const {
    vector<float> lhs_stats = it->second.get_stats();
	vector<float> rhs_stats = rhs.it->second.get_stats();
	if (lhs_stats[1] < rhs_stats[1]) {
        return true;
	}
	else if (lhs_stats[1] == rhs_stats[1]) {
	    int lhs_median = (int)(lhs_stats[0]);
	    int rhs_median = (int)(rhs_stats[0]);
	    if (lhs_median < rhs_median) {
            return true;
	    }
		else if (lhs_median == rhs_median) {
            string lhsname = it->first.get("last") + ", " + it->first.get("first");
			string rhsname = rhs.it->first.get("last") + ", " + rhs.it->first.get("last");
			if (lhsname < rhsname) {
                return true;
			}
		}
	}
    return false;
}

int main(int argc, char *argv[]) {
    /* If there aren't enough command line arguments or if the
     * first user-defined command line argument is not "-byname",
     * a usage mesage is printed to the stderr, and the program exits
     * by returning -1.
     */
    if (argc < 3 || (strcmp(argv[1], "-byname") != 0 && strcmp(argv[1], "-byrank") != 0 && strcmp(argv[1], "-top10") != 0)) {
        cerr << "Usage: Labscores1 -byname|-byrank|-top10 datafile.txt\n";
        return(-1);
    }
    // This block defines the map, name_t, labscores_t, and ifstream
    // objects that will be used for parsing the contents of argv[2].
    map_t namescores;
    name_t name;
    labscores_t scores;
    ifstream fin;
    fin.open(argv[2]);
    /* If the code was unable to open the file specified by argv[2],
     * a usage message is printed to stderr, and the program exits by
     * returning -1.
     */
    if (fin.fail()) {
        cerr << "Usage: Labscores1 -byname|-byrank|-top10 datafile.txt\n";
        return(-2);
    }
    // The strings needed for parsing the lines and names from argv[2].
    string line, first, last;
    // The integer needed for parsing the scores from argv[2].
    int curr_score;
    /* `max_namelength` is an integer that stores the length of the largest
     * formatted name. It will be used to specify the width of the content
     * printed by the `name_t::print_name` function.
     */
    int max_namelength = 0;
    // The stringstream needed to extract the name and score data from lines.
    sstream sin;
    /* This loop reads content from argv[2] line-by-line. The current line
     * is stored in `line`. Then, the first and last names are obtained from
     * `line`.
     */
    while (getline(fin, line)) {
        sin.clear();
        scores.clear();
        sin.str(line);
        sin >> first;
        sin >> last;
        /* This block determines if the current name is longer than
         * `max_namelength` after being formatted. If it is, `max_namelength`
         * is set to the current name's size.
         */
        if ((int)(first.size() + last.size() + 5) > max_namelength) {
            max_namelength = first.size() + last.size() + 5;
        }
        /* The rest of this while loop sets the first- and last-name members
         * of the name_t object (`name`) to the first and last names parsed
         * from argv[2]. Then, the stringstream is used to read the scores
         * from the current line. They are added to the labscores_t object
         * (`scores`). After all the data is read from the line, the stats
         * for the score data are calculated (`labscores_t::set_stats`).
         * Finally, the name_t and labscores_t objects for this line are
         * paired together, and the pair is added to the map.
         */
        name.set(first, "first"); 
        name.set(last, "last");
        while (sin >> curr_score) {
            scores.add_data(curr_score);
        }
        scores.set_stats();
        namescores.insert(make_pair(name, scores));
    }
    map_t::iterator curr = namescores.begin();
    map_t::iterator end = namescores.end();
	if (strcmp(argv[1], "-byname") == 0) {
        while (curr != end) {
            curr->first.print_name(max_namelength);
            curr->second.print_labscores();
            cout << endl;
            ++curr;
        }
	}
	else {
		heap_t scoreheap;
        while (curr != end) {
            scoreheap.add_data(curr);
			++curr;
		}
		scoreheap.heapify();
		map_t::iterator top;
		int loop_num = 0;
		while (!scoreheap.empty()) {
            top = scoreheap.extract_top();
            top->first.print_name(max_namelength);
            top->second.print_labscores();
            cout << endl;
			loop_num++;
			if (strcmp(argv[1], "-top10") == 0 && loop_num == 10) {
                break;
			}
		}
	}
    return 0;
}
