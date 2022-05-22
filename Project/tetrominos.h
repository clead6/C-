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
    virtual void print_piece(const board &board)=0;
    virtual void move_down(board &board)=0;
    virtual void move_right(board &board)=0;
    virtual void move_left(board &board)=0;
    virtual void rotate(board &board)=0;
    virtual bool bottom_wall(const board &board)=0;
    virtual bool right_wall(const board &board)=0;
    virtual bool left_wall(const board &board)=0;
};

#endif