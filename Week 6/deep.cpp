// PL6/deep.cpp
// An example of a deep copy
// Niels Walet, last updated 23/02/2020
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
    ~dynamic_array(){std::cout<<"Destructor called"<<std::endl;}
    dynamic_array(dynamic_array&); //copy constructor
    dynamic_array& operator=(dynamic_array&); // assignment operator
    size_t length() const {return size;} //function returns size of array
    double & operator[](size_t i); // overload [] operator to return a certain element of the array
};

// Copy constructor using deep copying
dynamic_array::dynamic_array(dynamic_array &to_copy)
{
    array=nullptr; size=to_copy.length();
    if(size>0) {
        array=new double[size];
        // Copy values into new array
        for(size_t i{};i<size;i++) array[i] = to_copy[i];
    }
}

// Assignment operator using deep copying
dynamic_array & dynamic_array::operator=(dynamic_array &rhs)
{
    if(&rhs == this) return *this; // no self assignment
    // First delete this object's array
    delete[] array; array=nullptr; size=0;
    // Now copy size and declare new array
    size=rhs.length();
    if(size>0) {
        array=new double[size];
        // Copy values into new array
        for(size_t i{};i<size;i++) array[i] = rhs[i];
    }
    return *this; // Special pointer!!!
}

// Parameterized constructor implementation
dynamic_array::dynamic_array(size_t size_req)
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

// Overloaded element [] operator implementation with bounds checking
double &dynamic_array::operator[](size_t i) 
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
    //
    std::cout<<"Declaring array a2 with default constructor"<<std::endl;
    dynamic_array a2;
    std::cout<<"Length of a2 = "<<a2.length()<<std::endl;
    std::cout<<"Now copy values from a1 by assignment"<<std::endl;
    a2=a1;
    std::cout<<"Length of a2 = "<<a2.length()<<std::endl;
    std::cout<<"a2[0] = "<<a2[0]<<std::endl;
    std::cout<<"a2[1] = "<<a2[1]<<std::endl;
    std::cout<<std::endl;
    //
    std::cout<<"Declare array a3 and initialize"<<std::endl;
    dynamic_array a3=a1;
    std::cout<<"Length of a3 = "<<a3.length()<<std::endl;
    std::cout<<"a3[0] = "<<a3[0]<<std::endl;
    std::cout<<"a3[1] = "<<a3[1]<<std::endl;
    std::cout<<std::endl;
    //
    std::cout<<"Using other C++ way to declare and initialize"<<std::endl;
    dynamic_array a4{a1};
    std::cout<<"Length of a4 = "<<a4.length()<<std::endl;
    std::cout<<"a4[0] = "<<a4[0]<<std::endl;
    std::cout<<"a4[1] = "<<a4[1]<<std::endl;
    std::cout<<std::endl;
    //
    a1[1] = -2.5;
    std::cout<<"a1[1] = "<<a1[1]<<std::endl;
    std::cout<<"a2[1] = "<<a2[1]<<std::endl;
    std::cout<<"a3[1] = "<<a3[1]<<std::endl;
    std::cout<<"a4[1] = "<<a4[1]<<std::endl;
    return 0;
}