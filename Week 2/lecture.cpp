#include<iostream> 

int main() 
{ 
    double* x; // create a pointer 
    std::cout << &x << std::endl; 
    double y(2); // initialize y to 2
    std::cout << &y << std::endl;
    x=&y; // x refers to y (x gets y's address)
    std::cout << *x << " " << &x << std::endl; // dereference x
}