# AVL Binary Search Tree data structure

***

### Classes and their explanation

* TreeNode represents a node in a tree (a leaf)
* Tree represents an AVL BinarySearchTree that uses TreeNodes 
* TreeMap is an AVL BinarySearchTree where each node is a <Key, Value> pair

### Tree supported methods:

* `write` Takes an ostream reference, and calls write on the root of the tree.
* `insert` Takes an item of data, and inserts it into the tree.
* `find` Takes an item of data and traverses the Binary Search Tree to see if the data is in the tree.
If it is, it returns a TreeNode* pointing to the node containing the data.
* `maxDepth` Returns the max depth of the tree.

Tree also has a copy constructor, iterators, overridden (assignment, operator*, operator==, operator!=, operator++) operators.

Because the tree is an AVL tree, everytime a new node is inserted the tree is rebalanced.

----

## How to compile and run

Open the terminal and cd to the directory containing cloned files:

```
cd PATH_TO_THE_CLONED_DIRECTORY
```

Compile all test files using CMake:

```
make all
```

Compile all test files without CMake:

```
g++ -std=c++11 -o TestTreeNode TestTreeNode.cpp

g++ -std=c++11 -o TestTree TestTree.cpp

g++ -std=c++11 -o TestTreeMap TestTreeMap.cpp

g++ -std=c++11 -o TestTreeD TestTreeD.cpp
```

Test the code by running all the tests:

```
./TestTreeNode

./TestTree

./TestTreeMap

./TestTreeD
```
***

Vakaris Paulavičius

Version 1.1
