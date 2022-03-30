// PL1/simple_namespace.cpp
// A particularly simple example of C++ in action!
// Demonstrates use of using statement to slect specific functions
// Niels Walet, last updated 04/12/2019
#include<iostream>
using std::cout;
using std::endl;
int main() 
{ 
  const int current_year{2020}; //Declare and initialise
  cout << "C++ is the best programming language in "<<current_year<<"!"<<endl; 
  return 0; 
} 
 