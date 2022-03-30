#include "treenode.h"

#include <iostream>
#include <sstream> 

using std::cout;
using std::endl;
using std::ostringstream;

int main() {
    
    int retval = 0;
    {
        unique_ptr<TreeNode<int>> root(new TreeNode<int>(3));
        
        if (root->data == 3) {
            cout << "1) Pass: a node initialised with '3' contains 3 as its data\n";
        } else {
            cout << "1) Fail: a node initialised with '3' should contain 3 as its data but contains " << root->data << "\n";
            ++retval;
        }
        
        if (!root->parent) {
            cout << "2) Pass: a newly initialised node has a null parent\n";
        } else {
            cout << "2) Fail:  a newly initialised node should have a null parent but parent is " << root->parent << "\n";
            ++retval;
        }
        
        auto leftChild = new TreeNode<int>(2);
        root->setLeftChild(leftChild);
        
        if (root->leftChild.get() == leftChild) {
            cout << "3) Pass: the root correctly points to a left child added to it\n";
        } else {
            cout << "3) Fail: added left child, pointer " << leftChild << ", but root's left child pointer is " << root->leftChild.get() << "\n";
            ++retval;
        }
        if (leftChild->parent == root.get()) {
            cout << "4) Pass: the left child of root correctly points root as its parent\n";
        } else {
            cout << "4) Fail: the left child of has parent " << leftChild->parent << " its parent should be root (" << root.get() << ")\n";
            ++retval;
        }

        auto rightChild =new TreeNode<int>(4);
        root->setRightChild(rightChild);
        
        if (root->rightChild.get() == rightChild) {
            cout << "5) Pass: the root correctly points to a right child added to it\n";
        } else {
            cout << "5) Fail: added right child, pointer " << rightChild << ", but root's right child pointer is " << root->rightChild.get() << "\n";
            ++retval;
        }
        if (rightChild->parent == root.get()) {
            cout << "6) Pass: the right child of root correctly points root as its parent\n";
        } else {
            cout << "6) Fail: the right child of has parent " << rightChild->parent << " its parent should be root (" << root.get() << ")\n";
            ++retval;
        }
        
        root->leftChild->setLeftChild(new TreeNode<int>(1));
        
        ostringstream s;
        root->write(s);
        
        if(s.str() == " 1  2  3  4 "){
            cout << "7) Pass: the tree prints correctly\n";
        } else {
            cout << "7) Fail: Tree is now" << endl;
            cout << "            3" << endl;
            cout << "        2       4" << endl;
            cout << "     1" << endl;
            cout << "Should print as \" 1  2  3  4 \", but printed as \"" <<  s.str() << "\"\n";
            ++retval;
         
        }
        
        cout << "\n";
    }         
    
    return retval;
    
}
