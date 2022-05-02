#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>

#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)

#endif


class board
{
protected:
    int height{0};
    int length{0};
    std::string *console{nullptr};

public:
    board()=default;
    board(int h, int l); // parameterised constructor
    ~board(); // destructor
    int get_length() {return length;}
    int get_height() {return height;}
    std::string *get_console() {return console;}
    void print_board();
    bool game_over();

    int index(int i, int j) const; 
    std::string & operator()(const int i, const int j) const; 
};

board::board(int h, int l) 
{
    height = h;
    length = l;
    console = new std::string[height*length];

    for (size_t i{}; i<(height*length);i++) {
        console[i]=" ";
    }
}

board::~board()
{
    height = 0;
    length = 0;
    delete[] console;
}

void board::print_board() 
{
    std::cout << "|";
    for (int j{0};j<length;j++) {
        std::cout << "-";
    }
    std::cout << "|" << std::endl << "|";

    for (int i{0}; i<(height*length);i++) {
        if (i%length==0 && i!=0) {
            std::cout << "|" << std::endl << "|";
        }
        std::cout << console[i]; // use string streams
    }

    std::cout << "|" << std::endl << "|";
    for (int j{0};j<length;j++) {
        std::cout << "-";
    }
    std::cout << "|" << std::endl;
}

int board::index(int i, int j) const
{
    if(i<=0 || i>length || j<=0 || j>height) {
        std::cout << "Element out of bounds" << std::endl;
        throw;
    }
    return (j-1)*height+(i-1);
}

std::string &board::operator()(const int i, const int j) const
{
    return console[index(i,j)];
}

bool board::game_over() 
{
    for (int i{1};i<=length;i++) {
        if (console[index(i,1)]=="#" && console[index(i,2)]=="#") {

            return true;
        }
    }
    return false;
}

class tetrominos
{
protected:
    std::string *piece {nullptr};
    int horizontal_position {};
    int vertical_position {};
    int rotation {0};
public:
    tetrominos()=default;
    virtual void print_piece(board &board)=0;
    virtual void move_down(board &board)=0;
    virtual void move_right(board &board)=0;
    virtual void move_left(board &board)=0;
    virtual void rotate(board &board)=0;
    virtual bool bottom_wall(board &board)=0;
    virtual bool right_wall(board &board)=0;
    virtual bool left_wall(board &board)=0;

};

class i_piece: public tetrominos
{
public:
    i_piece();
    void print_piece(board &board);
    void move_right(board &board);
    void move_down(board &board);
    void move_left(board &board);
    void rotate(board &board);
    bool bottom_wall(board &board);
    bool right_wall(board &board);
    bool left_wall(board &board);

};

i_piece::i_piece() 
{
    piece = new std::string[4];

    for (int i{};i<4;i++){
        piece[i]="#";
    }

    vertical_position = 1; 
    horizontal_position = 6; // get length

}

void i_piece::print_piece(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (rotation==0) {
        for (int i{};i<4;i++) {
            game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
        } 
    } else { 
        for (int i{};i<4;i++) {
            game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
        }  
    }
}

void i_piece::move_down(board & board) 
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (rotation==0) {
        for (int i{};i<4;i++) {
            game_console[board.index(horizontal_position+i,vertical_position)]=" "; 
        }
        vertical_position+=1;

        for (int i{};i<4;i++) {
            game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
        }
    } else {
        game_console[board.index(horizontal_position,vertical_position)]=" ";   

        vertical_position+=1;

        for (int i{};i<4;i++) {
            game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
        }
    }
    
}

void i_piece::move_right(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!right_wall(board)) {

        if (rotation==0) {

            game_console[board.index(horizontal_position,vertical_position)]=" ";

            horizontal_position+=1;

            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
            } 
        } else  {
            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=" ";
            }

            horizontal_position+=1;

            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
            } 
        }
    }
        
     
}

void i_piece::move_left(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};


    if (!left_wall(board)) {
        if (rotation==0) {
            game_console[board.index(horizontal_position+3,vertical_position)]=" ";

            horizontal_position-=1;

            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position+i,vertical_position)]=piece[i];
            } 
        } else  {
            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=" ";
            }

            horizontal_position-=1;

            for (int i{};i<4;i++) {
                game_console[board.index(horizontal_position,vertical_position+i)]=piece[i];
            } 
        }
    }
        
    
}

void i_piece::rotate(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (rotation==0 && vertical_position>2 && vertical_position<height-1) {
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
        
    } else if (rotation==1 && horizontal_position>2 && horizontal_position<length-2) {
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
    }
}

bool i_piece::bottom_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (rotation==0) {

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
    } else  {
        if (vertical_position==height-3) {
            return true;
        } else if (game_console[board.index(horizontal_position,vertical_position+4)] =="#") {
            return true;
        } else {
            return false;
        }
    }

    
}

bool i_piece::right_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (rotation==0) {
        if (horizontal_position+3==length) {
            return true;
        } else if (game_console[board.index(horizontal_position+4,vertical_position)]=="#") {
            return true;
        } else {
            return false;
        }
    } else {
        if (horizontal_position==length) {
            return true;
        } else if (game_console[board.index(horizontal_position+1,vertical_position+4)]=="#") {
            return true;
        } else {
            return false;
        }
    }
    
}

bool i_piece::left_wall(board &board)
{
    std::string* game_console = board.get_console();
    int height {board.get_height()};
    int length {board.get_length()};

    if (rotation==0) {
        if (horizontal_position==1) {
            return true; 
        } else if (game_console[board.index(horizontal_position-1,vertical_position)]=="#") {
            return true;
        } else {
            return false;
        }
    } else {
        if (horizontal_position==1) {
            return true;
        } else if (game_console[board.index(horizontal_position-1,vertical_position+4)]=="#") {
            return true;
        } else {
            return false;
        }
    }
    
}

class tetris 
{
private:
    board console;
    int score{};

public:
    tetris()=default;
    void initialize_game();
};


void tetris::initialize_game()
{
    board console(12,12);
    i_piece *p {nullptr};
    //bool game_over {false};
    system("cls");

    while (!console.game_over()) {
        p = new i_piece;
        p->print_piece(console);
        while(!p->bottom_wall(console) && !console.game_over()) { 
            console.print_board();        


            if (GetAsyncKeyState(VK_RIGHT)) {					
                p->move_right(console);
            } else if (GetAsyncKeyState(VK_LEFT)) {					
                p->move_left(console);
            } else if (GetAsyncKeyState(VK_UP)) {
                p->rotate(console);
            } else {
                p->move_down(console);
            }
            Sleep(1000);
            
        }
        p->print_piece(console);
    
        console.print_board(); 
        

    }
    console.print_board();     
    p->print_piece(console);

}



int main() 
{

    tetris game;
    game.initialize_game();


}