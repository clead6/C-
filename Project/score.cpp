#include <iostream>
#include <string>
#include "board.h"
#include "tetris.h"

score::~score()
{
    std::cout << "delete score" << std::endl;
}

int score::points_pieces()
{
    score_count+=25;
    return score_count;
}

int score::points_lines(int &level, int &lines_deleted)
{
    if (lines_deleted==1) {
        score_count += (level+1)*40;
    } else if (lines_deleted==2) {
        score_count += (level+1)*100;
    } else if (lines_deleted==3) {
        score_count += (level+1)*300;
    } else if (lines_deleted==4) {
        score_count += (level+1)*1000;
    } 
    return score_count;
}

void score::print_score(int &level, int &score_count)
{
    std::cout << "Level " << level << "\tScore " << score_count << std::endl;
}