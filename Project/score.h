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
    int points_pieces();
    int points_lines(int &level, int &lines_deleted);
    void print_score(int &level, int &score_count);
};

#endif