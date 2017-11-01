#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef enum { FIRST_SOLUTION, ALL_SOLUTIONS } program_mode_t;

class prime_partition {
  public:
      prime_partition(program_mode_t &);
	  void operator()(int);
  private:
	bool gen_partition_first(int, int, vector<int>&);
    void expand_plist(int);
    void prev_primes(int, vector<int>&);
	program_mode_t mode;
    vector< vector<int> > partition_list;
    vector<int> plist;
};

prime_partition::prime_partition(program_mode_t & usr_mode) {
    mode = usr_mode;
}

void prime_partition::operator()(int usr_num) {
    if (plist.back() < usr_num) {
        expand_plist(usr_num);
	}
	if (mode == FIRST_SOLUTION) {
		vector<int> sol_store
		gen_partition_first(usr_num, 0, sol_store);
		cout << partition_list[0][0] << " " << partition_list[0][1] << " " << partition_list[0][2] << endl;
		return;
	}
} 

bool prime_partition::gen_partition_first(int curr_num, int ind1, vector<int> &store) {
    if (curr_num == 0) {
        return false;
	}
	vector<int> pprimes;
	prev_primes(curr_num, pprimes);
	vector<int>::iterator loop_pprimes = pprimes.end();
	--loop_pprimes;
	int next_num;
	store.push_back(*loop_pprimes);
	while (loop_pprimes >= pprimes.begin()) {
        next_num = curr_num - *loop_pprimes;
		if (gen_partition_first(next_num, ind1+1, store)) {
            return true;
		}
		--loop_pprimes;
		store[ind1] = *loop_pprimes;
	}
	return false;
}

void prime_partition::prev_primes(int curr_num, vector<int> &pprimes) {
    vector<int>::iterator loop_plist = plist.begin();
	while (loop_plist != plist.end() && *loop_plist <= curr_num) {
	    pprimes.push_back(*loop_plist);
		++loop_plist;
	}
}

void prime_partition::expand_plist(int curr_num) {
    bool prime = false;
	int num = plist.back() + 1;
	while (!prime || num < curr_num) {
        prime = true;
		for (int i = 2; i*i <= num; i++) {
            if (num % i == 0) {
                prime = false;
				break;
		    }
		}
		if (prime) {
            plist.push_back(num);
		}
		num++;
	}
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
      cerr << "Usage: ./Goldbach -first/all\n";
	  exit(-1);
  }
  if (strcmp(argv[1], "-first") && strcmp(argv[1], "-all")) {
      cerr << "Usage: ./Goldbach -first/all\n";
	  exit(-2);
  }
  program_mode_t mode;

  if (!strcmp(argv[1], "-first")) {
      mode = FIRST_SOLUTION; 
  }
  else {
      mode = ALL_SOLUTIONS;
  }

  prime_partition goldbach(mode);

  int number;
  while (1) {
	cout << "number = ";
    cin >> number;
	if (cin.eof())
	  break;
	
	goldbach(number);
  }

  cout << "\n";
}
