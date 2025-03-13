/****************************************************************************\
 * BST.cpp
 *
 *  Created on: 2025
 *      Author: OCdt Syed
 *
 *  Implementation details: Implements a Binary Search Tree (BST)
 *  supporting insertion, deletion, search, traversal, and height calculation.
 *
\***************************************************************************/

#include "BST.h"
#include <iostream>
using namespace std;

/*

    Private Helpers

 */

/** Returns the node with the smallest key in a given subtree. */
BSTNode *BST::_min(BSTNode *x) {
    while (x && x->left) {
        x = x->left;
    }
    return x;
}


/** Returns the in-order successor of a given node. */
BSTNode *BST::_successor(const BSTNode *x) {
    if (x->right) {
        return _min(x->right);
    }
    BSTNode *y = x->parent;
    while (y && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

/** Returns the maximum of two integers. */
static int max(const int a, const int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/** Computes and returns the height of the node x. */
int BST::_height(const BSTNode *x) {
    if (x == nullptr) {
        return 0;
    }
    return 1 + max(_height(x->left), _height(x->right));
}

/** Finds and returns the node with the specified key, or nullptr if not found. */
BSTNode *BST::_findNode(const int key) const {
    BSTNode *node = m_root;
    while (node && node->key != key) {
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}


/** Determines the replacement node when deleting a node. */
BSTNode *BST::_getReplacement(const BSTNode *node) {
    if (node->left != nullptr) {
        return node->left;
    }
    return node->right;
}

/** Replaces a node with another node in the tree. */
void BST::_replaceNode(const BSTNode *node, BSTNode *replacement) {
    if (node == m_root) {
        m_root = replacement;
    } else {
        if (node == node->parent->left) {
            node->parent->left = replacement;
        } else {
            node->parent->right = replacement;
        }
    }
    if (replacement) {
        replacement->parent = node->parent;
    }
}


/** Recursively deletes all nodes in the tree. */
void BST::_deleteTree(const BSTNode *node) {
    if (node == nullptr) {
        return;
    }
    _deleteTree(node->left);
    _deleteTree(node->right);
    delete node;
}


/*

    Traversals

 */

/** Recursive helper function for preorder traversal. */
void BST::_preOrder(const BSTNode *node) {
    if (!node) return;
    cout << node->key << ", ";
    _preOrder(node->left);
    _preOrder(node->right);
}

/** Recursive helper function for inorder traversal. */
void BST::_inOrder(const BSTNode *node) {
    if (!node) return;
    _inOrder(node->left);
    cout << node->key << ", ";
    _inOrder(node->right);
}

/** Recursive helper function for postorder traversal. */
void BST::_postOrder(const BSTNode *node) {
    if (!node) return;
    _postOrder(node->left);
    _postOrder(node->right);
    cout << node->key << ", ";
}


/*

    Public Methods

*/

/** Constructs an empty binary search tree. */
BST::BST() : m_root(nullptr) {
}

/** Destroys the BST and frees memory. */
BST::~BST() {
    _deleteTree(m_root);
}

/** Prints all key-value pairs in sorted order. */
void BST::printTree() const {
    const BSTNode *node = _min(m_root);
    cout << "[";
    while (node) {
        cout << "(" << node->key << "," << node->data << ")";
        node = _successor(node);
        if (node) cout << ", ";
    }
    cout << "]\n";
}

/** Searches for a node by key and returns associated data, or "" if not found. */
string BST::search(const int key) const {
    BSTNode *node = _findNode(key);
    return node ? node->data : "";
}

/** Inserts a new node with a given key and data. */
void BST::insert(const int key, const string &data) {
    auto *newNode = new BSTNode{nullptr, nullptr, nullptr, key, data};

    if (m_root == nullptr) {
        m_root = newNode;
        return;
    }

    BSTNode *parent = m_root;
    BSTNode *current = m_root;
    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}


/** Deletes the node with the given key and returns associated data, or "" if not found. */
string BST::remove(const int key) {
    BSTNode *node = _findNode(key);
    if (!node) return "";
    string removedData = node->data;
    BSTNode *replacement = _getReplacement(node);
    _replaceNode(node, replacement);
    if (node->left && node->right) {
        const BSTNode *successor = _min(node->right);
        node->key = successor->key;
        node->data = successor->data;
        remove(successor->key);
    }
    delete node;
    return removedData;
}

/** Computes and returns the height of the tree. */
int BST::height() const {
    return _height(m_root);
}

/** Prints the keys using preorder traversal. */
void BST::preOrder() const {
    cout << "[";
    _preOrder(m_root);
    cout << "]\n";
}

/** Prints the keys using inorder traversal. */
void BST::inOrder() const {
    cout << "[";
    _inOrder(m_root);
    cout << "]\n";
}

/** Prints the keys using postorder traversal. */
void BST::postOrder() const {
    cout << "[";
    _postOrder(m_root);
    cout << "]\n";
}
