#include <iostream>

#include "test_new_class_interface.h"


int main() {
    int value = 132876;
    std::string str = "Value name";
    MyClass key_value = MyClass(value, str);
    key_value.printInfo();

    // std::cout << "Hello, World 2" << std::endl;
    return 0;
}

// You just practicing or this is out assignment?






