# Lab 7:

## Instructions:

### Part 1:
First, create the `BST.h` file needed to compile and run the `BST1` program which is based on `bst1_usage.cpp`. Here is how you do it.

Copy `bst.h` to `BST.h` (_I did this by just renaming_ `bst.h`_ to_ `BST.h` _using the `mv` command in Terminal_.). Strip out comments as well as any code not needed for `BST1` like the iterator subcalss and all undefined bst member functions (_This was just commented out._). Add a node ID (`int`) and a parent pointer (`node *`) to the `bst::node` subclass. Define and implement the `bst::node()` constructor. Have the constructor take a node ID argument which is set to 0 if absent, and use this argument to initialize the node ID. Set the parent pointer to `NULL`.

The node ID is a unique integer assigned to nodes as they are created (_It essentially states the order in which the nodes were added._). Add a node ID to the bst class which is initialized in the `bst` constructor and updated everytime a new node is added to the binary search tree. Update `bst::insert` to do the latter and to pass teh updated value along to the `bst::node` constructor.

With respect to the parent link, be aware that `bst::insert()` is a recursive function which does __not__ have access to the parent when processing a node. You must therefore set the parent link as you ascend out of the recursion (when you reach the parent, you have access to the root of the subtree just processed).

Update `bst::node::print()` to output the node key, its ID, the parent ID, and the left and right subtree IDs (if they exist).

### Part 2:
Make simple drawings that illustrate how the following three functions described below are meant to work, namely the `bst::iterator::operator++()`, `bst::lower_bound(key)`, and `bst::upper_bound(key)` functions. The behavior of these functions is as follows:
* `bst::iterator::operator++()`: This function implements a single step for an inorder traversal of the tree.
* `bst::lower_bound(key)`: This function determines the lower bound for the search range [`lower_bound`, `upper_bound`). It is defined by `key <= lower_bound(key)`. In words, `lower_bound(key)` will attempt to find the first node whose key value is equal to the `key` parameter. If it cannot find a node with an equal key, it will find the node with the smallest key that is still greater than the `key` parameter. After finding the desired node, it will return an iterator to that node.
* `bst::upper_bound(key)`: This function determines the upper bound for the search range [`lower_bound`, `upper_bound`). It is defined by `key < upper_bound(key)`. In words, `upper_bound(key)` will find the node with the smallest key that is still greater than the `key` parameter, and it will return an iterator to that node. If no node has a key greater than the `key` parameter, a `NULL` iterator will be returned.

Add a few sentences to explain your drawings but be succinct. These drawings are meant for you to __think about functionality before you think about code__.

### Part 3:
Modify `BST.h` as necessary to compile and run the `BST2` program which is based on `bst2_usage.cpp`. A quick look at the latter should convince you that this is a matter of adding an iterator subclass to the `bst` class. Here is how you do it.

Add public member functions `bst::begin()` and `bst::end()` which respectively return an iterator that points to the node which holds the smallest key and an iterator that contains a `NULL` pointer which indicates the binary search tree has been exhausted (analogous to the first node and the end of a single-linked list). Recall that the smallest key is found in the leftmost node. You find it by iteratively searching through the sequence of left children starting at the root of the tree.

The `bst.h` (_the provided file that was turned into _`BST.h`) file lists a number of iterator operators that must be included, namely: 
* `++` __pre__-increment for an inorder move to the next node
* `*` for dereferencing and thus accessing the node key
* `==` and `!=` for comparing iterators.

Base you code for these operators on the `list::iterator` code covered in class.

The `++` __pre__-increment operator is by far the most complicated of all the code you will write in this lab assignment. Before you even think about programming it, make sure you know how to carry out an inorder traversal with focus on how to advance from one node to the next. Be aware that you will __NOT__ be using recursion. Each call to `bst::iterator::operator++()` must explicitly update the underlying node pointer to the next node.

When the `bst::iterator` subclass has been implemented, the `print()` function in `bst2_usage.cpp` will output the content of the binary search tree in a lexicographically sorted order.

### Part 4:
Modify `BST.h` as necessary to compile and run the `BST3` program which is based on `bst3_usage.cpp`. A quick look at the latter should convince you that this is a matter of adding two public member functions to the `bst` class, namely `bst::lower_bound()` and `bst::upper_bound()` which both take a key as input and return an iterator corresponding to a node in the binary search tree (or an iterator containing a `NULL` pointer). Here is how these functions are supposed to work.

The `bst::lower_bound(key)` function must return an iterator to the first node in the binary search tree whose key is not less than the given key. If the key exists in the tree, the returned iterator points to that node. If the key does not exist, the returned iterator points to the first node whose key value is greater (_In other words, the iterator points to the node with the closest key value to the parameter without the key value being less than the parameter._). Your search must be based on explicitly traversing the appropriate path from the root to the target node. That is, do not use an iterator-based inorder traversal.

The `bst::upper_bound(key)` function 
