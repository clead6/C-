// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Declares T Piece class - derived class of Tetrominos

#ifndef T_PIECE_H
#define T_PIECE_H

#include <iostream>
#include <string>
#include "board.h"
#include "tetrominos.h"

class t_piece: public tetrominos
{
private:
    std::string *piece {nullptr};
    int horizontal_position {};
    int vertical_position {};
    int rotation {0};
public:
    t_piece(board &board);
    ~t_piece();
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