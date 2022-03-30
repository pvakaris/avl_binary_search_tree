#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:
/**
 * TreeNode represents a binary TreeNode.
 * @tparam T Data type stored in the TreeNode.
 *
 * @author Vakaris Paulavičius (K20062023)
 * @version 1.2
 */
template<typename T>
class TreeNode {

public:

    T data;
    unique_ptr<TreeNode> leftChild;
    unique_ptr<TreeNode> rightChild;
    TreeNode * parent;

    /**
     * Constructor of the TreeNode object when its paren TreeNode is known.
     * @param data Data to be stored in the TreeNode.
     * @param parentNode Parent node of the TreeNode.
     */
    TreeNode(T data, TreeNode * parentNode)
            : data(std::move(data)), parent(parentNode), leftChild(nullptr), rightChild(nullptr) {
    }

    /**
     * Constructor of the TreeNode.
     * @param data Data to be stored in the TreeNode.
     */
    explicit TreeNode(T data)
            : data(std::move(data)), parent(nullptr), leftChild(nullptr), rightChild(nullptr)  {
    }

    /**
     * Set the leftChild to the new one and reset left child's parent.
     * @param child Child to reset the leftChild to.
     */
    void setLeftChild(TreeNode<T> * child) {
        leftChild.reset(child);
        if(child) {
            child->parent = this;
        }
    }

    /**
     * Set the rightChild to the new one and reset right child's parent.
     * @param child Child to reset the rightChild to.
     */
    void setRightChild(TreeNode<T> * child) {
        rightChild.reset(child);
        if(child) {
            child->parent = this;
        }
    }

    /**
     * Get the representation of node's children and node itself..
     * @param o ostream object.
     */
    void write(ostream& o) const{
        if(leftChild) {
            (leftChild)->write(o);
        }
        o << " " << data << " ";
        if(rightChild) {
            (rightChild)->write(o);
        }
    }

    /**
     * Get max depth from this TreeNode.
     * @return max depth.
     */
    int maxDepth() {
        if(this == nullptr) {
            return 0;
        }
        int leftSubtreeHeight = 0;
        if(leftChild) {
            leftSubtreeHeight = leftChild->maxDepth();
        }
        int rightSubtreeHeight = 0;
        if(rightChild) {
            rightSubtreeHeight = rightChild->maxDepth();
        }
        return leftSubtreeHeight > rightSubtreeHeight? (leftSubtreeHeight + 1) : (rightSubtreeHeight + 1);
    }

    /**
     * Find the leftmost descendant of this TreeNode.
     * @return leftmost child.
     */
    TreeNode<T> * findLeftmostChild() {
        TreeNode<T> * toReturn = this;
        while(toReturn->leftChild) {
            TreeNode<T> * temp = toReturn;
            toReturn = temp->leftChild.get();
        }
        return toReturn;
    }

    /**
     * Find the rightmost descendant of this TreeNode.
     * @return rightmost child.
     */
    TreeNode<T> * findRightmostChild() {
        TreeNode<T> * toReturn = this;
        while(toReturn->rightChild) {
            TreeNode<T> * temp = toReturn;
            toReturn = temp->rightChild.get();
        }
        return toReturn;
    }

    /**
     * Find the next TreeNode of this TreeNode when rightChild is nullptr.
     * Used in the TreeNodeIterator.
     * @return Find the TreeNode that goes after this.
     */
    TreeNode<T> * findNextTreeNodeWhenRightChildIsNull() {
        TreeNode<T> * toReturn = this;
        while(toReturn->parent) {
            if(toReturn->parent->leftChild.get() == toReturn) {
                return toReturn->parent;
            }
            else {
                toReturn = toReturn->parent;
            }
        }
        return nullptr;
    }

    /**
     * Get the balance factor of the TreeNode.
     * @return balance factor.
     */
    int balanceFactor() {
        int leftSubtreeHeight = leftChild->maxDepth();
        int rightSubtreeHeight = rightChild->maxDepth();
        return leftSubtreeHeight - rightSubtreeHeight;
    }

    /**
     * Default deconstructor.
     */
    ~ TreeNode() = default;


};

// ====================================================================================================================

/**
 * TreeNodeIterator used to iterate over TreeNode objects.
 * @tparam T Data type stored in the current TreeNode.
 *
 * @author Vakaris Paulavičius (K20062023)
 * @version 1.1
 */
template<typename T>
class TreeNodeIterator {

private:

    TreeNode<T> * current;

public:

    /**
     * TreeNodeIterator constructor.
     * @param currentIn pointer to the initial TreeNode<T> of the iterator.
     */
    explicit TreeNodeIterator(TreeNode<T>* currentIn)
            : current(currentIn) {
    }

    /**
     * Return data stored in the current object of the iterator.
     * @return T data of the current object.
     */
    T & operator*() {
        return current->data;
    }


    /**
     * Increment the TreeNodeIterator so that it points to the next element in the BinarySearchTree.
     */
    void operator++() {
        TreeNode<T> * temp = current;
        if(temp->rightChild) {
            if((temp->rightChild)->leftChild) {
                current = temp->findLeftmostChild();
            }
            else {
                current = temp->rightChild.get();
            }
        }
        else {
            current = temp->findNextTreeNodeWhenRightChildIsNull();
        }
    }

    /**
     * Increment the TreeNodeIterator so that it points to the next element in the BinarySearchTree.
     * @return TreeNodeIterator object.
     */
    TreeNodeIterator<T> operator++(int)
    {
        TreeNodeIterator<T> itr = *this;
        TreeNode<T> * temp = current;
        if(temp->rightChild) {
            if((temp->rightChild)->leftChild) {
                current = temp->findLeftmostChild();
            }
            else {
                current = temp->rightChild.get();
            }
        }
        else {
            current = temp->findNextTreeNodeWhenRightChildIsNull();
        }
        return itr;
    }

    /**
     * Check whether this and the provided NodeIterator are the same.
     * They are the same if they point to the same Node.
     * @param other Another NodeIterator to compare to.
     * @return true if they are the same, false otherwise.
     */
    bool operator ==(const TreeNodeIterator other) const{
        return current == other.current;
    }

    /**
     * Check whether this and the provided NodeIterator are different.
     * They are different if they point to different Nodes.
     * @param other Another NodeIterator to compare to.
     * @return true if they are different, false otherwise.
     */
    bool operator !=(const TreeNodeIterator other) const{
        return current != other.current;
    }

    /**
     * Get a pointer to the Node that this Iterator is pointing to.
     * @return current Node.
     */
    TreeNode<T> * getNode() {
        return current;
    }

};
// do not edit below this line

#endif
