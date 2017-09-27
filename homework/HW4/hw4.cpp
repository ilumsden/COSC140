// Part 2 of this homework is at the bottom of this file.

#include<iostream>

using namespace std;

class stack {
    private:
        int *arr;
        int N;
    public:
        stack() {arr = new int[10]; N = 0;}
        ~stack();
        bool empty() {return(N == 0);}
        int size() {return N;}
        void push(int);
        void pop();
        int top();
};

stack::~stack() {
    delete [] arr;
}

void stack::push(int i) {
    /*if (N == 10) {
        throw runtime_error("Stack is full.");
    }*/ 
    int *old_arr = new int[10];
    for (int j = 0; j < N; j++) {
        old_arr[j] = arr[j];
    }
    arr[0] = i;
    for (int k = 0; k < N; k++) {
        arr[k+1] = old_arr[k];
    }
    delete [] old_arr;
    N++;
    return;
}

void stack::pop() {
    /*if (empty()) {
        throw runtime_error("Stack is empty.");
    }*/
    int *old_arr = new int[10];
    for (int i = 0; i < N; i++) {
        old_arr[i] = arr[i];
    }
    for (int k = 0; k < N-1; k++) {
        arr[k] = old_arr[k+1];
    }
    delete [] old_arr;
    N--;
    return;
}

int stack::top() {
    /*if (empty()) {
        throw runtime_error("Stack is empty.");
    }*/
    return(arr[0]);
}

int main() {
    stack s;
    for (int i = 0; i < 10; i++) {
        s.push(i);
        cout << "Stack top = " << s.top() << endl;
    }
    for (int j = 0; j < 9; j++) {
        s.pop();
        cout << "Stack top = " << s.top() << endl;
    }
    return(0);
}

/* Problem 2:
 * 
 * For the error checking, the push() function would check to
 * insure that N < 10, and the pop() and top() functions would
 * insure that N > 0 (N is the number of elements in the stack).
 * The condition for the pop() and top() functions could be represented
 * by the empty() function returning true to trigger the error.
 * Examples of this error checking can be found in the commented-out
 * code at the beginning of each of these functions.
 */
