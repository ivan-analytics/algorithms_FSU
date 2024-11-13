#include "bet.h"
#include <stack>
#include <sstream>

// Default constructor
BET::BET() : root(nullptr) {}

// One-parameter constructor
BET::BET(const std::string& postfix) : root(nullptr) {
    buildFromPostfix(postfix);
}

// Copy constructor
BET::BET(const BET& other) : root(nullptr) {
    root = clone(other.root);
}

// Destructor
BET::~BET() {
    makeEmpty(root);
}

// Build tree from postfix expression
bool BET::buildFromPostfix(const std::string& postfix) {
    // Delete existing tree
    makeEmpty(root);

    std::istringstream iss(postfix);
    std::string token;
    std::stack<BinaryNode*> s;

    while (iss >> token) {
        if (isOperator(token)) {
            if (s.size() < 2) {
                // Not enough operands
                makeEmpty(root);
                return false;
            }
            BinaryNode *right = s.top(); s.pop();
            BinaryNode *left = s.top(); s.pop();
            BinaryNode *node = new BinaryNode(token, left, right);
            s.push(node);
        } else {
            // Assuming that token is an operand
            BinaryNode *node = new BinaryNode(token);
            s.push(node);
        }
    }

    if (s.size() != 1) {
        // Too many operands
        makeEmpty(root);
        return false;
    }

    root = s.top();
    return true;
}

// Assignment operator
const BET& BET::operator=(const BET& other) {
    if (this != &other) {
        makeEmpty(root);
        root = clone(other.root);
    }
    return *this;
}

// Print infix expression
void BET::printInfixExpression() {
    printInfixExpression(root);
    std::cout << std::endl;
}

// Print postfix expression
void BET::printPostfixExpression() {
    printPostfixExpression(root);
    std::cout << std::endl;
}

// Size of the tree
size_t BET::size() {
    return size(root);
}

// Number of leaf nodes
size_t BET::leaf_nodes() {
    return leaf_nodes(root);
}

// Check if tree is empty
bool BET::empty() {
    return root == nullptr;
}

// Private member functions

void BET::printInfixExpression(BinaryNode *n) {
    if (n != nullptr) {
        if (n->left && n->right) {
            int currPrecedence = precedence(n->element);

            // Left child
            bool leftParens = false;
            if (isOperator(n->left->element)) {
                int leftPrecedence = precedence(n->left->element);
                if (leftPrecedence < currPrecedence) {
                    leftParens = true;
                }
            }

            // Right child
            bool rightParens = false;
            if (isOperator(n->right->element)) {
                int rightPrecedence = precedence(n->right->element);
                // adding == for right child for cases like "4 - ( 5 - 6 )"
                if (rightPrecedence < currPrecedence || (rightPrecedence == currPrecedence)) {
                    rightParens = true;
                }
            }

            if (leftParens)
                std::cout << "( ";
            printInfixExpression(n->left);
            if (leftParens)
                std::cout << " )";

            std::cout << " " << n->element << " ";

            if (rightParens)
                std::cout << "( ";
            printInfixExpression(n->right);
            if (rightParens)
                std::cout << " )";
        } else {
            std::cout << n->element;
        }
    }
}

void BET::makeEmpty(BinaryNode* &t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

void BET::printPostfixExpression(BinaryNode *n) {
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        std::cout << n->element << " ";
    }
}

size_t BET::size(BinaryNode *t) {
    if (t == nullptr)
        return 0;
    else
        return 1 + size(t->left) + size(t->right);
}

size_t BET::leaf_nodes(BinaryNode *t) {
    if (t == nullptr)
        return 0;
    else if (t->left == nullptr && t->right == nullptr)
        return 1;
    else
        return leaf_nodes(t->left) + leaf_nodes(t->right);
}

// Helper functions

bool BET::isOperator(const std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int BET::precedence(const std::string &op) {
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}