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

        /* `key` is the data stored in the node.
         * `id` is an int that states when the node was added to the tree.
         * `parent` is a node pointer that points to the parent of this node.
         * `link` is an array of node pointers. The pointers point to this
         * node's children.
         */
        TKey key;
        int id;
        node *parent;
        node *link[2];
    };
  
    public:
        class iterator {
	    public:
                iterator() {p = NULL;};
                iterator operator++();
                TKey &  operator*();
                bool operator==(const iterator &) const;
                bool operator!=(const iterator &) const;
            private:
                friend class bst<TKey>;
                iterator(node *np) {p = np;}
                node *p;
	};
	iterator begin();
	iterator end();

    public:
        bst() { Troot=NULL; tid=0;}
        ~bst() { clear(Troot); }

        bool empty() { return Troot==NULL; }

        void insert(TKey &);

        iterator lower_bound(const TKey &);
        iterator upper_bound(const TKey &);

        void print_bylevel();

    private:
        void clear(node *);
        node *insert(node *, TKey &);
        
        // tid is a node ID used to pass the correct ID to a node that
        // will be inserted.
        int tid;
        // Troot points to the root node of the tree.
        node *Troot;
};

/* This is the constructor for the node subclass.
 * ID has a default value of 0 (int()).
 * When run, it initializes `id` to the passed value (or default).
 * Additionally, it sets the key to the default value of its data type,
 * and it sets all the member pointers to NULL.
 */
template <class TKey>
bst<TKey>::node::node(int ID) {
    id = ID;
    key = TKey();
    parent = NULL;
    link[0] = NULL;
    link[1] = NULL;
}

// This function prints the node's data.
template <class TKey>
void bst<TKey>::node::print() {
    /* This cout statement prints out the node's
     * key and id.
     */
    cout << setw(3) << key << " "
         << setw(3) << id << ":";
	
    /* This if-else statement prints out "ROOT" if
     * this node is the root node. Otherwise, it prints
     * out the id of this node's parent node.
     */
    if (id == 1) {
        cout << " ROOT ";
    }
    else {
        cout << " P=" << setw(3) << parent->id;
    }

    /* This block prints out the ids of the left
     * and right children of this node. If the node
     * doesn't have a child in the desired direction,
     * "nothing" is printed out.
     */
    if (link[0]) cout << " L=" << setw(3) << link[0]->id;
    else         cout << "      ";
    if (link[1]) cout << " R=" << setw(3) << link[1]->id;
    else         cout << "      ";

    cout << "\n";
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::iterator::operator++() {
    if (p == NULL) {
        ;
    }
    else if (p->link[1] != NULL) {
        p = p->link[1];
	while (p->link[0] != NULL) {
            p = p->link[0];
	}
    }
    else if (p->parent == NULL) {
        ;
    }
    else {
        int exit = 0;
        while (p->parent != NULL) {
            if (p->parent->link[0] == p) {
                p = p->parent;
                exit = 1;
                break;
	    }
            p = p->parent;
        }
        if (!exit) {
            p = NULL;
	}
    }
    return iterator(p);
}

template <class TKey>
TKey & bst<TKey>::iterator::operator*() {
    return p->key;
}

template <class TKey>
bool bst<TKey>::iterator::operator==(const iterator &it) const {
    return it.p == p;
}

template <class TKey>
bool bst<TKey>::iterator::operator!=(const iterator &it) const {
    return it.p != p;
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::begin() {
    if (Troot == NULL || Troot->link[0] == NULL) {
        return iterator(Troot);
    }
    node *p = Troot;
    while (p->link[0] != NULL) {
        p = p->link[0];
    }
    return iterator(p);
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::end() {
    return iterator();
}

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

/* This function inserts a new node (with key = key parameter)
 * into the tree. The only comments inside this function will
 * be for the changes I made.
 */
template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key) {
    if (T == NULL) {
        /* This part of the function has been edited to update
         * `tid` and use it to initialize a new node with the correct
         * id value. The desired key value is then set as the node's key.
         */
        tid++;
        T = new node(tid);
        T->key = key;
    } 
    else if (T->key == key) {
        ;
    } 
    else {
        /* This part of the function will determine the direction
         * that the traversal will need to take. Then, it recursively
         * calls the insert function and uses its output to set the
         * child node in direction `dir`. If the immediate child of `T`
         * is not the inserted node, the recursion just relinks `T` and
         * its previous child in direction `dir`. Finally, this block 
         * links (or relinks) the child's parent and `T`.
         */ 
        int dir = T->key < key;
        T->link[dir] = insert(T->link[dir], key);
        T->link[dir]->parent = T;
    }

    return T;
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &inkey) {
    node *p = Troot;
    if (p == NULL) {
        return iterator();
    }
    int dir = (inkey > p->key);
    node *next = p->link[dir];
    node *curr_gt = p;
    if (next == NULL && curr_gt->key < inkey) {
        return iterator();
    }
    while (p->key != inkey && next != NULL) {
        if (p->key > inkey && p->key < curr_gt->key) {
            curr_gt = p;
        }
        p = next;
        dir = (inkey > p->key);
        next = p->link[dir];
        if (next == NULL) {
            if (p->key > inkey && p->key < curr_gt->key) {
                curr_gt = p;
            }
        }
    }
    if (p->key == inkey) {
        return iterator(p);
    }
    else if (curr_gt->key < inkey) {
        return iterator();
    }
    else {
        return iterator(curr_gt);
    }
}

template <class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &inkey) {
    node *p = Troot;
    if (p == NULL) {
        return iterator();
    }
    int dir = (inkey > p->key);
    node *next = p->link[dir];
    node *curr_gt = p;
    if (next == NULL && curr_gt->key < inkey) {
        return iterator();
    }
    while (next != NULL) {
        if (p->key > inkey && (p->key < curr_gt->key || curr_gt->key < inkey)) {
            curr_gt = p;
        }
        p = next;
        if (p->key == inkey) {
            dir = 1;
        }
        else {
            dir = (inkey > p->key);
        }
        next = p->link[dir];
        if (next == NULL) {
            if (p->key > inkey && (p->key < curr_gt->key || curr_gt->key < inkey)) {
                curr_gt = p;
            }
        }
    }
    if (curr_gt->key < inkey) {
        return iterator();
    }
    else {
        return iterator(curr_gt);
    }
}

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
