// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Declares Score class

#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <string>
#include <memory>
#include "board.h"
#include "i_piece.h"
#include "tetris.h"

class score
{
private:
    int score_count {};
public:
    score() {score_count=0;}
    ~score();
    const int points_pieces();
    const int points_lines(const int &level, const int &lines_deleted);
    const void print_score(const int &level, int &score_count);
};

#endif