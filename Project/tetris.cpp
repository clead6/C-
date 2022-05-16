#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include "board.h"
#include "i_piece.h"
#include "tetris.h"
#include "score.h"



#ifdef _WIN32
#include <windows.h>

#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)

#endif

tetris::~tetris()
{
    std::cout << "delete tetris" << std::endl;
}


void tetris::initialize_game()
{
    system("cls");
    this->game_board=std::make_unique<board>(12,14);
    this->game_score=std::make_unique<score>();

    while (!game_board->game_over()) {
        this->game_piece=std::make_unique<i_piece>(*game_board);
        system("cls");
        game_piece->print_piece(*game_board);

        while(!game_piece->bottom_wall(*game_board) && !game_board->game_over()) { 
            game_board->print_board();        

            if (GetAsyncKeyState(VK_DOWN)) {
                game_piece->move_down(*game_board);
                Sleep(50);
            } else if (GetAsyncKeyState(VK_RIGHT)) {					
                game_piece->move_right(*game_board);
                Sleep(150);
            } else if (GetAsyncKeyState(VK_LEFT)) {					
                game_piece->move_left(*game_board);
                Sleep(150);
            } else if (GetAsyncKeyState(VK_UP)) {
                game_piece->rotate(*game_board);
                Sleep(150);
            } else {
                game_piece->move_down(*game_board);
                Sleep(exp(-level/5.0)*1000);
            }            

            system("cls");
            
        }

        game_piece->print_piece(*game_board);
        game_board->print_board(); 

        fallen_pieces+=1;
        score_count = game_score->points_pieces();

        lines_deleted += game_board->delete_rows();
        if (lines_deleted>0) {
            score_count = game_score->points_lines(level, lines_deleted);
        }

        lines_deleted_count += lines_deleted;
        lines_deleted=0;

        if (lines_deleted_count>=5) {
            level+=1;
            lines_deleted_count-=5;
        }

        std::cout << "Level " << level << "\t Score " << score_count << std::endl;

    }   
}

