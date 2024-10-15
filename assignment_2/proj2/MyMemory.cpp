#include "MyMemory.h"



MyMemory::MyMemory(int num, int len) {
    mlist = cop4530::List<MyMemoryBlock>();

    for (int i = 0; i < num; i++) {
        mlist.push_back(MyMemoryBlock(i, len));
    }

    max_index = num - 1;
    block_size = len;
}



void MyMemory::resize(int num, int len) {
    mlist.clear();

    for (int i = 0; i < num; i++) {
        mlist.push_back(MyMemoryBlock(i, len));
    }

    max_index = num - 1;
    block_size = len;
    
    return;
}




int MyMemory::req_mem(int len) {
    for (auto &mem_block : mlist) {
        if (mem_block.get_length() >= len) {
            mem_block.allocate_mem(len);
            int ind = mem_block.get_index();            
            if (mem_block.get_length() == 0) 
                mlist.remove(mem_block);
            return ind;
        }
    }
    return -1;
}




bool MyMemory::release_mem(int ind, int len) {
    // find this ind
    // if we reach a larger ind, we didnt fouind it, add it
    if ((ind < 0 || ind > max_index) || (len < 0 || len > block_size))
        return false;

    if (mlist.empty()) {
        mlist.push_back(MyMemoryBlock(ind, len));
        return true;
    }

    for (auto itr = mlist.begin(); itr != mlist.end(); itr++) {
        if (itr->get_index() < ind) {
            continue;
        } else if (itr->get_index() == ind) {
            itr->free_mem(len);
            return true;
        } else {
            // if we reached a larger index, that means there is no such index in mlist -> 
            // -> add a new block before the current value to preserve ascending order of indexes
            mlist.insert(itr, MyMemoryBlock(ind, len));
            return true;
        }
    }
    return true;
}



void MyMemory::merge_mem() {
    if (mlist.empty()) return;

    auto itr = mlist.begin();
    auto prev = itr;
    itr++;
    while (itr != mlist.end()) {
        if ((itr->get_length() + (prev->get_length())) <= block_size) {
            prev->free_mem(itr->get_length());
            mlist.remove(*(itr++));
        } else {
            // only move prev if blocks haven't merged
            prev = itr;
            itr++;
        }
    }
}



void MyMemory::dump() {
    std::cout << "Number of blocks: " << mlist.size() << std::endl;
    for (auto &el : mlist)
        el.print(std::cout);
    return;
}


MyMemory::~MyMemory() {
    // mlist will clear all memory blocks in its own destructor;
    // nothing to clean manually
}