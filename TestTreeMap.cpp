#include "treemap.h"

#include <iostream>
#include <sstream> 
#include <string>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

int main() {
    
    int retval = 0;
    {
        TreeMap<int,string> tree;
        
        tree.insert(5,"panda");
        
        {
            ostringstream s;
            tree.write(s);
            
            if (s.str() == " 5,panda ") {
                cout << "1) Pass: adding (5,panda) to the tree yields the tree containing (5,panda) and only (5,panda)\n";
            } else {
                cout << "1) Fail: adding (5,panda) to the tree should yield the tree containing (5,panda) and only (5,panda) but it gives " << s.str() << "\n";
                ++retval;
            }
        }
                
        tree.insert(1,"lion");
        tree.insert(2,"dolphin");
        tree.insert(6,"llama");
        
        {
            ostringstream s1;
            tree.write(s1);
            
            if (s1.str() == " 1,lion  2,dolphin  5,panda  6,llama ") {
                cout << "2) Pass: adding more data to the tree correctly yields the tree  \" 1,lion  2,dolphin  5,panda  6,llama \"\n";
            } else {
                cout << "2) Fail: adding more data to the tree containing 5,panda should yield the tree  \" 1,lion  2,dolphin  5,panda  6,llama \" but it gives \"" << s1.str() << "\"\n";
                ++retval;
            }
        }
        
        {
            auto six = tree.find(6);
        
            if (six && six->v == "llama") {
                cout << "3) Pass: looking up 6 found llama\n";
            } else {
                cout << "3) Fail: looking up 6 did not find llama\n";
                ++retval;
            }
        }
        
        {
            auto three = tree.find(3);
            
            if (!three) {
                cout << "4) Pass: looking up 3 did not find anything";
            } else {
                cout << "4) Fail: looked for 3 in the tree (which doesn't contain 3) and got \"" << three->v << "\"\n";
                ++retval;
            }
        }
        

        cout << endl;
        
        
    }         
    
    return retval;
    
}
