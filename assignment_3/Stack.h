#ifndef DL_STACK_H
#define DL_STACK_H
#include <iostream>

namespace cop4530 {
	template <typename T>
		class Stack {
			public:
            Stack(); // zero-argument constructor.
            Stack (const Stack<T>& other); // copy constructor.   
            Stack(Stack<T>&& other); // move constructor.
            
            ~Stack(); // destructor

            Stack<T>& operator=(const Stack <T>& other); // copy assignment operator=
            Stack<T>& operator=(const Stack <T>&& other); // move assignment operator=
            
            bool empty() const; // returns true if the Stack contains no elements, and false otherwise  
            void clear(); // delete all elements from the stack

            void push(const T& x); // adds x to the Stack copy version
            void push(const T&& x); // adds x to the Stack copy version

            void pop(); // removes and discards the most recently added element of the Stack
            T& top(); // mutator that returns a reference to the most recently added element of the Stack
            const T& top() const; // accessor that returns the most recently added element of the Stack  
            
            int size() const; // returns the number of elements stored in the Stack

            // print elements of Stack to ostream os. ofc is the separator between elements in the stack when they are printed out 
            // Note that print() prints elements in the opposite order of the Stack (that is, the oldest element should be printed first)
            void print(std::ostream& os, char ofc = ' ') const;
            
            private:
            std::vector<T> elements;
        };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& a); // invokes the print() method to print the Stack<T> a in the specified ostream    

    template <typename T>
    bool operator==(const Stack<T>& s1, const Stack<T>& s2); // returns true if the two compared Stacks have the same elements, in the same order  
    
    template <typename T>
    bool operator!=(const Stack<T>& s1, const Stack<T>& s2); // opposite of operator==()
    
    // returns true if every element in Stack s1 is smaller than or equal to the corresponding element of Statck s2, 
    // i.e., if repeatedly invoking top() and pop() on both s1 and s2,  
    // we will generate a sequence of elements s1_i from s1 and s2_i from s2, and for every i,  s1_i <= s2_i, until s1 is empty.
    template <typename T>
    bool operator<=(const Stack<T>& s1, const Stack<T>& s2);

    // including the implementation file
    #include "stack.hpp"
}

#endif