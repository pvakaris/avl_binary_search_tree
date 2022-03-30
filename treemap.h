#ifndef TREEMAP_H
#define TREEMAP_H

#include "tree.h"

/**
 * This class represents a Key --> Value pair.
 * @tparam Key Key object.
 * @tparam Value Value object.
 *
 * @author Vakaris Paulavičius (K20062023)
 * @version 1.3
 */
template<typename Key, typename Value>
class KeyValuePair {

public:

    const Key k;
    Value v;

    /**
     * Constructor with Key and Value.
     * @param k Key.
     * @param v Value.
     */
    KeyValuePair(Key k, Value v)
        : k(k), v(std::move(v)) {
    }

    /**
     * Constructor with the Key only.
     * @param k Key.
     */
    explicit KeyValuePair(Key k)
        : k(k) {
    }

    /**
     * Check if Key of this KeyValuePair is smaller than the Key of the provided one.
     * @param other KeyValuePair to compare to.
     * @return true if this Key is smaller than the Key of the provided KeyValuePair.
     */
    bool operator <(const KeyValuePair other) const{
        return k < other.k;
    }

    /**
     * Check if this KeyValuePair is equal to the provided one according to its Key.
     * @param other KeyValuePair to compare to.
     * @return true if Keys are the same, false otherwise.
     */
    bool operator ==(const KeyValuePair other) const {
        return k == other.k;
    }
};

template<typename Key, typename Value>
ostream & operator<< (ostream & o, const KeyValuePair<Key,Value> & kv){
    o << kv.k << "," << kv.v;
    return o;
}

// ====================================================================================================================


/**
 * This class represents a TreeMap that has a BinarySearchTree of KeyValuePair's.
 * @tparam Key Key of the KeyValuePair.
 * @tparam Value Value of the KeyValuePair.
 *
 * @author Vakaris Paulavičius (K20062023)
 * @version 1.2
 */
template<typename Key, typename Value>
class TreeMap {

private:

    BinarySearchTree<KeyValuePair<Key,Value> > tree;

public:

    /**
     * Insert a KeyValuePair into the BinarySearchTree stored inside.
     * @param k Key of the KeyValuePair.
     * @param v Value of the KeyValuePair.
     * @return Pointer to the KeyValuePair<Key,Value> object if the insertion was successful, nullptr if the Key already
     * exists in the BinarySearchTree.
     */
    KeyValuePair<Key,Value> * insert(const Key & k, const Value & v) {
        return &(tree.insert(KeyValuePair<Key,Value>(k,v))->data);
    }

    /**
     * Get the TreeMap representation.
     * @param o ostream object.
     */
    void write(ostream & o) const {
        tree.write(o);
    }

    /**
     * Look for the KeyValuePair in the BinarySearchTree stored inside.
     * @param k Key of the KeyValuePair.
     * @param v Value of the KeyValuePair.
     * @return Pointer to the KeyValuePair<Key,Value> if it was found, nullptr if the Key does not exist in the BST.
     */
    KeyValuePair<Key,Value> * find(Key k) {
        KeyValuePair<Key,Value> pair (k);
        TreeNode<KeyValuePair<Key, Value>> * treeNode = tree.find(pair);
        return &treeNode->data;
    }

};
// do not edit below this line

#endif
