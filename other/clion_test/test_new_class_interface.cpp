//
// Created by Ivan Liuliaev on 8/29/24.
//

#include "test_new_class_interface.h"
#include <iostream>

// Constructor
MyClass::MyClass(int value, const std::string& name)
    : value_(value), name_(name) {}

// Destructor
MyClass::~MyClass() {
    // Optional: Clean up resources if necessary
}

// Getter for value
int MyClass::getValue() const {
    return value_;
}

// Setter for value
void MyClass::setValue(int value) {
    value_ = value;
}

// Getter for name
std::string MyClass::getName() const {
    return name_;
}

// Setter for name
void MyClass::setName(const std::string& name) {
    name_ = name;
}

// Print information about the object
void MyClass::printInfo() const {
    std::cout << "Value: " << value_ << ", Name: " << name_ << std::endl;
}
