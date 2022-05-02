#ifndef TETRONIMOS
#define TETRONIMOS

#include <iostream>
#include <string>
#include "board.h"

class tetrominos
{
protected:
    std::string *piece {nullptr};
    int horizontal_position {};
    int vertical_position {};
    int rotation {0};
public:
    virtual void print_piece(board &board)=0;
    virtual void move_down(board &board)=0;
    virtual void move_right(board &board)=0;
    virtual void move_left(board &board)=0;
    virtual void rotate(board &board)=0;
    virtual bool bottom_wall(board &board)=0;
    virtual bool right_wall(board &board)=0;
    virtual bool left_wall(board &board)=0;
};

#endif