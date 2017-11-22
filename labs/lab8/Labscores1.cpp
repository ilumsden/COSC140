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

using namespace std;

class name_t {
    public:
        name_t(string&, string&);
		bool operator<(const name_t&) const;
        void print_name(int) const;
		const string & get(const string&) const;
		void set(const string &, const string&);
    private:
        string lastname, firstname;
};

class labscores_t {
    public:
        labscores_t();
		void add_data(int);
		void set_stats();
		void print_labscores() const;
		void clear();
    private:
        vector<int> scores;
		int median;
		float mean;
};

name_t::name_t(string& first, string& last) {
    firstname = first;
	lastname = last;
}

bool name_t::operator<(const name_t& rhs) const {
    string this_name = lastname + ", " + firstname;
	string rhs_name = rhs.get("last") + ", " + rhs.get("first");
	return (this_name < rhs_name);
}

void name_t::print_name(int name_width) const {
    cout << setfill('.') << setw(name_width)
		 << lastname << ", " << firstname << " "
		 << setfill(' ') << "..";
	return;
}

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

labscores_t::labscores_t() {
    scores = vector<int>();
	median = 0;
	mean = 0;
}
		
void labscores_t::add_data(int data) {
    scores.push_back(data);
}
		
void labscores_t::set_stats() {
    sort(scores.begin(), scores.end());
	int N = scores.size();
	if (N % 2 != 0) {
        median = scores[(N/2) + 1];
	}
	else {
        median = scores[N/2];
	}
	int sum = accumulate(scores.begin(), scores.end(), 0);
	mean = (float)sum / scores.size();
}
		
void labscores_t::print_labscores() const {
    for (int i = 0; i < (int)scores.size(); i++) {
        cout << " " << scores[i];
	}
	cout << " : " << median << " " << setprecision(1) << mean;
	return;
}

void labscores_t::clear() {
    scores.clear();
	median = 0;
	mean = 0;
}

typedef map<name_t, labscores_t> map_t;
typedef stringstream sstream;

int main(int argc, char *argv[]) {
    if (argc < 3 || strcmp(argv[1], "-byname") != 0) {
        cerr << "Labscores1 -byname datafile.txt\n";
		return(-1);
	}
    map_t namescores;
	name_t name;
	labscores_t scores;
    ifstream fin;
	fin.open(argv[2]);
	if (fin.fail()) {
        cerr << "Labscores1 -byname datafile.txt\n";
		return(-2);
	}
	string line, first, last;
	int curr_score;
	int max_namelength = 0
	sstream sin;
	while (getline(fin, line)) {
        sin.clear();
		scores.clear();
		sin.str(line);
        sin >> first;
		sin >> last;
		if ((first.size() + last.size() + 5) > max_namelength) {
            max_namelength = first.size() + last.size() + 5;
		}
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
	while (curr != end) {
        curr->first.print_name(max_namelength);
		curr->second.print_labscores();
		cout << endl;
		++curr;
	}
	return 0;
}
