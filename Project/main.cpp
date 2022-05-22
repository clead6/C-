// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Main file: starts the game

#include <iostream>
#include <string>
#include <limits>
#include "tetris.h"

// Clears screen by printing empty lines - static function as implemented in different files
static void clear_screen()
{
    std::cout << std::string(30, '\n' );
}

// Template for input validation
template <typename T> bool is_it_correct(T game_mode, T input_1, T input_2)
{
    if (game_mode!=input_1 & game_mode!=input_2) {
        return false;
    } else {
        return true;
    }
}

int main() 
{
    clear_screen();
    int game_mode {};
    std::cout << "Welcome to Tetris!" << std::endl;
    std::cout << "Use A to move left, D to move right, W to rotate and S to speed down." << std::endl;
    std::cout << "Enter 1 to play a speed game, or 2 for a marathon version. " << std::endl;
    std::cin >> game_mode;
    while (std::cin.fail() || !is_it_correct<int>(game_mode, 1, 2)) {    
        std::cout << "Invalid input, enter 1 to play a speed game, or 2 for a marathon version. " << std::endl; // Needs to be >= 1
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> game_mode;
    }

    if (game_mode==1) {
        std::unique_ptr<speed::tetris> game(new speed::tetris); // starts a speeed tetris
        game->initialize_game();
    } else if (game_mode==2) {
        std::unique_ptr<marathon::tetris> game(new marathon::tetris); // starts a marathon tetris
        game->initialize_game();
    }

}