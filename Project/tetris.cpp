#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include <cstdlib>

#include "board.h"
#include "i_piece.h"
#include "o_piece.h"
#include "t_piece.h"
#include "l_piece.h"
#include "tetris.h"
#include "score.h"

#ifdef _WIN32
#include <windows.h>

#else
#include <unistd.h>
#include <cstdlib>
#define Sleep(x) usleep((x)*1000)
#define system("cls") std::system("clear");

#endif

marathon::tetris::~tetris()
{
    std::cout << "delete tetris" << std::endl;
}

speed::tetris::~tetris()
{
    std::cout << "delete tetris" << std::endl;
}

void marathon::tetris::initialize_game()
{
    system("cls");
    this->game_board=std::make_unique<board>(12,12);
    this->game_score=std::make_unique<score>();

    while (!game_board->game_over()) {

        int random_piece = rand() % 4;
        //int random_piece {3};
        switch(random_piece)
        {
            case 0:
                this->game_piece=std::make_unique<o_piece>(*game_board);
                break;
            case 1:
                this->game_piece=std::make_unique<i_piece>(*game_board);
                break;
            case 2:
                this->game_piece=std::make_unique<t_piece>(*game_board);
                break;
            case 3:
                this->game_piece=std::make_unique<l_piece>(*game_board);
                break;

            
        }

        
        system("cls");
        game_piece->print_piece(*game_board);

        while(!game_piece->bottom_wall(*game_board)) { 
            game_board->print_board();  
            game_score->print_score(level, score_count);      
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

        score_count = game_score->points_pieces();

        lines_deleted += game_board->delete_rows();
        if (lines_deleted>0) {
            score_count = game_score->points_lines(level, lines_deleted);
        }

        lines_deleted_count += lines_deleted;
        lines_deleted=0;

        if (lines_deleted_count>=3) {
            level+=1;
            lines_deleted_count-=3;
        }
    }   
    std::cout << "Game Over" << std::endl;
    game_score->print_score(level, score_count);    
}

void speed::tetris::initialize_game()
{
    system("cls");
    time = clock();
    this->game_board=std::make_unique<board>(12,12);
    this->game_score=std::make_unique<score>();

    while (!game_board->game_over()) {
        this->game_piece=std::make_unique<i_piece>(*game_board);
        system("cls");
        game_piece->print_piece(*game_board);

        while(!game_piece->bottom_wall(*game_board) && !game_board->game_over()) { 
            game_board->print_board();  
            game_score->print_score(level, score_count);      

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

        time = clock();
        if ((float)time/CLOCKS_PER_SEC > 60.0) {
            std::cout << "You played a 1 minute game" << std::endl;
            break;
        }

        game_piece->print_piece(*game_board);
        game_board->print_board(); 
        score_count = game_score->points_pieces();

        lines_deleted += game_board->delete_rows();
        if (lines_deleted>0) {
            score_count = game_score->points_lines(level, lines_deleted);
        }

        lines_deleted_count += lines_deleted;
        lines_deleted=0;

        if (lines_deleted_count>=3) {
            level+=1;
            lines_deleted_count-=3;
        }

    }   

    std::cout << "Game Over" << std::endl;
    game_score->print_score(level, score_count);    
}