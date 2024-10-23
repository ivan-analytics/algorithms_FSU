#include "MyMemoryBlock.h"


// constructor of the class. It will initialize the member variables index and length, using ind and len, respectively
MyMemoryBlock::MyMemoryBlock(int ind, int len) {
    index = ind;
    length = len;
}

// return the current length of the memory block
int MyMemoryBlock::get_length() {
    return length;
}

// return the index of the memory block
int MyMemoryBlock::get_index() {
    return index;
}

// this function emulates memory allocation
int MyMemoryBlock::allocate_mem(int len) {
    if (length < len) return -1; // the block does not have that much memory

    length -= len;

    return len;

}

// this function emulates memory de-allocation
void MyMemoryBlock::free_mem(int len) {
    length += len;
}


bool MyMemoryBlock::operator==(const MyMemoryBlock& other) const {
    return this->index == other.index;
}

bool MyMemoryBlock::operator!=(const MyMemoryBlock& other) const {
    return !this->operator==(other);
}

void MyMemoryBlock::print(std::ostream& os) const {
    os << "Block(index = " << this->index << "): " << this->length << std::endl;
}