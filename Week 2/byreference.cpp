// PL1/by_reference.cpp
// Call by value using pointer
// Niels Walet, last updated 04/12/2019
#include<iostream> 
void double_value(double *ptr_double) 
{
  (*ptr_double)*=2;
}
int main() 
{ 
  double number{4.}; 
  double* ptr_number = &number;
  std::cout<<number<<std::endl; 
  std::cout<<ptr_number<<std::endl;
  double_value(&number); 
  std::cout<<number<<std::endl; 
  return 0; 
}