#include ...
using namespace std;

class isprime {
  public:
    isprime() { ... }
    bool operator()(int);

  private:
    ...
};

bool isprime::operator()(int number)
{
    ...
}

int random_number()
{
	return ...
}

int main(int argc, char *argv[])
{
	int N = ...

	srand(N);

	vector< ? > ...
	vector< ? > ...

	generate( ... );
	transform( ... );

	int c = count( ... );
	
	cout << useful info
}
