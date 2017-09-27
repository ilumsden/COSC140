#include<iostream>

using namespace std;


struct node {
    int data;
    node *next;
    node *prev;
    node(int val=0) {data = val; next = NULL; prev=NULL;}
};

class list {
    private:
        int N;
        node *head;
    public:
        list(int);
        ~list();
        void push_front(const int&);
        void pop_front();
        const int &front();
        node *findnode(int);
        void print();
};

/*list::node::node(int val=0) {
    data = val;
    next = NULL;
}*/

list::list(int num_vals) {
    head = new node;
    N = 0;
    node *p = head;
    for (int i = 0; i < num_vals; i++) {
        push_front(0);
        p = p->next;
        if (i == num_vals-1) {
            p->next = head;
            head->prev = p;
        }
    }
}

list::~list() {
    while (N != 0) {
        node *p = head->next;
        if (N != 1) {
            head->next = p->next;
            head->next->prev = head;
        }
        else {
            head->next = NULL;
            head->prev = NULL;
        }
        delete p;
        N--;
    }
    delete head;
}

void list::push_front(const int &val) {
    node *p = new node(val);
    if (head->next == NULL) {
        head->next = p;
        p->prev = head;
        p->next = head;
        head->prev = p;
    }
    else {
        node *pp = head->next;
        head->next = p;
        p->prev = head;
        p->next = pp;
        pp->prev = p;
    }
    N++;
    return;
}

void list::pop_front() {
    node *p = head->next;
    if (p->next == NULL) {
        head->next = NULL;
        head->prev = NULL;
    }
    else {
        head->next = p->next;
        p->next->prev = head;
    }
    delete p;
    N--;
    return;
}

const int & list::front() {
    node *p = head->next;
    return p->data;
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

node* list::findnode(int ind) {
    node *found;
    if (ind <= N/2) {
        node *p = head->next;
        for (int j = 0; j < ind; j++) {
            p = p->next;
        }
        found = p;
    }
    else {
        node *p = head->prev;
        for (int j = N; j > ind; j--) {
            p = p->prev;
        }
        found = p;
    }
    return found;
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
    cout << "a[0] = " << a.findnode(0)->data << endl;
    cout << "a[1] = " << a.findnode(1)->data << endl;
    cout << "a[2] = " << a.findnode(2)->data << endl;
    cout << "a[3] = " << a.findnode(3)->data << endl;
    cout << "a[4] = " << a.findnode(4)->data << endl;
    return(0);
}
