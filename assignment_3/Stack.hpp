#include "Stack.h"

#include <iostream>
#include <stdexcept>


template <typename T>
cop4530::Stack<T>::Stack() {
    this->elements = std::vector<T>{};
} // zero-argument constructor.

template <typename T>
cop4530::Stack<T>::Stack(const Stack<T>& other) {
    this->elements = other.elements;
} // copy constructor.   

template <typename T>
cop4530::Stack<T>::Stack(Stack<T> &&other) {
    this->elements = std::move(other.elements);
} // move constructor.

template <typename T>
cop4530::Stack<T>::~Stack() {
    // vector container will delete elements on its own
} // destructor

template <typename T>
cop4530::Stack<T>& cop4530::Stack<T>::operator=(const Stack <T>& other) {
    if (this != &other)
        this->elements = other.elements;
    return this*;
} // copy assignment operator=

template <typename T>
cop4530::Stack<T>& cop4530::Stack<T>::operator=(const Stack <T>&&) {
    if (this != &other)
        this->elements = std::move(other.elements);
    return this*;
} // move assignment operator=

template <typename T>
bool cop4530::Stack<T>::empty() const {
    return elements.empty();
} // returns true if the Stack contains no elements, and false otherwise  

template <typename T>
void cop4530::Stack<T>::clear() {
    this->elements.clear();
} // delete all elements from the stack

template <typename T>
void cop4530::Stack<T>::push(const T& x) {
    this->elements.push_back(x);
} // adds x to the Stack copy version

template <typename T>
void cop4530::Stack<T>::push(const T&& x) {
    this->elements.push_back(std::move(x));
} // adds x to the Stack copy version

template <typename T>
void cop4530::Stack<T>::pop() {
    if (this->elements.empty()) throw std::runtime_error("pop() is called but stack is already empty")
    this->elements.pop_back(x);
} // removes and discards the most recently added element of the Stack

template <typename T>
T& cop4530::Stack<T>::top() {
    if (this->elements.empty()) throw std::runtime_error("top() is called but stack is empty")
    return this->elements.back();
} // mutator that returns a reference to the most recently added element of the Stack


template <typename T>
const T& cop4530::Stack<T>::top() const {
    if (this->elements.empty()) throw std::runtime_error("top() is called but stack is empty")
    return const this->elements.back();
} // accessor that returns the most recently added element of the Stack  

template <typename T>
int cop4530::Stack<T>::size() const {
    return this->elements.size();
} // returns the number of elements stored in the Stack

// print elements of Stack to ostream os. ofc is the separator between elements in the stack when they are printed out 
// Note that print() prints elements in the opposite order of the Stack (that is, the oldest element should be printed first)
template <typename T>
void cop4530::Stack<T>::print(std::ostream& os, char ofc = ' ') const {
    for (auto& el : this->elements)
        os << el << ofc;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const cop4530::Stack<T>& a) {
    a.print();
    return os;
} // invokes the print() method to print the Stack<T> a in the specified ostream    

template <typename T>
bool operator==(const cop4530::Stack<T>& s1, const cop4530::Stack<T>& s2) {
    // checking the first pair of elements before copying two stacks for higher efficiency
    // hence starting the loop from i=1 instead of 0
    if (s1.empty() && s2.empty()) return true;
    if ((s1.size() != s2.size()) || (s1.top() != s2.top())) return false;
    
    cop4530::Stack<T> s1_ = s1;
    cop4530::Stack<T> s2_ = s2;
    s1_.pop();
    s2_.pop();
    // picking s1.size() since the sizes should be equal at this point 
    for (int i = 1; i < s1.size(); i++) {
        if (s1_.top() != s2_.top()) return false;
        s1_.pop();
        s2_.pop();
    }

    // stacks are equal
    return true;
} // returns true if the two compared Stacks have the same elements, in the same order  

template <typename T>
bool operator!=(const cop4530::Stack<T>& s1, const cop4530::Stack<T>& s2) {
    return !(s1 == s2);
} // opposite of operator==()

// returns true if every element in Stack a is smaller than or equal to the corresponding element of Statck b, 
// i.e., if repeatedly invoking top() and pop() on both a and b,  
// we will generate a sequence of elements a_i from a and b_i from b, and for every i,  a_i <= b_i, until a is empty.
template <typename T>
bool operator<=(const cop4530::Stack<T>& s1, const cop4530::Stack <T>& s2) {
    // checking the first pair of elements before copying two stacks for higher efficiency
    // hence starting the loop from i=1 instead of 0
    if (s1.empty() && s2.empty()) return true;
    if (s1.empty() || s2.empty()) return false; // if one is empty, but not both - stop right there and return false as they clearly are not equal
    if (s1.top() > s2.top()) return false;
    
    cop4530::Stack<T> s1_ = s1;
    cop4530::Stack<T> s2_ = s2;
    s1_.pop();
    s2_.pop();
    // picking s1.size() since we check only until s1 is empty as instructed in assignment requirements
    for (int i = 1; i < s1.size(); i++) {
        if (s1_.top() > s2_.top()) return false;
        s1_.pop();
        s2_.pop();
    }

    return true;
}
