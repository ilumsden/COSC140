#include<iostream>

using namespace std;

struct node {
  node(int n_data=0) { data=n_data; next=prev=this; }
  int data;
  node *next;
  node *prev;
};

class list {
  public:
    list(int = 0);
    ~list();
    bool empty() const { return N == 0; }
    int size()   const { return N; }
    void clear();
    void insert(int, const int &);
    void erase(int);
    void push_back(const int &);
    void pop_back();
    const int & back();
    int & operator[](int);
  private:
    int N;
    node *head;
    node *findnode(int);
};

list::list(int n_N) {
  head = new node;
  N = 0;
  for (int i=0; i<n_N; i++)
    insert(0, 0);
}

list::~list() { clear(); delete head; }

void list::insert(int i, const int &din) {
  node *p = new node(din);
  node *pp = findnode(i-1);
  p->next = pp->next;
  p->prev = pp;
  p->next->prev = p;
  p->prev->next = p;
  N++;
}

void list::erase(int i) {
  node *p = findnode(i);
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  N--;
}

void list::clear() { while (!empty()) erase(0); }

void list::push_back(const int &din) { insert(N, din); }

void list::pop_back() { erase(N-1); }

const int & list::back() {
  node *p = findnode(N-1);
  return p->data;
}

int & list::operator[](int i) {
  node *p = findnode(i);
  return p->data;
}

node *list::findnode(int i) {
    node *found;
    if (i <= N/2) {
        node *p = head->next;
        for (int j = 0; j < i; j++) {
            p = p->next;
        }
        found = p;
    }
    else {
        node *p = head->prev;
        for (int j = N; j > i; j--) {
            p = p->prev;
        }
        found = p;
    }
    return found;
}

int main() {
   list a();
   for (int i = 0; i < 5; i++) {
       a.insert(0, i);
       cout << "a[0] = " << a[0] << endl;
   }
   return 0; 
}
