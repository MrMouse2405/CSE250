/****************************************************************************\
* main->cpp
*
*  Created on: 2025
*      Author: YOUR NAME
*
*
*  binary search tree by testing ALL the cases in provided documents->
*  Your output must be EXPLICIT about what is tested and what is the result->
*
\***************************************************************************/

#include <iostream>
#include "BST.h"
using namespace std;

inline void preorder(const BST *tree) {
    cout << "preOrder: ";
    tree->preOrder();
}

inline void postorder(const BST *tree) {
    cout << "postOrder: ";
    tree->postOrder();
}

inline void inorder(const BST *tree) {
    cout << "inOrder: ";
    tree->inOrder();
}

inline void search(const BST *tree, const int key) {
    if (const string result = tree->search(key); result.empty()) {
        cout << "search(" << key << "): " << "[null]" << "\n";
    } else {
        cout << "search(" << key << "): " << result << "\n";
    }
}

inline void remove(BST *tree, const int key) {
    if (const string result = tree->remove(key); result.empty()) {
        cout << "remove(" << key << "): " << "[null]" << "\n";
    } else {
        cout << "remove(" << key << "): " << result << "\n";
    }
}

inline void height(const BST *tree) {
    cout << "height: " << tree->height() << "\n";
}

inline void print(const BST *tree) {
    cout << "tree:\n";
    tree->printTree();
}

int main() {
    cout << "-------------------------- Question 1 --------------------------\n"; {
        const auto tree = new BST();
        preorder(tree);
        postorder(tree);
        inorder(tree);
        search(tree, 4);
        print(tree);
        height(tree);
        remove(tree, 4);
    }
    cout << "-------------------------- Question 2 --------------------------\n"; {
        const auto tree = new BST();
        /*

            question

         */
        string ret = tree->remove(5);
        tree->insert(5, "data5");
        ret = tree->remove(5);
        tree->insert(10, "data10");
        /*

            Answer

         */
        preorder(tree);
        postorder(tree);
        inorder(tree);
        search(tree, 4);
        search(tree, 5);
        search(tree, 10);
        print(tree);
        height(tree);
        remove(tree, 5);
        remove(tree, 10);
    }
    cout << "-------------------------- Question 3 --------------------------\n"; {
        const auto tree = new BST();
        /*

            question

         */
        tree->insert(10, "Data10");
        tree->insert(5, "Data5");
        tree->insert(15, "Data15");
        tree->insert(6, "Data6");
        tree->insert(3, "Data3");
        tree->insert(16, "Data16");
        tree->insert(13, "Data13");
        tree->insert(2, "Data2");
        tree->remove(5);
        /*

            Answer

         */
        preorder(tree);
        postorder(tree);
        inorder(tree);
        search(tree, 13);
        search(tree, 100);
        search(tree, 15);
        print(tree);
        height(tree);
    }
    return 0;
}
