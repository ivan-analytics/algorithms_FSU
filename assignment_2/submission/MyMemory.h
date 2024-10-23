#ifndef MY_MEMORY_H
#define MY_MEMORY_H
#include "MyMemoryBlock.h"

class MyMemory {
    public:
        MyMemory(int num = 0, int len = 0);

        void resize(int num = 100, int len = 100);

        int req_mem(int len);

        bool release_mem(int ind, int len);

        void merge_mem();

        void dump();

        ~MyMemory();

    private:
        cop4530::List<MyMemoryBlock> mlist;

        int max_index;

        // the length of memory blocks
        int block_size;

};

#endif