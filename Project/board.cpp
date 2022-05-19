#include <iostream>
#include <string>
#include <algorithm>
#include "board.h"
#include <windows.h>

#define RESET "\033[0m"

#define BLACK   "\033[30m"      /* Black */
#define RED     "\u001b[31m" //"\033[31m"     /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

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
        std::cout << console[i];
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
        if (console[index(i,1)]=="#") {

            return true;
        }
    }
    return false;
}

int board::delete_rows()
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