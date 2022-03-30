#include "treenode.h"
#include "tree.h"

#include <algorithm>
#include <iostream>
#include <sstream> 
#include <vector>

using std::cout;
using std::endl;
using std::ostringstream;
using std::vector;

int main() {
    
    int retval = 0;
    {
        BinarySearchTree<int> tree;
        
        if (tree.begin() == tree.end()) {
            cout << "1) Pass: the begin() and end() of an empty tree are the same\n";
        } else {
            ++retval;
            cout << "1) Fail: the begin() and end() of an empty tree are not the same\n";
        }
    }
    {
        BinarySearchTree<int> tree;
        
        vector<int> putIn{5,1,2,6};
        
        for (const int & e : putIn) {
            tree.insert(e);        
        }
             
        std::sort(putIn.begin(), putIn.end());

        vector<int> was;
        
        for (auto & e : tree) {
            was.push_back(e);            
        }
        
        
        if (was == putIn) {
            cout << "2) Pass: added 5,1,2,6 to a tree, looped over it, and got 1,2,5,6\n";            
        } else {
            ++retval;
            cout << "2) Fail: added 5,1,2,6 to a tree, looped over it, and got";
            
            for (int & e : was) {
                cout << " " << e;
            }
            
            cout << endl;
        }
        
        
        
    }         
    
    {
        BinarySearchTree<int> tree;
        vector<int> putIn{1,2,3};
        
        for (const int & e : putIn) {
            tree.insert(e);
        }
        if (tree.maxDepth() == 2) {
            cout << "3) Pass: After inserting 1,2,3, max tree depth is 2: is balanced\n";
        } else {
            ++retval;
            cout << "3) Fail: After inserting 1,2,3, max tree depth is " << tree.maxDepth() << ": is unbalanced, should be 2\n";
        }
    }
    
    
    {
        BinarySearchTree<int> tree;
        vector<int> putIn{1,2,3,4,5};
        
        for (const int & e : putIn) {
            tree.insert(e);
        }
        
        if (tree.maxDepth() == 3) {
            cout << "4) Pass: After inserting 1,2,3,4,5, max tree depth is 3: is balanced\n";
        } else {
            ++retval;
            cout << "4) Fail: After inserting 1,2,3,4,5, max tree depth is " << tree.maxDepth() << ": is unbalanced, should be 3\n";
        }
    }
    
    
    {
        BinarySearchTree<int> tree;
        vector<int> putIn{5,4,3,2,1};
        
        for (const int & e : putIn) {
            tree.insert(e);
        }
        
        if (tree.maxDepth() == 3) {
            cout << "5) Pass: After inserting 5,4,3,2,1, max tree depth is 3: is balanced\n";
        } else {
            ++retval;
            cout << "5) Fail: After inserting 5,4,3,2,1, max tree depth is " << tree.maxDepth() << ": is unbalanced, should be 3\n";
        }
    }
    
    {
        BinarySearchTree<int> tree;
        vector<int> putIn{1,3,2};
        
        for (const int & e : putIn) {
            tree.insert(e);
        }
        
        if (tree.maxDepth() == 2) {
            cout << "6) Pass: After inserting 1,3,2, max tree depth is 2: is balanced\n";
        } else {
            ++retval;
            cout << "6) Fail: After inserting 1,3,2, max tree depth is " << tree.maxDepth() << ": is unbalanced, should be 2\n";
        }
    }
    
    {
        BinarySearchTree<int> tree;
        vector<int> putIn{3,1,2};
        
        for (const int & e : putIn) {
            tree.insert(e);
        }
        
        if (tree.maxDepth() == 2) {
            cout << "7) Pass: After inserting 3,1,2, max tree depth is 2: is balanced\n";
        } else {
            ++retval;
            cout << "7) Fail: After inserting 3,1,2, max tree depth is " << tree.maxDepth() << ": is unbalanced, should be 2\n";
        }
    }
    
    return retval;
    
}
