#include<iostream>

using namespace std;

int strlen(char *);

int main(int argc, char *argv[]) {
    cout << "Num args = " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "argv[" << i << "] = "
             << &argv[i] << " " << argv[i]
             << "(strlen=" << strlen(argv[i])
             << ")" << endl;
    }
    return(0);
}

int strlen(char *s) {
    int len = 0;
    while (*s != '\0') {
        len++;
        s++;
    }
    return(len);
}
