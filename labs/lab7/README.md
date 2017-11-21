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
