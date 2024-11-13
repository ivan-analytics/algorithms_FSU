#ifndef DL_BET_H
#define DL_BET_H

#include <string>
#include <iostream>


class BET {
public:
    BET(); 
    BET(const std::string& postfix); 
    BET(const BET&); 
    ~BET(); 
    bool buildFromPostfix(const std::string& postfix); 
    const BET& operator=(const BET&); 
    void printInfixExpression(); 
    void printPostfixExpression(); 
    size_t size(); 
    size_t leaf_nodes(); 
    bool empty(); 

private:
    struct BinaryNode {
        std::string element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const std::string &theElement, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
            : element(theElement), left(lt), right(rt) {}
    };

    BinaryNode *root; // root of the tree

    void printInfixExpression(BinaryNode *n); 
    void makeEmpty(BinaryNode* &t); 
    BinaryNode *clone(BinaryNode *t) const; 
    void printPostfixExpression(BinaryNode *n); 
    size_t size(BinaryNode *t); 
    size_t leaf_nodes(BinaryNode *t);

    // Helper functions
    bool isOperator(const std::string &token); // check if token is operator
    int precedence(const std::string &op); // return precedence of operator
};

#endif
