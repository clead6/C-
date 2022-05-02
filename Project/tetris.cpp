#include <iostream>
#include <string>
#include "board.h"
#include "i_piece.h"
#include "tetris.h"

#ifdef _WIN32
#include <windows.h>

#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)

#endif

void tetris::initialize_game()
{
    system("cls");
    board *game_board{};
    game_board = new board(12,12);
    i_piece *p {nullptr};

    while (!game_board->game_over()) {
        p = new i_piece(*game_board);
        p->print_piece(*game_board);
        while(!p->bottom_wall(*game_board) && !game_board->game_over()) { 
            game_board->print_board();        


            if (GetAsyncKeyState(VK_RIGHT)) {					
                p->move_right(*game_board);
            } else if (GetAsyncKeyState(VK_LEFT)) {					
                p->move_left(*game_board);
            } else if (GetAsyncKeyState(VK_UP)) {
                p->rotate(*game_board);
            } else {
                p->move_down(*game_board);
            }
            Sleep(1000);
            
        }
        p->print_piece(*game_board);
        game_board->print_board(); 
        delete p;
    }   
    delete game_board;
}

