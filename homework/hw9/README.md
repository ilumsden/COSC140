# Homework 9: Recursion

## Problem 1

```
int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int factorial_n = factorial(n);
    cout << "factorial = " << factorial_n << "\n";
}
```

Write a recursive implementation of the factorial function needed above. Non-positive values of n should be returned as is. That is, `factorial(5) = 120` while `factorial(-5) = -5`.

## Problem 2

```
void magic(const char *c) {
    if (!(*c)) {
        return;
    }
    magic(c+1);
    cout << *c;
}

int main(int argc, char *argv[]) {
    char text[80];
    while (cin.getline(text, 80)) {
        magic(text);
        cout << "\n";
    }
}
```

Determine what the above code writes to stdout given the following input:

```
nspx mbufn zn fub mxp sn
gmf fupnfs fn pu ffmg
zpc bobobc pz
nbshfmfu tibsbt fft ibspo tufm fhsbn
```
