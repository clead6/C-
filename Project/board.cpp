#include <iostream>
#include <string>
#include <algorithm>
#include "board.h"

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

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
    std::cout << "delete board" << std::endl;
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
        std::cout << WHT << console[i]; // use string streams
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
    return (j-1)*length+(i-1);
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

int board::delete_rows()
{
    bool row_full {true};
    int number_rows {};
    while (row_full) {
        for (int i{1};i<=length;i++) {
            if (console[index(i,height)]!="#") {
                row_full = false;
                break;
            }
        }

        if (row_full==true) {
            for (int j{height}; j>1; j--) {
                for (int i{1}; i<=length; i++) {
                    console[index(i,j)]=console[index(i,j-1)];
                }
            }

            for (int i{1}; i<=length; i++) {
                console[index(i,1)]=" ";
            }
            number_rows+=1;
        }
            

    }
    return number_rows;

}