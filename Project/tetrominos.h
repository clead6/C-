// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Declares virtual Tetrominos class

#ifndef TETROMINOS_H
#define TETROMINOS_H

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