// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Implements Board class

#include <iostream>
#include <string>
#include <algorithm>
#include "board.h"

// Constructor
board::board(int h, int l) 
{
    height = h;
    length = l;
    console = new std::string[height*length];

    for (size_t i{}; i<(height*length);i++) {
        console[i]=" ";
    }
}

// Destructor
board::~board()
{
    std::cout << "delete board" << std::endl;
    height = 0;
    length = 0;
    delete[] console;
}

// Prints board and limits around it
const void board::print_board() 
{
    std::cout << "|";
    for (int j{0};j<length;j++) {
        std::cout << "-";
    }
    std::cout << "|" << std::endl << "|";

    for (int i{0}; i<(height*length);i++) {
        if (i%length==0 && i!=0) {
            std::cout << "|" << std::endl << "|";
        }
        std::cout << console[i];
    }

    std::cout << "|" << std::endl << "|";
    for (int j{0};j<length;j++) {
        std::cout << "-";
    }
    std::cout << "|" << std::endl;
}

// Index function to easily access console elements
const int board::index(int i, int j) const
{
    if(i<=0 || i>length || j<=0 || j>height) {
        std::cout << "Element out of bounds" << std::endl;
        throw;
    }
    return (j-1)*length+(i-1);
}

// Overload () operator to access console elements
std::string &board::operator()(const int i, const int j) const
{
    return console[index(i,j)];
}

// Checks if game is over
const bool board::game_over() 
{
    for (int i{1};i<=length;i++) {
        if (console[index(i,1)]=="#") {

            return true;
        }
    }
    return false;
}

// Checks if any rows are full and if so deletes them
const int board::delete_rows()
{
    bool row_full {false};
    int number_rows {};
    int is_it_full {0};
    int full_row_number {};

    while(!row_full) {
        for (int i{1};i<=length;i++) {
            for (int j{1};j<=height;j++) {
                if (console[index(j,i)]=="#") {
                    is_it_full+=1;
                }
            }
            
            if (is_it_full==12) {
                row_full=true;
                full_row_number = i;
                is_it_full=0;
                break;
            } else {
                is_it_full=0;
            }
            
        }
        
        if (row_full==true) {
            for (int j{full_row_number}; j>1; j--) {
                for (int i{1}; i<=length; i++) {
                    console[index(i,j)]=console[index(i,j-1)];
                }
            }

            for (int i{1}; i<=length; i++) {
                console[index(i,1)]=" ";
            }

            number_rows+=1;
            row_full=false;
        } else if (row_full==false) {
            break;
        }
    }       
    
    return number_rows;

}