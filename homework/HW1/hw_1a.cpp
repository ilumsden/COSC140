#include<iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Num args = " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "argv[" << i << "] = " << &argv[i] << " " << argv[i] << endl;
    }
    return(0);
}
