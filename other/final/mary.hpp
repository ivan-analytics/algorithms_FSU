#ifndef MARYTREET_HPP
#define MARYTREET_HPP

#include "MArityTree.h"

// Constructor
template <typename T, int M>
MArityTree<T, M>::MArityTree() : root(nullptr) {}

// Destructor
template <typename T, int M>
MArityTree<T, M>::~MArityTree() {}

// Insert a child under a parent
template <typename T, int M>
bool MArityTree<T, M>::insert(const T& parent, const T& child) {
    // If tree is empty, insert root if parent equals child
    if (root == nullptr) {
        if (parent == child) { // Assuming parent value equals child value for root
            root = std::make_unique<Node>(child);
            return true;
        } else {
            std::cerr << "Parent not found. Cannot insert node.\n";
            return false;
        }
    }

    // Find the parent node
    Node* parentNode = findNode(root.get(), parent);
    if (parentNode != nullptr) {
        if (static_cast<int>(parentNode->children.size()) < M) {
            parentNode->children.emplace_back(std::make_unique<Node>(child));
            return true;
        } else {
            std::cerr << "Parent already has maximum children (" << M << ").\n";
            return false;
        }
    }

    std::cerr << "Parent node not found.\n";
    return false;
}

// Search for a value in the tree
template <typename T, int M>
bool MArityTree<T, M>::search(const T& value) const {
    return findNode(root.get(), value) != nullptr;
}

// Remove a node (only leaf nodes can be removed)
template <typename T, int M>
bool MArityTree<T, M>::remove(const T& value) {
    if (root == nullptr) {
        std::cerr << "Tree is empty. Cannot remove node.\n";
        return false;
    }

    // Special case: if root is the node to remove
    if (root->data == value) {
        if (root->children.empty()) {
            root.reset();
            return true;
        } else {
            std::cerr << "Cannot remove node with children.\n";
            return false;
        }
    }

    // Attempt to remove the node
    return removeNode(nullptr, root.get(), value);
}

// Traverse the tree and print node values
template <typename T, int M>
void MArityTree<T, M>::traverse() const {
    traverseNode(root.get());
    std::cout << std::endl;
}

// Private method to find a node with a specific value
template <typename T, int M>
typename MArityTree<T, M>::Node* MArityTree<T, M>::findNode(Node* current, const T& value) const {
    if (current == nullptr) return nullptr;
    if (current->data == value) return current;

    for (const auto& child : current->children) {
        Node* found = findNode(child.get(), value);
        if (found != nullptr) return found;
    }
    return nullptr;
}

// Private method to remove a leaf node with a specific value
template <typename T, int M>
bool MArityTree<T, M>::removeNode(Node* parent, Node* current, const T& value) {
    for (auto it = current->children.begin(); it != current->children.end(); ++it) {
        if ((*it)->data == value) {
            if ((*it)->children.empty()) {
                current->children.erase(it);
                return true;
            } else {
                std::cerr << "Cannot remove node with children.\n";
                return false;
            }
        }
        // Recursive call
        if (removeNode(current, it->get(), value)) {
            return true;
        }
    }
    return false;
}

// Private method to traverse and print the tree in pre-order
template <typename T, int M>
void MArityTree<T, M>::traverseNode(const Node* node) const {
    if (node == nullptr) return;
    std::cout << node->data << " ";
    for (const auto& child : node->children) {
        traverseNode(child.get());
    }
}

#endif // MARYTREET_HPP
