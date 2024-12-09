#ifndef MARYTREET_H
#define MARYTREET_H

#include <vector>
#include <memory>
#include <iostream>

/**
 * @brief A simplified M-ary Tree implementation.
 * 
 * @tparam T The type of data stored in the tree nodes.
 * @tparam M The maximum number of children each node can have.
 */
template <typename T, int M>
class MArityTree {
private:
    /**
     * @brief Structure representing a tree node.
     */
    struct Node {
        T data;  // Data stored in the node
        std::vector<std::unique_ptr<Node>> children;  // Child nodes

        /**
         * @brief Constructor to initialize a node with data.
         * 
         * @param value The value to store in the node.
         */
        Node(const T& value) : data(value), children() {}
    };

    std::unique_ptr<Node> root;  // Root of the tree

public:
    // Constructor and Destructor
    MArityTree();
    ~MArityTree();

    // Public Methods
    /**
     * @brief Inserts a child node under a specified parent node.
     * 
     * @param parent The value of the parent node.
     * @param child The value of the child node to insert.
     * @return true If insertion is successful.
     * @return false If parent is not found or parent already has M children.
     */
    bool insert(const T& parent, const T& child);

    /**
     * @brief Searches for a node with the specified value.
     * 
     * @param value The value to search for.
     * @return true If the value is found.
     * @return false If the value is not found.
     */
    bool search(const T& value) const;

    /**
     * @brief Removes a node with the specified value.
     * 
     * @param value The value of the node to remove.
     * @return true If removal is successful.
     * @return false If the node is not found or has children (only leaf nodes can be removed).
     */
    bool remove(const T& value);

    /**
     * @brief Traverses the tree in pre-order and prints node values.
     */
    void traverse() const;

private:
    // Private Helper Methods
    /**
     * @brief Finds a node with the specified value.
     * 
     * @param current The current node being searched.
     * @param value The value to search for.
     * @return Node* Pointer to the found node or nullptr if not found.
     */
    Node* findNode(Node* current, const T& value) const;

    /**
     * @brief Removes a node with the specified value. Only removes leaf nodes.
     * 
     * @param parent The parent of the current node.
     * @param current The current node being searched.
     * @param value The value of the node to remove.
     * @return true If removal is successful.
     * @return false Otherwise.
     */
    bool removeNode(Node* parent, Node* current, const T& value);

    /**
     * @brief Helper method to traverse and print the tree.
     * 
     * @param node The current node being traversed.
     */
    void traverseNode(const Node* node) const;
};

// Include the implementation file
#include "MArityTree.hpp"

#endif // MARYTREET_H
