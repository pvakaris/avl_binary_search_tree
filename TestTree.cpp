#include "treenode.h"
#include "tree.h"

#include <iostream>
#include <sstream> 

using std::cout;
using std::endl;
using std::ostringstream;



class JustAnInt {
    
public:
    
    int x;
    
    bool operator<(const JustAnInt & other) const {
        return (x < other.x);
    }
};


int main() {
    
    int retval = 0;
    {
        BinarySearchTree<int> tree;
        
        tree.insert(5);
        
        {
            ostringstream s;
            tree.write(s);
            
            if (s.str() == " 5 ") {
                cout << "1) Pass: adding 5 to the tree yields the tree containing 5 and only 5\n";
            } else {
                cout << "1) Fail: adding 5 to the tree should yield the tree containing 5 and only 5 but it gives " << s.str() << "\n";
                ++retval;
            }
        }
        
        tree.insert(1);
        tree.insert(2);
        tree.insert(6);
        
        {
            ostringstream s1;
            tree.write(s1);
            
            if (s1.str() == " 1  2  5  6 ") {
                cout << "2) Pass: adding 1, 2 and 6 to the tree containing 5 yields the tree  \" 1  2  5  6 \"\n";
            } else {
                cout << "2) Fail: adding 1, 2 and 6 to the tree containing 5 should yield the tree  \" 1  2  5  6 \" but it gives \"" << s1.str() << "\"\n";
                ++retval;
            }
        }
        
        
        {
            auto six = tree.find(6);
        
            if (six && six->data == 6) {
                cout << "3) Pass: found 6 in the tree \" 1  2  5  6 \"\n";
            } else {
                cout << "3) Fail: 6 is in the tree \" 1  2  5  6 \" but find hasn't found a note containing 6\n";
                ++retval;
            }
        }
        
        {
            auto three = tree.find(3);
            
            if (!three) {
                cout << "4) Pass: didn't find 3 in the tree \" 1  2  5  6 \", which doesn't contain it";
            } else {
                cout << "4) Fail: looked for 3 in the tree \" 1  2  5  6 \", which doesn't contain 3 and got non-null node containing \"" << three->data << "\"\n";
                ++retval;
            }
            
        }
        
        cout << endl;
        
        
    }         

    
    {
        
        // compiler errors here mean you tried to do something other than 'operator<' when comparing data in the tree
        BinarySearchTree<JustAnInt> tree;
        tree.insert(JustAnInt{42});
    }
    
    return retval;
    
}
