#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

class board
{
protected:
    int height{0};
    int length{0};
    std::string *console{nullptr};

public:
    board()=default;
    board(int h, int l); // parameterised constructor
    ~board(); // destructor
    int get_length() {return length;}
    int get_height() {return height;}
    std::string *get_console() {return console;}
    void print_board();
    bool game_over();

    int index(int i, int j) const; 
    std::string & operator()(const int i, const int j) const; 
};

#endif
