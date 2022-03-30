// PL3/carray.cpp
// Demonstration  of the "C" style array
// Niels Walet, last updated 04/12/2019
#include<iostream>
#include<string>
int main() 
{
  const size_t n_a{5};
  double a[n_a];
  for(size_t i{};i<n_a;i++) a[i]=static_cast<double>(i+1);
  for(size_t i{};i<n_a;i++) std::cout<<"a["<<i<<"] = "<<a[i]<<std::endl;
  return 0;
}
