cmake_minimum_required(VERSION 3.29)
project(clion_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(clion_test main.cpp
        test_new_class_interface.h
        test_new_class_interface.cpp)
