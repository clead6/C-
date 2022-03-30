// PL1/by_reference2.cpp
// Arrays vs. pointers
// Niels Walet, last updated 04/12/2019
#include<iostream> 
void print_array(const int array_entries, int *array) 
{
  // show that array[i] is equivalent to *(array+i) 
  for(int i{};i<array_entries;i++) 
    std::cout<<array[i]<<" "<<*(array+i)<<std::endl;
  return; 
}
int main() 
{ 
  const int array_entries{3}; 
  int array[array_entries]; 
  for(int i{};i<array_entries;i++) array[i]=i; 
  print_array( array_entries,array); 
  return 0; 
}