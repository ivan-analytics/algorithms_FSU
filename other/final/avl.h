#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

// Definition of the AVLTree class
class AVLTree {
private:
    // Definition of the Node structure
    struct Node {
        int key;         // The key value
        Node* left;      // Pointer to the left child
        Node* right;     // Pointer to the right child
        int height;      // Height of the node

        Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root; // Root of the AVL Tree

    // Helper functions
    int height(Node* node);
    int getBalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, int key);
    Node* minValueNode(Node* node);
    Node* deleteNode(Node* node, int key);
    void inOrderTraversal(Node* node);

public:
    AVLTree();                           // Constructor
    ~AVLTree();                          // Destructor
    void insert(int key);                // Public insert function
    void deleteKey(int key);             // Public delete function
    bool search(int key);                // Search for a key
    void inOrder();                      // Public in-order traversal
};

#include "AVLTree.hpp" // Include the implementation

#endif // AVLTREE_H
