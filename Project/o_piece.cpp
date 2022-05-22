// PHYS 30762 Programming in C++
// Final Project
// Clea Dronne - 29/04/2022

// Initializes O Piece class - derived class of Tetrominos
// 1 rotation state

#include <iostream>
#include <string>
#include "board.h"
#include "o_piece.h"

// Constructor
o_piece::o_piece(board & board) 
{
    piece = new std::string[4];

    for (int i{};i<4;i++){
        piece[i]="#";
    }

    vertical_position = 1; 
    horizontal_position = board.get_length()/2; 

}

// Destructor
o_piece::~o_piece()
{
    std::cout << "delete piece" << std::endl;
    horizontal_position=0;
    vertical_position=0;
    rotation=0;
    delete[] piece;
}

// Prints piece by modifying board
void o_piece::print_piece(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    for (int i{};i<2;i++) {
        for (int j{};j<2;j++) {
            game_console[board.index(horizontal_position+i,vertical_position+j)]=piece[i];
        }
    } 

}

// Piece moves down one line
void o_piece::move_down(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    for (int i{};i<2;i++) {
        for (int j{};j<2;j++) {
            game_console[board.index(horizontal_position+i,vertical_position+j)]=" ";
        }
    } 
    vertical_position+=1;


    for (int i{};i<2;i++) {
        for (int j{};j<2;j++) {
            game_console[board.index(horizontal_position+i,vertical_position+j)]=piece[i];
        }
    } 
}

// Piece moves right one column
void o_piece::move_right(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!right_wall(board)) {

        for (int i{};i<2;i++) {
            for (int j{};j<2;j++) {
                game_console[board.index(horizontal_position+i,vertical_position+j)]=" ";
            }
        } 
        horizontal_position+=1;


        for (int i{};i<2;i++) {
            for (int j{};j<2;j++) {
                game_console[board.index(horizontal_position+i,vertical_position+j)]=piece[i];
            }
        }
    }   
}

// Piece moves left one column
void o_piece::move_left(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!left_wall(board)) {
        for (int i{};i<2;i++) {
            for (int j{};j<2;j++) {
                game_console[board.index(horizontal_position+i,vertical_position+j)]=" ";
            }
        } 
        horizontal_position-=1;


        for (int i{};i<2;i++) {
            for (int j{};j<2;j++) {
                game_console[board.index(horizontal_position+i,vertical_position+j)]=piece[i];
            }
        }
    }        
}

// Piece rotates clockwise
void o_piece::rotate(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};
}

// Piece blocked and can't move down
bool o_piece::bottom_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (vertical_position+1==height) {
        return true;
    } else if (game_console[board.index(horizontal_position,vertical_position+2)] =="#") {
        return true;
    } else if (game_console[board.index(horizontal_position+1,vertical_position+2)] =="#") {
        return true;
    } else {
        return false;
    }
}

// Piece blocked and can't move right
bool o_piece::right_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (horizontal_position+1==length) {
        return true;
    } else if (game_console[board.index(horizontal_position+2,vertical_position)]=="#") {
        return true;
    } else if (game_console[board.index(horizontal_position+2,vertical_position+1)]=="#") {
        return true;
    } else {
        return false;
    }
}

// Piece blocked and can't move left
bool o_piece::left_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (horizontal_position==1) {
        return true; 
    } else if (game_console[board.index(horizontal_position-1,vertical_position)]=="#") {
        return true;
    } else if (game_console[board.index(horizontal_position-1,vertical_position+1)]=="#") {
        return true;
    } else {
        return false;
    }
}