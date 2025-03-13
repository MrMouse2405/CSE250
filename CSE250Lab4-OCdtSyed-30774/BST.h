/****************************************************************************\
* BST.h
 *
 *  Created on: 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *  This file defines the Binary Search Tree (BST) data structure.
 *  It includes a BST node structure and a BST class that supports
 *  insertion, deletion, searching, traversal, and height calculation.
 *
\***************************************************************************/

#pragma once
#include <string>

/** Binary Search Tree node */
struct BSTNode {
    /** Pointer to the parent node. */
    BSTNode *parent;
    /** Pointer to the left child node. */
    BSTNode *left;
    /** Reference to the right child node. */
    BSTNode *right;
    /** Key used to search an element. */
    int key;
    /** Data associated to the element. */
    std::string data;
};

/** Binary Search Tree
 * In a Binary search tree:
 * 		Every node y in the left subtree of x  must have y.key < x.key
 *  	Every node y in the right subtree of x  must have y.key > x.key
 *  	The root node has root.parent = null
 *  	Here no keys can be duplicated
 */
class BST final {
public:
    /** Construct an empty binary search tree. */
    BST();

    /** Destroy and free up the memory allocated by the binary search tree. */
    ~BST();

    /** Prints all the data from the tree in key order (using _min and _successor). */
    void printTree() const;

    /** Finds a node with (key) from the tree and returns the associated (data) or "" if not found. */
    [[nodiscard]] std::string search(int key) const;

    /** Inserts a new node in the tree with given (key, data). */
    void insert(int key, const std::string &data);

    /** Deletes the node with (key) from the tree and returns the associated (data) or "" if not found. */
    std::string remove(int key);

    /** Computes and returns the height of the tree. */
    [[nodiscard]] int height() const;

    /** Prints the keys (comma separated) of the tree using an preorder traversal. */
    void preOrder() const;

    /** Prints the keys (comma separated) of the tree using an inorder traversal. */
    void inOrder() const;

    /** Prints the keys (comma separated) of the tree using an postorder traversal. */
    void postOrder() const;

private:
    /** Pointer to the root node of the tree, or nullptr if empty */
    BSTNode *m_root;

    /** Returns the node with the smallest key in a given subtree. */
    static BSTNode *_min(BSTNode *x);

    /** Returns the in-order successor of a given node. */
    static BSTNode *_successor(const BSTNode *x);

    /** Computes and returns the height of a given node. */
    static int _height(const BSTNode *x);

    /** Finds and returns the node with the specified key, or nullptr if not found. */
    [[nodiscard]] BSTNode *_findNode(int key) const;

    /** Determines the replacement node when deleting a node. */
    static BSTNode *_getReplacement(const BSTNode *node);

    /** Replaces a node with another node in the tree. */
    void _replaceNode(const BSTNode *node, BSTNode *replacement);

    /** Recursive helper function for preorder traversal. */
    static void _preOrder(const BSTNode *node);

    /** Recursive helper function for inorder traversal. */
    static void _inOrder(const BSTNode *node);

    /** Recursive helper function for postorder traversal. */
    static void _postOrder(const BSTNode *node);

    /** Recursively deletes all nodes in the tree. */
    static void _deleteTree(const BSTNode *node);
};
