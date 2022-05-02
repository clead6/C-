#include <iostream>
#include <string>
#include "board.h"

board::board(int h, int l) 
{
    height = h;
    length = l;
    console = new std::string[height*length];

    for (size_t i{}; i<(height*length);i++) {
        console[i]=" ";
    }
}

board::~board()
{
    height = 0;
    length = 0;
    delete[] console;
}

void board::print_board() 
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
        std::cout << console[i]; // use string streams
    }

    std::cout << "|" << std::endl << "|";
    for (int j{0};j<length;j++) {
        std::cout << "-";
    }
    std::cout << "|" << std::endl;
}

int board::index(int i, int j) const
{
    if(i<=0 || i>length || j<=0 || j>height) {
        std::cout << "Element out of bounds" << std::endl;
        throw;
    }
    return (j-1)*height+(i-1);
}

std::string &board::operator()(const int i, const int j) const
{
    return console[index(i,j)];
}

bool board::game_over() 
{
    for (int i{1};i<=length;i++) {
        if (console[index(i,1)]=="#" && console[index(i,2)]=="#") {

            return true;
        }
    }
    return false;
}