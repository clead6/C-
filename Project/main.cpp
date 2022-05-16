#include <iostream>
#include <string>
#include <limits>
#include "tetris.h"

int main() 
{
    system("cls");
    int game_mode {};
    std::cout << "Welcome to Tetris! Enter 1 to play a speed game, or 2 for a marathon version. " << std::endl;
    std::cin >> game_mode;
    while (std::cin.fail() || (game_mode!=1 & game_mode!=2)) {
        std::cout << "Invalid input, enter 1 to play a speed game, or 2 for a marathon version. " << std::endl; // Needs to be >= 1
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> game_mode;
    }

    if (game_mode==1) {
        std::unique_ptr<speed::tetris> game(new speed::tetris);
        game->initialize_game();
    } else if (game_mode==2) {
        std::unique_ptr<marathon::tetris> game(new marathon::tetris);
        game->initialize_game();
    }

}