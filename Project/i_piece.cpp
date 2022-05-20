// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Initializes I Piece class - derived class of Tetrominos

#include <iostream>
#include <string>
#include "board.h"
#include "i_piece.h"

i_piece::i_piece(board & board) 
{
    piece = new std::string[4];

    for (int i{};i<4;i++){
        piece[i]="#";
    }

    vertical_position = 1; 
    horizontal_position = board.get_length()/2-1; // get length

}

i_piece::~i_piece()
{
    std::cout << "delete piece" << std::endl;
    horizontal_position=0;
    vertical_position=0;
    rotation=0;
    delete[] piece;
}

void i_piece::print_piece(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation)
    {
        case 0: 
            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
            } 
            break;
         
        case 1:  
            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
            }  
            break;
    }
}

void i_piece::move_down(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation)
    {
        case 0:
            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=" "; 
            }
            vertical_position+=1;

            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
            }
            break;
        case 1:
            game_console[board.index(horizontal_position,vertical_position)]=" ";   

            vertical_position+=1;

            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
            }   
            break;     
    }  
}

void i_piece::move_right(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!right_wall(board)) {

        switch (rotation)
        {
            case 0:
                game_console[board.index(horizontal_position,vertical_position)]=" ";

                horizontal_position+=1;

                for (int i{};i<4;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
                } 

                break;

            case 1:
                for (int i{};i<4;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=" ";
                }

                horizontal_position+=1;

                for (int i{};i<4;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
                } 

                break;
        }
    }   
}

void i_piece::move_left(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!left_wall(board)) {
        switch(rotation)
        {
            case 0:      
                game_console[board.index(horizontal_position+3,vertical_position)]=" ";

                horizontal_position-=1;

                for (int i{};i<4;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
                } 

                break;

            case 1:
                for (int i{};i<4;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=" ";
                }

                horizontal_position-=1;

                for (int i{};i<4;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
                } 

                break;
        }
    }        
}

void i_piece::rotate(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation)
    {
        case 0:
            if (vertical_position>2 && vertical_position<height-1) {
                try {
                    if (game_console[board.index(horizontal_position+2,vertical_position-1)]==" " 
                        && game_console[board.index(horizontal_position+2,vertical_position+1)]==" "
                        && game_console[board.index(horizontal_position+2,vertical_position+2)]==" ") {
                        
                        for (int i{};i<4;i++) {
                            game_console[board.index(horizontal_position+i,vertical_position)]=" ";
                        }
                        horizontal_position+=2;
                        vertical_position-=1;
                        for (int i{};i<4;i++) {
                            game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
                        }
                        rotation=1; 
                    }
                } catch (std::out_of_range& except) {}
            }
            break;

        case 1:
            if (horizontal_position>2 && horizontal_position<length-2) {
                try {
                    if (game_console[board.index(horizontal_position-2,vertical_position+2)]==" " 
                        && game_console[board.index(horizontal_position-1,vertical_position+2)]==" "
                        && game_console[board.index(horizontal_position+1,vertical_position+2)]==" ") {
            
                        for (int i{};i<4;i++) {
                            game_console[board.index(horizontal_position,vertical_position+i)]=" ";
                        }
                        horizontal_position-=2;
                        vertical_position+=2;
                        for (int i{};i<4;i++) {
                            game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
                        } 

                        rotation=0;
                    }
                } catch (std::out_of_range& except) {}
            }
            break;
    }
}

bool i_piece::bottom_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation) 
    {
        case 0:
            if (vertical_position==height) {
                return true;
            } else if (game_console[board.index(horizontal_position,vertical_position+1)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+1)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+2,vertical_position+1)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+3,vertical_position+1)] =="#") {
                return true;
            } else {
                return false;
            }

            break;
    
        case 1:
            if (vertical_position==height-3) {
                return true;
            } else if (game_console[board.index(horizontal_position,vertical_position+4)] =="#") {
                return true;
            } else {
                return false;
            }
            break;
        
        default:
            return false;
            break;
    }
}

bool i_piece::right_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation) 
    {
        case 0:
            if (horizontal_position+3==length) {
                return true;
            } else if (game_console[board.index(horizontal_position+4,vertical_position)]=="#") {
                return true;
            } else {
                return false;
            }
            break;
        case 1: 
            if (horizontal_position==length) {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+4)]=="#") {
                return true;
            } else {
                return false;
            }
            break;
        default:
            return false;
            break;
    }  
}

bool i_piece::left_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch(rotation)
    {
        case 0: 
            if (horizontal_position==1) {
                return true; 
            } else if (game_console[board.index(horizontal_position-1,vertical_position)]=="#") {
                return true;
            } else {
                return false;
            }
            break;
        case 1:
            if (horizontal_position==1) {
                return true;
            } else if (game_console[board.index(horizontal_position-1,vertical_position+4)]=="#") {
                return true;
            } else {
                return false;
            }
            break;
        default:
            return false;
            break;
    }
}