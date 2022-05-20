// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Declares S Piece class - derived class of Tetrominos

#ifndef S_PIECE_H
#define S_PIECE_H

#include <iostream>
#include <string>
#include "board.h"
#include "tetrominos.h"

class s_piece: public tetrominos
{
protected:
    std::string *piece {nullptr};
    int horizontal_position {};
    int vertical_position {};
    int rotation {0};
public:
    s_piece(board &board);
    ~s_piece();
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