// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Initializes J Piece class - derived class of Tetrominos

#include <iostream>
#include <string>
#include "board.h"
#include "j_piece.h"


j_piece::j_piece(board & board) 
{
    piece = new std::string[4];

    for (int i{};i<4;i++){
        piece[i]="#";
    }

    vertical_position = 1; 
    horizontal_position = board.get_length()/2-1; // get length

}

j_piece::~j_piece()
{
    std::cout << "delete piece" << std::endl;
    horizontal_position=0;
    vertical_position=0;
    rotation=0;
    delete[] piece;
}

void j_piece::print_piece(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation)
    {
        case 0: 
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
            } 
            game_console[board.index(horizontal_position+2,vertical_position+1)]=piece[3];
            break;
         
        case 1:  
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+1,vertical_position+i)]=piece[i];
            }  
            game_console[board.index(horizontal_position,vertical_position+2)]=piece[3];
            break;

        case 2:
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+i,vertical_position+1)]=piece[i];
            } 
            game_console[board.index(horizontal_position,vertical_position)]=piece[3];
            break;

        case 3:
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
            }  
            game_console[board.index(horizontal_position+1,vertical_position)]=piece[3];
            break;

    }
}

void j_piece::move_down(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation)
    {
        case 0:
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=" ";
            } 
            game_console[board.index(horizontal_position+2,vertical_position+1)]=" ";
            vertical_position+=1;

            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
            } 
            game_console[board.index(horizontal_position+2,vertical_position+1)]=piece[3];
            break;
        case 1:
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+1,vertical_position+i)]=" ";
            }  
            game_console[board.index(horizontal_position,vertical_position+2)]=" ";

            vertical_position+=1;

            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+1,vertical_position+i)]=piece[i];
            }  
            game_console[board.index(horizontal_position,vertical_position+2)]=piece[3];
            break;  
        case 2:
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+i,vertical_position+1)]=" ";
            }
            game_console[board.index(horizontal_position,vertical_position)]=" ";

            vertical_position+=1;

            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position+i,vertical_position+1)]=piece[i];
            } 
            game_console[board.index(horizontal_position,vertical_position)]=piece[3];

            break;


        case 3:
            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=" ";
            }  
            game_console[board.index(horizontal_position+1,vertical_position)]=" ";

            vertical_position+=1;

            for (int i{};i<3;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
            }  
            game_console[board.index(horizontal_position+1,vertical_position)]=piece[3];

            break;
    }  
}

void j_piece::move_right(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!right_wall(board)) {
        switch (rotation)
        {

            case 0:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position)]=" ";
                } 
                game_console[board.index(horizontal_position+2,vertical_position+1)]=" ";
                horizontal_position+=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
                } 
                game_console[board.index(horizontal_position+2,vertical_position+1)]=piece[3];
                break;
            case 1:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+1,vertical_position+i)]=" ";
                }  
                game_console[board.index(horizontal_position,vertical_position+2)]=" ";

                horizontal_position+=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+1,vertical_position+i)]=piece[i];
                }  
                game_console[board.index(horizontal_position,vertical_position+2)]=piece[3];
                break;  
            case 2:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position+1)]=" ";
                } 
                game_console[board.index(horizontal_position,vertical_position)]=" ";   

                horizontal_position+=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position+1)]=piece[i];
                } 
                game_console[board.index(horizontal_position,vertical_position)]=piece[3];
                break;

            case 3:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=" ";
                }  
                game_console[board.index(horizontal_position+1,vertical_position)]=" ";

                horizontal_position+=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
                }  
                game_console[board.index(horizontal_position+1,vertical_position)]=piece[3];
                break;
        }  
    }   
}

void j_piece::move_left(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!left_wall(board)) {
        switch (rotation)
        {

            case 0:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position)]=" ";
                } 
                game_console[board.index(horizontal_position+2,vertical_position+1)]=" ";
                horizontal_position-=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
                } 
                game_console[board.index(horizontal_position+2,vertical_position+1)]=piece[3];
                break;
            case 1:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+1,vertical_position+i)]=" ";
                }  
                game_console[board.index(horizontal_position,vertical_position+2)]=" ";

                horizontal_position-=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+1,vertical_position+i)]=piece[i];
                }  
                game_console[board.index(horizontal_position,vertical_position+2)]=piece[3];
                break;  
            case 2:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position+1)]=" ";
                } 
                game_console[board.index(horizontal_position,vertical_position)]=" ";   

                horizontal_position-=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position+i,vertical_position+1)]=piece[i];
                } 
                game_console[board.index(horizontal_position,vertical_position)]=piece[3];
                break;

            case 3:
                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=" ";
                }  
                game_console[board.index(horizontal_position+1,vertical_position)]=" ";

                horizontal_position-=1;

                for (int i{};i<3;i++) {
                    game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
                }  
                game_console[board.index(horizontal_position+1,vertical_position)]=piece[3];
                break;
        }  
    }        
}

void j_piece::rotate(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation)
    {
        case 0:
            if (vertical_position>1) { //remove if and test try catch
                try {
                    if (game_console[board.index(horizontal_position+1,vertical_position-1)]==" ") {
                        
                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position+i,vertical_position)]=" ";
                        } 
                        game_console[board.index(horizontal_position+2,vertical_position+1)]=" ";
            
                        vertical_position-=1;
                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position+1,vertical_position+i)]=piece[i];
                        }  
                        game_console[board.index(horizontal_position,vertical_position+2)]=piece[3];
                        rotation=1; 
                    }
                } catch (std::out_of_range& except) {}
            }
            break;

        case 1:
            if (horizontal_position+1<length) {
                try {
                    if (game_console[board.index(horizontal_position+2,vertical_position+1)]==" ") {
            
                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position+1,vertical_position+i)]=" ";
                        }  
                        game_console[board.index(horizontal_position,vertical_position+2)]=" ";

                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position+i,vertical_position+1)]=piece[i];
                        } 
                        game_console[board.index(horizontal_position,vertical_position)]=piece[3];

                        rotation=2;
                    }
                } catch (std::out_of_range& except) {}
            }
            break;

        case 2:
            if (vertical_position+1<height) { 
                try {
                    if (game_console[board.index(horizontal_position+1,vertical_position+2)]==" "
                        && game_console[board.index(horizontal_position+2,vertical_position+2)]==" ") {
                        
                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position+i,vertical_position+1)]=" ";
                        } 
                        game_console[board.index(horizontal_position,vertical_position)]=" ";   

                        horizontal_position+=1;
                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
                        }  
                        game_console[board.index(horizontal_position+1,vertical_position)]=piece[3];

                        rotation=3;
                    }
                } catch (std::out_of_range& except) {}
            }
            break;

        case 3:
            if (horizontal_position>1) {
                try {
                    if (game_console[board.index(horizontal_position-1,vertical_position+1)]==" "
                        && game_console[board.index(horizontal_position-1,vertical_position+2)]==" ") {
            
                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position,vertical_position+i)]=" ";
                        }  
                        game_console[board.index(horizontal_position+1,vertical_position)]=" ";

                        vertical_position+=1;
                        horizontal_position-=1;

                        for (int i{};i<3;i++) {
                            game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
                        } 
                        game_console[board.index(horizontal_position+2,vertical_position+1)]=piece[3];
                        
                        rotation=0;
                    }
                } catch (std::out_of_range& except) {}
            }
            break;

        default:
            break;
    }
}

bool j_piece::bottom_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation) 
    {
        case 0:
            if (vertical_position==height-1) {
                return true;
            } else if (game_console[board.index(horizontal_position,vertical_position+1)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+1)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+2,vertical_position+2)] =="#") {
                return true;
            } else {
                return false;
            }
            break;
    
        case 1:
            if (vertical_position==height-2) {
                return true;
            } else if (game_console[board.index(horizontal_position,vertical_position+3)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+3)] =="#") {
                return true;
            } else {
                return false;
            }
            break;

        case 2:
            if (vertical_position==height-1) {
                return true;
            } else if (game_console[board.index(horizontal_position,vertical_position+2)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+2)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+2,vertical_position+2)] =="#") {
                return true;
            } else {
                return false;
            }
            break;

        case 3:
            if (vertical_position==height-2) {
                return true;
            } else if (game_console[board.index(horizontal_position,vertical_position+3)] =="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+1)] =="#") {
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

bool j_piece::right_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    switch (rotation) 
    {
        case 0:
            if (horizontal_position+2==length) {
                return true;
            } else if (game_console[board.index(horizontal_position+3,vertical_position)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+3,vertical_position+1)]=="#") {
                return true;
            } else {
                return false;
            }
            break;
        case 1: 
            if (horizontal_position+1==length) {
                return true;
            } else if (game_console[board.index(horizontal_position+2,vertical_position)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+2,vertical_position+1)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+2,vertical_position+2)]=="#") {
                return true;
            } else {
                return false;
            }
            break;
        case 2:
            if (horizontal_position+2==length) {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+3,vertical_position+1)]=="#") {
                return true;
            } else {
                return false;
            }
            break;

        case 3: 
            if (horizontal_position+1==length) {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+1)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+1,vertical_position+2)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position+2,vertical_position)]=="#") {
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

bool j_piece::left_wall(board &board)
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
            } else if (game_console[board.index(horizontal_position,vertical_position)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position,vertical_position+1)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position-1,vertical_position+2)]=="#") {
                return true;
            } else {
                return false;
            }
            break;
        case 2: 
            if (horizontal_position==1) {
                return true; 
            } else if (game_console[board.index(horizontal_position-1,vertical_position)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position-1,vertical_position+1)]=="#") {
                return true;
            } else {
                return false;
            }
            break;

        case 3:
            if (horizontal_position==1) {
                return true;
            } else if (game_console[board.index(horizontal_position-1,vertical_position)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position-1,vertical_position+1)]=="#") {
                return true;
            } else if (game_console[board.index(horizontal_position-1,vertical_position+2)]=="#") {
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