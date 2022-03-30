// PL6/move.cpp
// An example of a move constructor
// Niels Walet, last updated 23/02/2020
#include<iostream>
class dynamic_array
{
private:
    size_t size {};
    double *array {nullptr};
public:
    dynamic_array() {std::cout<<"Default constructor called"<<std::endl;}
    dynamic_array(size_t); // parametrised
    dynamic_array(dynamic_array&); // copy
    dynamic_array(dynamic_array&&); //move
    ~dynamic_array(){std::cout<<"Destructor called"<<std::endl;}
    dynamic_array& operator=(dynamic_array&); //copy assignment
    dynamic_array& operator=(dynamic_array&&); //move assignment
    size_t length() const {return size;}
    double & operator[](size_t i);
};

dynamic_array::dynamic_array(dynamic_array &to_copy)
// Copy constructor using deep copying
{
    // Copy size and declare new array
    std::cout <<"copy constructor\n";
    array=nullptr; size=to_copy.length();
    if(size>0) {
        array=new double[size];
        // Copy values into new array
        for(size_t i{};i<size;i++) array[i] = to_copy[i];
    }
}

dynamic_array::dynamic_array(dynamic_array &&to_move)
// Move constructor
{ // steal the data
    std::cout <<"move constructor\n";
    size=to_move.size;
    array=to_move.array;
    to_move.size=0;
    to_move.array=nullptr;
}

dynamic_array & dynamic_array::operator=(dynamic_array &rhs)
// Assignment operator using deep copying
{
    std::cout <<"copy assignment\n";
    if(&rhs == this) return *this; // no self assignment
    // First delete this object's array
    delete[] array; array=nullptr; size=0;
    // Now copy size and declare new array
    size=rhs.length();
    if(size>0){
        array=new double[size];
        // Copy values into new array
        for(size_t i{};i<size;i++) array[i] = rhs[i];
    }
    return *this; // Special pointer!!!
}

dynamic_array & dynamic_array::operator=(dynamic_array&& rhs)
// Move assignment operator
{
    std::cout <<"move assignment\n";
    std::swap(size,rhs.size);
    std::swap(array,rhs.array);
    return *this; // Special pointer!!!
}
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
    for(size_t i{}; i<size; i++) array[i] = 0;
}
double &dynamic_array::operator[](size_t i) 
// Overloaded element[] operator implementation d
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
    dynamic_array a1(2);
    std::cout<<"Length of a1 = "<<a1.length()<<std::endl;
    a1[0] = 0.5;
    a1[1] = 1.0;
    std::cout<<"a1[0] = "<<a1[0]<<std::endl;
    std::cout<<"a1[1] = "<<a1[1]<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Declaring array a2 with default constructor"<<std::endl;
    dynamic_array a2;
    std::cout<<"Length of a2 = "<<a2.length()<<std::endl;
    std::cout<<"Now copy values from a1 by assignment"<<std::endl;
    a2=a1;
    std::cout<<"Length of a2 = "<<a2.length()<<" and of a1 ="<<a1.length()<<std::endl;
    std::cout<<"a2[0] = "<<a2[0]<<std::endl;
    std::cout<<"a2[1] = "<<a2[1]<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Declaring array a3 with parameterized constructor"<<std::endl;
    dynamic_array a3(2);
    std::cout<<"Length of a3 = "<<a3.length()<<std::endl;
    a3[0] = 0.5;
    a3[1] = 1.0;
    std::cout<<"a3[0] = "<<a3[0]<<std::endl;
    std::cout<<"a3[1] = "<<a3[1]<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Now move values from a1 by assignment"<<std::endl;
    dynamic_array a4;
    a4= std::move(a3);
    std::cout<<"Length of a4 = "<<a4.length()<<" and of a3 ="<<a3.length()<<std::endl;
    std::cout<<"a4[0] = "<<a4[0]<<std::endl;
    std::cout<<"a4[1] = "<<a4[1]<<std::endl;
    std::cout<<std::endl;

  return 0;
}