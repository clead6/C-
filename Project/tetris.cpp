// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Implements Tetris class

#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <stdio.h>  

#include "board.h"
#include "i_piece.h"
#include "o_piece.h"
#include "t_piece.h"
#include "l_piece.h"
#include "j_piece.h"
#include "s_piece.h"
#include "z_piece.h"
#include "tetris.h"
#include "score.h"

#ifdef _WIN32
#include <windows.h>
#include "./PDCurses/curses.h"

#else
#include <unistd.h>
#include <cstdlib>
#include <ncurses.h>
#define Sleep(x) usleep((x)*1000)

#endif

// Clears screen by printing empty lines - static function as implemented in different files
static void clear_screen()
{
    std::cout << std::string(30, '\n' );
}

// Lambda function to randomly generate a number between two bounds
auto random_number = [] (auto initial, auto final)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(initial,final); 
    return distribution(rng);
};

// Destructor
marathon::tetris::~tetris()
{
    std::cout << "delete tetris" << std::endl;
}

speed::tetris::~tetris()
{
    std::cout << "delete tetris" << std::endl;
}

// Initializes the marathon game and runs it until game over
void marathon::tetris::initialize_game() 
{
    clear_screen();
    this->game_board=std::make_unique<board>(12,12);
    this->game_score=std::make_unique<score>();

    while (!game_board->game_over()) {

        int generator = random_number(1,7);
        switch(generator)
        {
            case 1:
                this->game_piece=std::make_unique<i_piece>(*game_board);
                break;
            case 2:
                this->game_piece=std::make_unique<t_piece>(*game_board);
                break;
            case 3:
                this->game_piece=std::make_unique<l_piece>(*game_board);
                break;
            case 4:
                this->game_piece=std::make_unique<o_piece>(*game_board);
                break;
            case 5:
                this->game_piece=std::make_unique<j_piece>(*game_board);
                break;     
            case 6:
                this->game_piece=std::make_unique<s_piece>(*game_board);
                break;   
            case 7:
                this->game_piece=std::make_unique<z_piece>(*game_board);
                break;        
        }


        clear_screen();
        game_piece->print_piece(*game_board);

        while(!game_piece->bottom_wall(*game_board)) { 
            initscr();
            game_board->print_board();  
            game_score->print_score(level, score_count);  
            refresh();
            noecho();
            nodelay(stdscr,true);

            int input = getch();
            if (input=='s') {
                endwin();
                game_piece->move_down(*game_board);
                Sleep(50);
            } else if (input=='d') {
                endwin();
                game_piece->move_right(*game_board);
                Sleep(150);
            } else if (input=='a') {
                endwin();
                game_piece->move_left(*game_board);
                Sleep(150);
            } else if (input=='w') {
                endwin();
                game_piece->rotate(*game_board);
                Sleep(150);                
            } else {
                endwin();
                game_piece->move_down(*game_board);
                Sleep(exp(-level/5.0)*1000);
            }

            clear_screen();
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

// Initializes the tetris game and runs until timer is over
void speed::tetris::initialize_game() 
{
    clear_screen();
    clock_t time;
    time = clock();
    this->game_board=std::make_unique<board>(12,12);
    this->game_score=std::make_unique<score>();

    while (!game_board->game_over()) {

        int generator = random_number(1,7);
        switch(generator)
        {
            case 1:
                this->game_piece=std::make_unique<i_piece>(*game_board);
                break;
            case 2:
                this->game_piece=std::make_unique<t_piece>(*game_board);
                break;
            case 3:
                this->game_piece=std::make_unique<l_piece>(*game_board);
                break;
            case 4:
                this->game_piece=std::make_unique<o_piece>(*game_board);
                break;
            case 5:
                this->game_piece=std::make_unique<j_piece>(*game_board);
                break;     
            case 6:
                this->game_piece=std::make_unique<s_piece>(*game_board);
                break;   
            case 7:
                this->game_piece=std::make_unique<z_piece>(*game_board);
                break;        
        }


        clear_screen();
        game_piece->print_piece(*game_board);

        while(!game_piece->bottom_wall(*game_board)) { 


            initscr();
            game_board->print_board();  
            game_score->print_score(level, score_count);  
            refresh();
            noecho();
            nodelay(stdscr,true);

            int input = getch();
            if (input=='s') {
                endwin();
                game_piece->move_down(*game_board);
                Sleep(50);
            } else if (input=='d') {
                endwin();
                game_piece->move_right(*game_board);
                Sleep(150);
            } else if (input=='a') {
                endwin();
                game_piece->move_left(*game_board);
                Sleep(150);
            } else if (input=='w') {
                endwin();
                game_piece->rotate(*game_board);
                Sleep(150);                
            } else {
                endwin();
                game_piece->move_down(*game_board);
                Sleep(exp(-level/5.0)*1000);
            }


            clear_screen();
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

    std::cout << "Time Out" << std::endl;
    game_score->print_score(level, score_count);    
}