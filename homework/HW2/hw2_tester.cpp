#include<iostream>

using namespace std;

class list {
    private:
        struct node {
            int data;
            node *next;
            node(int val=0) {data = val; next = NULL;}
        };
        int N;
        node *head;
    public:
        list(int);
        ~list();
        void push_front(const int&);
        void pop_front();
        const int &front();
        void print();
};

list::list(int num_vals) {
    head = new node;
    N = 0;
    for (int i = 0; i < num_vals; i++) {
        push_front(0);
    }
}

list::~list() {
    while (N != 0) {
        node *p = head->next;
        head->next = p->next;
        delete p;
        N--;
    }
    delete head;
}

void list::push_front(const int &val) {
    node *p = new node(val);
    node *pp = head->next;
    p->next = pp;
    head->next = p;
    N++;
    return;
}

void list::pop_front() {
    node *p = head->next;
    node *pp = p->next;
    head->next = pp;
    N--;
    return;
}

const int & list::front() {
    return head->next->data;
}

void list::print() {
    node *p;
    if (N == 0) {
        cout << "No values to print" << endl;
        return;
    }
    else {
        p = head->next;
    }
    cout << "List vals:";
    for (int i = 0; i < N; i++) {
        cout << " " << p->data << ",";
        p = p->next;
    }
    cout << endl;
    return;
}

int main() {
    int num;
    list a(5);
    a.print();
    for (int i = 0; i < 4; i++) {
        a.pop_front();
        a.print();
        num = a.front();
        cout << "Front = " << num << endl;
    }
    for (int i = 1; i < 5; i ++) {
        a.push_front(i);
        a.print();
        cout << "Front = " << a.front() << endl;
    }
    return(0);
}
