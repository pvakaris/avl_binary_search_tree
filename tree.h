#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:
/**
 * BinarySearchTree is a class that implements a BinarySearchTree data structure and functionality..
 * @tparam T Data type stored in the current TreeNode.
 *
 * @author Vakaris Paulavičius (K20062023)
 * @version 1.1
 */
template<typename T>
class BinarySearchTree {

private:

    unique_ptr<TreeNode<T>> root;

    // === METHODS ===

    /**
     * Insert data into the BST recursively from the given TreeNode.
     * @param node A TreeNode which to look for a place to insert from.
     * @param data Data element to insert.
     * @return Pointer to the TreeNode containing the specified data or nullptr if the data already exists in the tree.
     */
    TreeNode<T> * insertRecursively(TreeNode<T> * node, const T data) {
        if(data < node->data) {
            TreeNode<T> * pointer;
            if(node->leftChild) {
                pointer = insertRecursively(node->leftChild.get(), data);
            }
            else {
                node->setLeftChild(new TreeNode<T>(data));
                pointer = node->leftChild.get();
            }
            return pointer;
        }
        else if(node->data < data) {
            TreeNode<T> * pointer;
            if(node->rightChild) {
                pointer = insertRecursively(node->rightChild.get(), data);
            }
            else {
                node->setRightChild(new TreeNode<T>(data));
                pointer = node->rightChild.get();
            }
            return pointer;
        }
        else {
            return nullptr; // Already exists
        }
    }

    /**
     * Look for data in the BST recursively from the given TreeNode.
     * @param node A TreeNode which to look for data from.
     * @param data Data element which to look for.
     * @return Pointer to the TreeNode containing the specified data or nullptr if the data is not in the tree.
     */
    TreeNode<T> * findRecursively(TreeNode<T> * node, const T data) const{
        if(node) {
            if(data == node->data) {
                return node;
            }
            else if(data < node->data){
                TreeNode<T> * pointer = nullptr;
                if(node->leftChild) {
                    pointer = findRecursively(node->leftChild.get(), data);
                }
                return pointer;
            }
            else { // if(node->data < data)
                TreeNode<T> * pointer = nullptr;
                if(node->rightChild) {
                    pointer = findRecursively(node->rightChild.get(), data);
                }
                return pointer;
            }
        }
        else {
            return nullptr;
        }
    }

    /**
     * Make copies of the oldNode children and make those copies as newNode children.
     * @param newNode A TreeNode which to update.
     * @param oldNode A TreeNode whose children to copy.
     */
    void copyRecursively(TreeNode<T> * newNode, TreeNode<T> * oldNode) {
        if(oldNode->leftChild) {
            newNode->setLeftChild(new TreeNode<T>(oldNode->leftChild->data), newNode);
            copyRecursively(newNode->leftChild.get(), oldNode->leftChild.get());
        }

        if(oldNode->rightChild) {
            newNode->setRightChild(new TreeNode<T>(oldNode->rightChild->data), newNode);
            copyRecursively(newNode->rightChild.get(), oldNode->rightChild.get());
        }
    }

    // ===================== AVL tree functionality =====================

    /**
     * Check if the BST became unbalanced after the most recent insertion.
     * @param node Inserted TreeNode.
     */
    void checkBalance(TreeNode<T> * node) {
        TreeNode<T> * parentParent = node->parent->parent;
        if(parentParent) {
            int balanceFactor = parentParent->balanceFactor();
            if(balanceFactor == 2 || balanceFactor == -2) {
                balance(node, parentParent);
            }
        }
    }

    /**
     * Balance the unbalanced BST by performing the right rotation.
     * @param node Inserted TreeNode.
     * @param parentParent Parent of the parent of the inserted TreeNode.
     */
    void balance(TreeNode<T> * node, TreeNode<T> * parentParent) {
        if(parentParent->rightChild && parentParent->rightChild->rightChild.get() == node) {
            leftLeftRotation(parentParent);
        }
        else if(parentParent->leftChild && parentParent->leftChild->leftChild.get() == node) {
            rightRightRotation(parentParent);
        }
        else if(parentParent->leftChild && parentParent->leftChild->rightChild.get() == node) {
            leftRightRotation(parentParent);
        }
        else if(parentParent->rightChild && parentParent->rightChild->leftChild.get() == node) {
            rightLeftRotation(parentParent);
        }
    }

    /**
     * Perform left-left rotation on the provided TreeNode.
     * @param node A TreeNode which to perform the left-left rotation on.
     */
    void leftLeftRotation(TreeNode<T> * node) {
        TreeNode<T> * nodesParent = node->parent;
        TreeNode<T> * nodesRightChild = node->rightChild.release();
        TreeNode<T> * leftChildOfNodesRightChild = nodesRightChild->leftChild.release();
        if(nodesParent) { // Means that "node" is not the root of the tree
            TreeNode<T> * nodePointer;
            if(node->data < nodesParent->data) {
                nodePointer = nodesParent->leftChild.release();
                nodesParent->setLeftChild(nodesRightChild);
            }
            else {
                nodePointer = nodesParent->rightChild.release();
                nodesParent->setRightChild(nodesRightChild);
            }
            nodesRightChild->setLeftChild(nodePointer);
            nodePointer->setRightChild(leftChildOfNodesRightChild);
        }
        else {
            TreeNode<T> * rootPointer = root.release();
            root.reset(nodesRightChild);
            nodesRightChild->setLeftChild(rootPointer);
            rootPointer->setRightChild(leftChildOfNodesRightChild);
            nodesRightChild->parent = nullptr;
        }
    }

    /**
     * Perform right-right rotation on the provided TreeNode.
     * @param node A TreeNode which to perform the right-right rotation on.
     */
    void rightRightRotation(TreeNode<T> * node) {
        TreeNode<T> * nodesParent = node->parent;
        TreeNode<T> * nodesLeftChild = node->leftChild.release();
        TreeNode<T> * rightChildOfNodesLeftChild = nodesLeftChild->rightChild.release();
        if(nodesParent) { // Means that "node" is not the root of the tree
            TreeNode<T> * nodePointer;
            if(node->data < nodesParent->data) {
                nodePointer = nodesParent->leftChild.release();
                nodesParent->setLeftChild(nodesLeftChild);
            }
            else {
                nodePointer = nodesParent->rightChild.release();
                nodesParent->setRightChild(nodesLeftChild);
            }
            nodesLeftChild->setRightChild(nodePointer);
            nodePointer->setLeftChild(rightChildOfNodesLeftChild);
        }
        else {
            TreeNode<T> * rootPointer = root.release();
            root.reset(nodesLeftChild);
            nodesLeftChild->setRightChild(rootPointer);
            rootPointer->setLeftChild(rightChildOfNodesLeftChild);
            nodesLeftChild->parent = nullptr;
        }
    }

    /**
     * Perform left-right rotation on the provided TreeNode.
     * @param node A TreeNode which to perform the left-right rotation on.
     */
    void leftRightRotation(TreeNode<T> * node) {
        leftLeftRotation(node->leftChild.get());
        rightRightRotation(node);
    }

    /**
     * Perform right-left rotation on the provided TreeNode.
     * @param node A TreeNode which to perform the right-left rotation on.
     */
    void rightLeftRotation(TreeNode<T> * node) {
        rightRightRotation(node->rightChild.get());
        leftLeftRotation(node);
    }

    // ==================================================================

public:
    /**
     * Default constructor of the BinarySearchTree with no elements inside.
     */
    BinarySearchTree() = default;

    /**
     * Get the tree representation.
     * @param o ostream object.
     */
    void write(ostream& o) const{
       if(root) {
           root->write(o);
       }
    }

    /**
     * Insert element to the BinarySearchTree.
     * @param data Data element which to insert.
     * @return Pointer to the TreeNode with the provided data element, nullptr if the data already exists in the BST.
     */
    TreeNode<T> * insert(const T data) {
        if(root) {
            TreeNode<T> * pointer = insertRecursively(root.get(), data);
            if(pointer) {
                checkBalance(pointer);
            }
            return pointer;
        }
        else {
            root.reset(new TreeNode<T>(data));
            return root.get();
        }
    }

    /**
     * Look for the data element in the BinarySearchTree.
     * @param data Data element which to look for.
     * @return Pointer to the TreeNode containing the provided data, nullptr if the data does not exist in the BST.
     */
    TreeNode<T> * find(const T data) const{
        if(root) {
            return findRecursively(root.get(), data);
        }
        else {
            return nullptr;
        }
    }

    /**
     * Get maximum depth of the BinarySearchTree.
     * @return max depth of the BST.
     */
    int maxDepth() const{
        return root->maxDepth();
    }

    /**
     * Get a TreeNodeIterator pointing to the first element of the tree.
     * @return TreeNodeIterator pointing to the beginning of the tree.
     */
    TreeNodeIterator<T> begin() const{
      TreeNode<T> * firstElement;
      if(root) {
          firstElement = root->findLeftmostChild();
      }
      else {
          firstElement = nullptr;
      }
      return TreeNodeIterator<T>(firstElement);
    }

    /**
     * Get a TreeNodeIterator pointing to the next element of the last element of the tree.
     * @return TreeNodeIterator pointing to the end of the tree.
     */
    TreeNodeIterator<T> end() const{
      TreeNode<T> * lastElement;
      if(root) {
          lastElement = root->findRightmostChild();
          return TreeNodeIterator<T>(lastElement->rightChild.get());
      }
      else {
          return TreeNodeIterator<T>(nullptr);
      }
    }

    /**
     * Equal operator used to make this BST identical to the provided one.
     * @param other BST which to look at.
     * @return An updated BinarySearchTree.
     */
    BinarySearchTree & operator=(const BinarySearchTree & other) {
        root.reset(new TreeNode<T>(other.root->data));
        copyRecursively(root.get(), other.root.get());
        return *this;
    }

    /**
     * Copy constructor.
     * @param other BinarySearchTree to make a copy of.
     */
    BinarySearchTree(const BinarySearchTree & other)
            : root(nullptr) {
        root.reset(new TreeNode<T>(other.root->data));
        copyRecursively(root.get(), other.root.get());
    }

};
// do not edit below this line

#endif
