#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

typedef istringstream isstream;
typedef unsigned int uint;

class hash_table {
    public:
        hash_table(int N=23);
		void insert(const string &, int);
		const vector<int> & find(const string &);
	private:
		struct key_line {
            string key;
			vector<int> line_nums;
			bool inuse() {return (key == string())?false:true;}
			bool operator==(const string &s) {return (key == s);}
		};
		int hash(const string &);
		int nextprime(int);
		int qprobe(const string &);
		void resize();

		int num_inuse;
		int max_inuse;

		vector<key_line> table;
};

hash_table::hash_table(int N) {
    table.assign(N, key_line());
    num_inuse = 0;
	max_inuse = N/2;
}

void hash_table::insert(const string &key, int lnum) {
    int index = qprobe(key);
	if (table.at(index) == string()) {
		key_line new_key;
		new_key.key = key;
		new_key.line_nums.push_back(lnum);
        table[index] = new_key;
		if (++num_inuse >= max_inuse) {
            resize();
		}
	}
	if (table.at(index) == key) {
		vector<int>::iterator found = std::find(table.at(index).line_nums.begin(), table.at(index).line_nums.end(), lnum);
		if (found == table.at(index).line_nums.end()) {
            table.at(index).line_nums.push_back(lnum);
		}
	}
}

int hash_table::hash(const string &key) {
    int index = 0;
	const char *c = key.c_str();
	while (*c) {
        index = ((index << 5) | (index >> 27)) + *c++;
	}
	return (uint)index & table.size();
}

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

int hash_table::qprobe(const string &key) {
    int index = hash(key);
	int k = 0;
	while (table.at(index).inuse() && !(table.at(index) == key)) {
        index += 2*(++k) - 1;
		index = index % table.size();
	}
	return index;
}

void hash_table::resize() {
    vector<key_line> tmp;
	for (int i = 0; i < (int)table.size(); i++) {
        if (table.at(i).inuse()) {
            tmp.push_back(table.at(i));
		}
	}
	int N = nextprime(2*table.size());
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2;
	for (int i = 0; i < (int)tmp.size(); i++) {
        key_line &key = tmp.at(i);
		table[qprobe(key.key)] = key;
		num_inuse++;
	}
}

const vector<int> & hash_table::find(const string &key) {
    //vector<int> lnums;
    int index = qprobe(key);
    if (table.at(index) == key) {
        return table.at(index).line_nums;
	}
	return const vector<int>();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
		cerr << "Usage: ./Hashtable textfile" << endl;
		return -1;
	}
	hash_table tbl;
	ifstream fin;
	fin.open(argv[1]);
	isstream sin;
	vector<string> lines;
	string line;
	int line_num = 1;
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
		sin.str(line);
		string word;
		while (sin >> word) {
            tbl.insert(word, line_num); 
		}
		sin.str("");
		line_num++;
    }
	cout << "user> ";
	string input;
	vector<int> lnums;
	while (cin >> input) {
        lnums = tbl.find(input);
		if (lnums.empty()) {
            cout << input << " not found.\n" << endl;
		}
		else {
            for (int i = 0; i < (uint)lnums.size(); i++) {
                cout << setw(4) << lnums.at(i) << ":";
				cout << lines.at(lnums.at(i) - 1) << endl; 
			}
			cout << endl;
		}
	}
	return 0;
}
