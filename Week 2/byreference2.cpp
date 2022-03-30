// PL1/by_reference2.cpp
// Call by value using reference in function definition 
// Niels Walet, last updated 04/12/2019
#include<iostream> 
using namespace std;
void double_value(double& reference) 
{
  reference*=2;
}
int main() 
{ 
  double number{4.}; 
  std::cout<<number<<std::endl; 
  std::cout<<&number<<std::endl;
  double_value(number); 
  std::cout<<number<<std::endl; 
  return 0; 
}