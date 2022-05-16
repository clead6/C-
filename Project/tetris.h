#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
#include <memory>
#include "board.h"
#include "i_piece.h"
#include "score.h"

class tetris 
{
private:
    int level {};
    int lines_deleted {};
    int lines_deleted_count {};
    int fallen_pieces {};
    int score_count {};
    std::unique_ptr<board> game_board;
    std::unique_ptr<i_piece> game_piece;
    std::unique_ptr<score> game_score;

public:
    tetris()=default;
    ~tetris();
    void initialize_game();
};


#endif