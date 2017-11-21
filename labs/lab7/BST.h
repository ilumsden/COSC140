#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/* BST.h
 * Author: Ian Lumsden
 * Date: November 20, 2017
 * 
 * This file contains all the code for implementing a
 * Binary Search Tree which does NOT allow duplicates.
 * As part of this Binary Search Tree class, a node structure
 * and an iterator subclass are also implemented.
 */

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

/* This iterator pre-increment operator progresses the
 * iterator so that its internal pointer points to the next
 * inorder node in the tree.
 */
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::iterator::operator++() {
    /* If the iterator points to a NULL node, it is at the 
     * end of the tree, and the next inorder node will still
     * be NULL. Therefore, this block will do nothing.
     */
    if (p == NULL) {
        ;
    }
    /* If the node that the iterator points to has a right child and said
     * right child doesn't have a left child, the iterator's internal pointer
     * will be set to point to the current node's right child.
     * If the right child has a left child, this block go as far left in the
     * right child's left subtree as possible. The iterator's internal pointer
     * is then set to point to this leftmost node.
     */
    else if (p->link[1] != NULL) {
        p = p->link[1];
	while (p->link[0] != NULL) {
            p = p->link[0];
	}
    }
    /* If the node that the iterator points to has a NULL parent,
     * this block will do nothing. Note that this block will not
     * be run if the current node has a right subtree.
     */
    else if (p->parent == NULL) {
        ;
    }
    /* This code block deals with progressing up the tree.
     * The block will progress the node pointer up the tree until
     * either the current node is the left child of its parent or
     * the current node's parent is NULL. When the current node is the
     * left child of its parent, the progression will stop at the parent node.
     * Otherwise (when the current node's parent is NULL), the node pointer
     * will be set to NULL.
     */
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
    /* After the node pointer, p, is set by the above code,
     * an iterator to that node is returned.
     */
    return iterator(p);
}

/* The iterator dereference operator returns the key stored
 * in the node that the iterator points to.
 */
template <class TKey>
TKey & bst<TKey>::iterator::operator*() {
    return p->key;
}

/* The iterator == operator compares the memory addresses of
 * the nodes that the current iterator and parameter iterator point to.
 * If the memory addresses are the same, the operator returns true.
 * Otherwise, it returns false.
 */
template <class TKey>
bool bst<TKey>::iterator::operator==(const iterator &it) const {
    return it.p == p;
}

/* The iterator != operator compares the memory addresses of
 * the nodes that the current iterator and parameter iterator point to.
 * If the memory addresses are the same, the operator returns false.
 * Otherwise, it returns true.
 */
template <class TKey>
bool bst<TKey>::iterator::operator!=(const iterator &it) const {
    return it.p != p;
}

/* This function progresses to the leftmost node in the tree
 * and returns an iterator to that node. If the tree has no
 * nodes or if the root node has no left subtree, this function
 * returns an iterator to the root node.
 */
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

/* This function returns a NULL iterator (which represents the node
 * after the last node in the tree).
 */
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

/* This function returns an iterator to the first node with a key
 * equal to the parameter. If no node has a key that is equal, an iterator
 * to the node with the smallest key greater than the parameter is returned.
 */
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &inkey) {
    // p is a node pointer that points to the current node.
    node *p = Troot;
    // If the tree is empty, a NULL iterator is returned.
    if (p == NULL) {
        return iterator();
    }
    /* dir is an integer that specifies the direction that
     * the tree traversal should take. If the parameter is greater
     * than the current node's key, dir will be 1, and the traversal
     * will progress to the right. Otherwise, dir will be 0, and the
     * traversal will progress to the left.
     */
    int dir = (inkey > p->key);
    // next is a node pointer that points to the next node in the traversal.
    node *next = p->link[dir];
    /* curr_gt is a node pointer that points to the node in the traversal
     * path with the smallest key greater than the parameter.
     */
    node *curr_gt = p;
    /* If the root node does not have a child in the correct direction
     * for the traversal and the root node's key value is less than
     * the parameter, a NULL iterator is returned.
     */ 
    if (next == NULL && curr_gt->key < inkey) {
        return iterator();
    }
    /* This while loop traverses the tree until it reaches a
     * NULL node or the first node with a key value equal to
     * the parameter.
     */
    while (p->key != inkey && next != NULL) {
        /* If the current node's key is greater than the
         * parameter and less than the key value of the node
         * that curr_gt points to, curr_gt is updated to point
         * to the current node.
         */
        if (p->key > inkey && p->key < curr_gt->key) {
            curr_gt = p;
        }
        /* The current node pointer and next pointer are updated so that
         * they point to the next pair of nodes in the traversal path.
         */
        p = next;
        dir = (inkey > p->key);
        next = p->link[dir];
        /* If the next pointer points to a NULL node, the check for
         * changing what curr_gt points to (see above) is performed
         * one last time before exiting the loop.
         */
        if (next == NULL) {
            if (p->key > inkey && p->key < curr_gt->key) {
                curr_gt = p;
            }
        }
    }
    /* After exiting the traversal, if the current node's key value
     * equals the parameter, an iterator to the current node is returned.
     */
    if (p->key == inkey) {
        return iterator(p);
    }
    /* After exiting the traversal, if the key value of curr_gt is less than
     * the parameter, a NULL iterator is returned.
     */
    else if (curr_gt->key < inkey) {
        return iterator();
    }
    // Otherwise, an iterator to curr_gt is returned.
    else {
        return iterator(curr_gt);
    }
}

/* This function returns an iterator to the first node with a key
 * greater than the parameter. If no node has a key that is greater, a
 * NULL iterator is returned.
 */
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &inkey) {
    // p is a node pointer that points to the current node.
    node *p = Troot;
    // If the tree is empty, a NULL iterator is returned.
    if (p == NULL) {
        return iterator();
    }
    /* dir is an integer that specifies the direction that
     * the tree traversal should take. If the parameter is greater
     * than the current node's key, dir will be 1, and the traversal
     * will progress to the right. Otherwise, dir will be 0, and the
     * traversal will progress to the left.
     */
    int dir = (inkey > p->key);
    // next is a node pointer that points to the next node in the traversal.
    node *next = p->link[dir];
    /* curr_gt is a node pointer that points to the node in the traversal
     * path with the smallest key greater than the parameter.
     */
    node *curr_gt = p;
    /* If the root node does not have a child in the correct direction
     * for the traversal and the root node's key value is less than
     * the parameter, a NULL iterator is returned.
     */ 
    if (next == NULL && curr_gt->key < inkey) {
        return iterator();
    }
    // This while loop traverses the tree until it reaches a NULL node.
    while (next != NULL) {
        /* If the current node's key is greater than the
         * parameter and less than the key value of the node
         * that curr_gt points to, curr_gt is updated to point
         * to the current node. Also, if the key value of curr_gt
         * is less than the parameter and the key value of the current
         * node is greater than the parameter, curr_gt is updated 
         * to the current node.
         */
        if (p->key > inkey && (p->key < curr_gt->key || curr_gt->key < inkey)) {
            curr_gt = p;
        }
        /* The current node pointer is updated to the next node in the 
         * traversal.
         */
        p = next;
        /* If the current node's key is equal to the parameter, dir is set
         * to 1 to force the traversal to the right. Otherwise, the traversal
         * is dictated by the comparision between the parameter and current
         * node's key.
         */
        if (p->key == inkey) {
            dir = 1;
        }
        else {
            dir = (inkey > p->key);
        }
        // next is updated to the new next node in the traversal.
        next = p->link[dir];
        /* If the next pointer points to a NULL node, the check for
         * changing what curr_gt points to (see above) is performed
         * one last time before exiting the loop.
         */
        if (next == NULL) {
            if (p->key > inkey && (p->key < curr_gt->key || curr_gt->key < inkey)) {
                curr_gt = p;
            }
        }
    }
    /* After completing the traversal, if the key value of curr_gt is
     * less than the parameter, a NULL iterator is returned.
     */
    if (curr_gt->key < inkey) {
        return iterator();
    }
    // Otherwise, an iterator to curr_gt is returned.
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
