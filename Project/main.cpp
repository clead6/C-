#include <iostream>
#include <string>
#include "tetris.h"

int main() 
{
    std::unique_ptr<tetris> game(new tetris);
    game->initialize_game();
}