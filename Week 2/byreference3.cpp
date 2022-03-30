// PL1/byreference3.cpp
// Use of a reference variable
// Niels Walet, last updated 04/12/2019
#include<iostream> 
int main() 
{ 
  int number{4}; 
  int &reference{number}; 
  int *ptr = &number;
  std::cout<<number<<" "<<*ptr << " " <<reference<<std::endl; 
  number++; 
  std::cout<<number<<" "<<*ptr << " " <<reference<<std::endl; 
  return 0;
}
