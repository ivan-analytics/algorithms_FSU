#ifndef MY_MEMORY_BLOCK_H
#define MY_MEMORY_BLOCK_H
#include "List.h"

class MyMemoryBlock {
    public:
        // constructor of the class. It will initialize the member variables index and length, using ind and len, respectively
        MyMemoryBlock(int ind = 0, int len = 0);

        // return the current length of the memory block
        int get_length();

        // return the index of the memory block
        int get_index();

        // this function emulates memory allocation
        int allocate_mem(int len);

        // this function emulates memory de-allocation
        void free_mem(int len);

        // to be able to utilize remove() method of cop4530::List interface, that compares the elements
        bool operator==(const MyMemoryBlock& other) const;
        bool operator!=(const MyMemoryBlock& other) const;

        void print(std::ostream& os) const; 


    private:
        // memory address
        int index;

        // current length of the memory block
        int length;
};

#endif