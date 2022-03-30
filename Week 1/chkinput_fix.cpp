// PL1/chkinput.cpp
// variation on simple.cpp, checking for valid input
// Niels Walet, last updated 04/12/2019
#include<iostream>
int main() 
{
  int any_year; 
  std::cout << "Enter a year: "; 
  std::cin >> any_year;
  // Check input is valid 
  while(true) {
      if (std::cin.fail()) {
        std::cin.clear(); 
        std::cin.ignore();
        std::cout <<"Sorry, your input was not valid, please enter a year: "; 
        std::cin >> any_year;
      }
      else {break;
      }
  }
  std::cout<<"C++ is the best programming language in "<<any_year<<"!"<<std::endl;
}