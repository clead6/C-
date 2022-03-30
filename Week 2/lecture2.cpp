#include<iostream>

int main() {
    char* pc = nullptr;
    char& rc = *pc;

    std::cout << rc << std::endl; // nothing gets printed, this is illegal: a pointer must always point to something. 
    // With pointers, need to check for null pointer, while with reference this is not allowed.
}