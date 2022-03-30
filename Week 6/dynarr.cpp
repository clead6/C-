// PL6/dynarr.cpp
// A dynamic array class
// Niels Walet, last updated 23/02/2019
#include<iostream>
class dynamic_array
{
private:
    size_t size {};
    double *array {nullptr};
public:
    dynamic_array()
        {std::cout<<"Default constructor called"<<std::endl;}
    dynamic_array(size_t s);
    ~dynamic_array(){delete array; std::cout<<"Destructor called"<<std::endl;}
    size_t length() const {return size;}
    double & operator[](size_t i);
};
dynamic_array::dynamic_array(size_t size_req)
// Parameterized constructor implementation
{
    std::cout<<"Parameterized constructor called"<<std::endl;
    if(size_req<1) {
        std::cout<<"Error: trying to declare an array with size < 1"<<std::endl;
        throw("size not positive");
    }
    size = size_req;
    array = new double[size];
    for(size_t i{}; i<size; i++) array[i]=0;
}
double & dynamic_array::operator[](size_t i)
// Overloaded element [] operator implementation with bounds checking
{
    if(i<0 || i>=size) {
        std::cout<<"Error: trying to access array element out of bounds"<<std::endl;
        throw("Out of Bounds error");
    }
    return array[i];
}
int main()
{
    std::cout<<"Declaring array a1 with parameterized constructor"<<std::endl;
    dynamic_array a1{2};
    std::cout<<"Length of a1 = "<<a1.length()<<std::endl;
    a1[0] = 0.5;
    a1[1] = 1.0;
    std::cout<<"a1[0] = "<<a1[0]<<std::endl;
    std::cout<<"a1[1] = "<<a1[1]<<std::endl;
    std::cout<<std::endl;
    return 0;
}