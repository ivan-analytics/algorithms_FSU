//
// Created by Ivan Liuliaev on 8/29/24.
//

#ifndef TEST_NEW_CLASS_INTERFACE_H
#define TEST_NEW_CLASS_INTERFACE_H

#include <string>

class MyClass {
public:
    // Constructor
    MyClass(int value, const std::string& name);

    // Destructor
    ~MyClass();

    // Public methods
    int getValue() const;
    void setValue(int value);

    std::string getName() const;
    void setName(const std::string& name);

    void printInfo() const;

private:
    // Private members
    int value_;
    std::string name_;
};




#endif //TEST_NEW_CLASS_INTERFACE_H
