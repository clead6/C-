#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
#include "board.h"

class tetris 
{
private:
    int score{};

public:
    tetris()=default;
    void initialize_game();
};

#endif