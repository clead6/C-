#ifndef TETRONIMOS_H
#define TETRONIMOS_H

#include <iostream>
#include <string>
#include "board.h"

class tetrominos
{
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