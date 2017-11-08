#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey>
class bst {
    struct node {
        node(int ID = int());

	    void print();

        TKey key;
		int id;
        node *parent;
        node *link[2];
    };
  
    /*public:
	    class iterator {
	        public:
		        //default constructor (no argument)
		        //overloaded operators (++, *, ==, !=)
	        private:
	            //friend class bst<TKey>;
		        //constructor (with argument)

	            node *p;
	    };

	    //iterator begin() { ... }
	    //iterator end() { ... }*/

    public:
        bst() { Troot=NULL; tid=0;}
	    ~bst() { clear(Troot); }

	    bool empty() { return Troot==NULL; }

	    void insert(TKey &);

	    //iterator lower_bound(const TKey &);
	    //iterator upper_bound(const TKey &);

	    void print_bylevel();

    private:
	    void clear(node *);
	    node *insert(node *, TKey &);
        
		// tid is a node ID used to pass the correct ID to a node that
		// will be inserted.
	    int tid;
        node *Troot;
};

template <class TKey>
bst<TKey>::node::node(int ID) {
    id = ID;
    key = TKey();
	parent = NULL;
    link[0] = NULL;
	link[1] = NULL;
}

template <class TKey>
void bst<TKey>::node::print() {
    cout << setw(3) << key << " "
		 << setw(3) << id << ":";

    //output node and parent ID information
    //change below to output subtree ID information
	
	if (id == 1) {
        cout << " ROOT ";
	}
	else {
        cout << " P=" << setw(3) << parent->id;
	}

    if (link[0]) cout << " L=" << setw(3) << link[0]->id;
    else         cout << "      ";
    if (link[1]) cout << " R=" << setw(3) << link[1]->id;
    else         cout << "      ";

    cout << "\n";
}

//bst<TKey>::iterator functions not defined above go here

template <class TKey>
void bst<TKey>::clear(node *T) {
    if (T) {
        clear(T->link[0]);
        clear(T->link[1]);
        delete T;
        T = NULL;
    }
}

template <class TKey>
void bst<TKey>::insert(TKey &key) { 
    Troot = insert(Troot, key);
}

template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key) {
    if (T == NULL) {
		tid++;
        T = new node(tid);
        T->key = key;
    } 
	else if (T->key == key) {
        ;
    } 
	else {
        int dir = T->key < key;
        T->link[dir] = insert(T->link[dir], key);
		T->link[dir]->parent = T;
    }

    return T;
}

//bst<TKey>::lower_bound function goes here

//bst<TKey>::upper_bound function goes here

template <class TKey>
void bst<TKey>::print_bylevel() {
    if (Troot == NULL)
        return;

    queue<node *> Q;
    node *T;

    Q.push(Troot);
    while (!Q.empty()) {
        T = Q.front();
        Q.pop();

        T->print();
        if (T->link[0]) Q.push(T->link[0]);
        if (T->link[1]) Q.push(T->link[1]);
    }
}
#endif
