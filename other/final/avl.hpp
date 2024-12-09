#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "AVLTree.h"

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Destructor helper to delete all nodes
AVLTree::~AVLTree() {
    // Implement a post-order traversal to delete nodes
    // For simplicity, we'll skip it here. In production code, ensure all nodes are deleted.
}

// Get the height of the node
int AVLTree::height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Get balance factor of node
int AVLTree::getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Right rotate subtree rooted with y
AVLTree::Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
AVLTree::Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Insert a key into the subtree rooted with node and returns the new root
AVLTree::Node* AVLTree::insert(Node* node, int key) {
    // 1. Perform the normal BST insertion
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Duplicate keys not allowed
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // 3. Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);

    // If node is unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Public insert function
void AVLTree::insert(int key) {
    root = insert(root, key);
}

// Find the node with the smallest key value
AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;

    // Loop down to find the leftmost leaf
    while (current->left != nullptr)
        current = current->left;

    return current;
}


void remove( const Comparable & x, AvlNode * & t )
{
    if( t == nullptr )
        return; // item not found; do nothing
    else if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != nullptr && t->right != nullptr ) { // two children
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else {
        BinaryNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }
    balance( t );
}


// Delete a node with given key and return new root
AVLTree::Node* AVLTree::deleteNode(Node* node, int key) {
    // STEP 1: Perform standard BST delete
    if (node == nullptr)
        return node;

    // If the key to be deleted is smaller than the node's key, it lies in left subtree
    if (key < node->key)
        node->left = deleteNode(node->left, key);

    // If the key to be deleted is greater than the node's key, it lies in right subtree
    else if (key > node->key)
        node->right = deleteNode(node->right, key);

    // If key is same as node's key, this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((node->left == nullptr) || (node->right == nullptr)) {
            Node* temp = node->left ? node->left : node->right;

            // No child case
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else // One child case
                *node = *temp; // Copy the contents of the non-empty child

            delete temp;
        }
        else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);

            // Copy the inorder successor's data to this node
            node->key = temp->key;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (node == nullptr)
        return node;

    // STEP 2: Update height of the current node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // STEP 3: Get the balance factor
    int balance = getBalance(node);

    // If node is unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Public delete function
void AVLTree::deleteKey(int key) {
    root = deleteNode(root, key);
}

// In-order traversal
void AVLTree::inOrderTraversal(Node* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << node->key << " ";
        inOrderTraversal(node->right);
    }
}

// Public in-order traversal
void AVLTree::inOrder() {
    inOrderTraversal(root);
    std::cout << std::endl;
}

// Search for a key in the AVL Tree
bool AVLTree::search(int key) {
    Node* current = root;
    while (current != nullptr) {
        if (key == current->key)
            return true;
        else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

#endif // AVLTREE_HPP
