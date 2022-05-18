#ifndef I_PIECE_H
#define I_PIECE_H

#include <iostream>
#include <string>
#include "board.h"
#include "tetronimos.h"

class i_piece: public tetrominos
{
public:
    i_piece(board &board);
    ~i_piece();
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