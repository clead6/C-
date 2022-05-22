To paste in terminal to build

g++ main.cpp tetris.cpp board.cpp score.cpp i_piece.cpp l_piece.cpp o_piece.cpp t_piece.cpp j_piece.cpp s_piece.cpp z_piece.cpp -lncurses -o main


On Linux:
install ncurses library
Put in terminal: sudo yum install ncurses-devel

On Windows:
PDcurses in the folder - this library causes a warning

It is recommended to run the game in an external terminal.