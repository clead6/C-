// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Declares O Piece class - derived class of Tetrominos

#ifndef O_PIECE_H
#define O_PIECE_H

#include <iostream>
#include <string>
#include "board.h"
#include "tetrominos.h"

class o_piece: public tetrominos
{
protected:
    std::string *piece {nullptr};
    int horizontal_position {};
    int vertical_position {};
    int rotation {0};
public:
    o_piece(board &board);
    ~o_piece();
    void print_piece(board &board);
    void move_right(board &board);
    void move_down(board &board);
    void move_left(board &board);
    void rotate(board &board);
    bool bottom_wall(board &board);
    bool right_wall(board &board);
    bool left_wall(board &board);

};

#endif