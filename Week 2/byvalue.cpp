// PL1/byvalue.cpp
// Demonstration of a call by value
// Niels Walet, last updated 04/12/2019
#include<iostream> 
void double_value(double value) 
{ 
  value*=2; 
}
int main() 
{ 
  double number{4.}; 
  std::cout<<number<<std::endl; 
  double_value(number); 
  std::cout<<number<<std::endl; 
  return 0; 
} 