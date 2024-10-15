#include "MyMemoryBlock.h"


// constructor of the class. It will initialize the member variables index and length, using ind and len, respectively
MyMemoryBlock(int ind = 0, int len = 0) {
    index = ind;
    length = len;
}

// return the current length of the memory block
int get_length() {
    return length;
}

// return the index of the memory block
int get_index() {
    return index;
}

// this function emulates memory allocation
int allocate_mem(int len) {
    if (length < len) return -1; // the block does not have that much memory

    length -= len;

    return len;

}

// this function emulates memory de-allocation
void free_mem(int len) {
    length += len;
}