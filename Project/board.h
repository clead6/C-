// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Declares Board class

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

class board
{
private:
    int height{0};
    int length{0};
    std::string *console{nullptr};

public:
    board()=default;
    board(int h, int l); // parameterised constructor
    ~board(); // destructor
    const int get_length() {return length;}
    const int get_height() {return height;}
    std::string *get_console() {return console;}
    const void print_board();
    const bool game_over();
    const int delete_rows();
    const int index(int i, int j) const; 
    std::string & operator()(const int i, const int j) const; 
};

#endif
