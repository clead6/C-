#include <iostream>									// For IO.
#include <string>									// For string processing.
#include <Windows.h>								// For console graphics.

using namespace std;

// Board Class

class Board {

	// This is the board class.
	// This manages the board array and allows for easy interaction.


private:
	unsigned int height;								// keeps height of the board.
	unsigned int width;									// keeps width of the board.
	string* board;										// keeps the board array.

public:

	// Making the piece class friend.
	// This allows us to access private variables easily.
	friend class Piece;

	// --- GRAPHICS ---
	// This function uses Windows.h and allows us to
	// print at any specific coordinate of the screen.
	void gotoxy(int x, int y) {

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD scrn;
		scrn.X = x;
		scrn.Y = y;

		SetConsoleCursorPosition(h, scrn);

	}

	// Constructor
	Board() {
	
		height = 20;									// height of board.
		width = 20;										// width of board.

		board = new string[height];						// creating board.

		for (unsigned int i = 0; i < height; i++) {		// initializing values.

			board[i].resize(width);

			board[i][0] = char(178);					// creating border.
			board[i][width - 1] = char(178);			// right & left

			for (unsigned int j = 1; j < width - 1; j++) {

				board[i][j] = ' ';						// creating blank space.

			}

		}


		for (unsigned int i = 0; i < board[0].size(); i++) {		// creating border.

			board[0][i] = char(220);					// top border.
			board[height - 1][i] = char(223);			// bottom border.

		}


	}

	// Board Printing Function
	void printBoard() {

		for (unsigned int i = 0; i < height; i++) {		// looping through
			gotoxy(0, i);
			cout << board[i] << endl;					// the board and printing.
		}

	}

	// Row Cleaning Function
	// After every move, this function is called to remove
	// filled rows.
	// It returns the number of rows that were cleaned for scored addition.
	int cleanRows() {

		int rowsCleaned = 0;
		
		for (int i = 1; i < height - 1; i++) {

			bool isValid = true;

			for (int j = 1; j < width - 1 && isValid; j++) {

				if (board[i][j] != char(177))
					isValid = false;

			}

			if (isValid) {

				for (int j = 1; j < width - 1; j++) {

					board[i][j] = char(249);
					printBoard();
					Sleep(30);

				}

				for (int j = i; j > 1; j--) {
					board[j] = board[j - 1];
				}

				++rowsCleaned;

			}

		}

		return rowsCleaned;

	}

	// Gamer Over Check
	// This function checks if the game has ended.
	// Condition 1: If the top row is filled.
	// Condition 2: If the remaining rows are less than 2.
	bool checkOver() const {

		for (int i = 1; i < width - 1; i++) {
			if (board[1][i] != ' ') return true;
		}

		int emptyRows = 0;
		for (int i = 1; i < height - 1; i++) {
		
			bool filled = false;

			for (int j = 1; j < width - 1 && !filled; j++)
				if (board[i][j] != ' ') filled = true;

			emptyRows += (!filled);

		}

		if (emptyRows < 3) return true;

		return false;

	}

	// Getters & Setters
	string* getBoard() const {
		return board;
	}

	unsigned int getHeight() const {
		return height;
	}

	unsigned int getWidth() const {
		return width;
	}

	// Destructor
	~Board() {

		delete[] board;			// deallocating board
		height = 0;
		width = 0;

	}

};


// Piece Class
class Piece {

	// This is the piece class that acts as an abstract class for
	// inherited pieces.

	// We are using inheritance to create all of the later pieces
	// by using this class.

protected:
	string* piece;										// keeps the actual piece.
	unsigned int xPos;									// x position of piece.
	unsigned int yPos;									// y position of piece.
	int tilt;											// keeps the tilt of the piece.

														// tilt keeps a track of current rotation
														// of the piece.

public:

	// Constructor
	Piece() {

		piece = nullptr;
		xPos = 0;		// original position
		yPos = 0;		// of every piece.
		tilt = 0;

	}


	// Virtual functions
	
	// These functions allow us to use polymorphism.
	// They have been defined in every inherited class later.

	virtual void print(Board& board) = 0;					// print() function takes the board object and puts
															// the piece at specific X and Y.

	virtual void moveDown(Board& board) = 0;				// moveDown() function clears the previous position of
															// the piece and brings the piece one position down.

	virtual bool downBound(const Board& board) const = 0;	// downBound() checks if the piece has reached the down
															// boundary or not. If not, we can keep on moving down.

	virtual bool rightBound(const Board& board) const = 0;	// rightBound() checks if the piece has reached the right
															// boundary or not. If not, we can keep on moving right.

	virtual bool leftBound(const Board& board) const = 0;	// leftBound() checks if the piece has reached the left
															// boundary or not. If not, we can keep on moving left.

	virtual void moveRight(Board& board) = 0;				// It uses the rightBound() function to verify if we can
															// move right. If yes, then it changes the position of the piece.

	virtual void moveLeft(Board& board) = 0;				// It uses the leftBound() function to verify if we can move
															// left. If yes, then it changes the position of the piece.

	virtual void rotate(Board& board) = 0;					// This function handles all of the rotations for the pieces.


	// Destructor
	~Piece() {

		if (piece)
			delete[] piece;

		piece = nullptr;

	}

};


// Stick Piece Implementation
class Stick : public Piece {

public:

	// Check the definition of Piece class to get
	// an idea about function definition and functionality.

	// We do not need a destructor because parent class handles
	// all deallocation.

	// Stick ->

	//	.
	//	.
	//	.
	//	.

	// . . . .

	Stick() {
		
		piece = new string[4];				// allocating mem for piece.
		for (int i = 0; i < 4; i++) {		// creating piece.

			piece[i][0] = char(177);
		
		}

	}

	void print(Board& board) {
		
		string* gameboard = board.getBoard();	// modifying the board.

		if (tilt == 0) {

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + i + 1][xPos + 1] = piece[i][0];	// copying the piece.

			}

		}
		else {

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + 1][xPos + i + 1] = piece[i][0];	// copying the piece.

			}

		}

	}

	void moveDown(Board& board) {
		
		string* gameboard = board.getBoard();


		if (tilt == 0) {
			for (int i = 0; i < 4; i++) {

				gameboard[yPos + i + 1][xPos + 1] = ' ';			// clearing the previous spot.

			}

			++yPos;		// moving the piece down

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + i + 1][xPos + 1] = piece[i][0];	// copying the piece.

			}
		}
		else {

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + 1][xPos + i + 1] = ' ';			// clearing the previous spot.

			}

			++yPos;		// moving the piece down

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + 1][xPos + i + 1] = piece[i][0];	// copying the piece.

			}

		}

	}

	bool downBound(const Board& board) const {

		if (tilt == 0) {


			if (yPos + 6 == board.getHeight()) {

				return true;

			}
			else if (board.getBoard()[yPos + 5][xPos + 1] != ' ') {

				return true;

			}

			return false;

		}
		else {


			if (yPos + 1 == board.getHeight()) {

				return true;

			}
			else {
				
				for (int i = 0; i < 4; i++)
					if (board.getBoard()[yPos + 2][xPos + 1 + i] != ' ') return true;

				return false;

			}

			return false;


		}

	}

	bool rightBound(const Board& board) const {
		

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 4; i++) {

				if (gameboard[yPos + 1 + i][xPos + 2] != ' ') {
					return false;
				}

			}

			return true;

		}
		else {

			if (gameboard[yPos + 1][xPos + 5] != ' ') return false;

			return true;

		}


	}

	bool leftBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 4; i++) {

				if (gameboard[yPos + 1 + i][xPos] != ' ') {
					return false;
				}

			}

			return true;

		}
		else {

			if (gameboard[yPos + 1][xPos] != ' ') return false;

			return true;

		}

	}

	void moveRight(Board& board) {
		
		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + i + 1][xPos + 1] = ' ';			// clearing the previous spot.

			}

			if (xPos + 3 < board.getWidth() && rightBound(board)) {
				++xPos;
			}
			// moving the piece right

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + i + 1][xPos + 1] = piece[i][0];	// copying the piece.

			}
		}
		else {

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + 1][xPos + i + 1] = ' ';			// clearing the previous spot.

			}

			if (xPos + 6 < board.getWidth() && rightBound(board)) {
				++xPos;
			}
			// moving the piece right

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + 1][xPos + i + 1] = piece[i][0];	// copying the piece.

			}

		}

	}

	void moveLeft(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + i + 1][xPos + 1] = ' ';			// clearing the previous spot.

			}

			if (xPos > 0 && leftBound(board)) {
				--xPos;												// moving the piece left.
			}

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + i + 1][xPos + 1] = piece[i][0];	// copying the piece.

			}

		}
		else {

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + 1][xPos + i + 1] = ' ';			// clearing the previous spot.

			}

			if (xPos > 0 && leftBound(board)) {
				--xPos;												// moving the piece left.
			}

			for (int i = 0; i < 4; i++) {

				gameboard[yPos + 1][xPos + i + 1] = piece[i][0];	// copying the piece.

			}

		}

	}

	void rotate(Board& board) {
		
		string* gameboard = board.getBoard();

		if (tilt == 0
			&& gameboard[yPos + 1][xPos + 2] == ' '
			&& gameboard[yPos + 1][xPos + 3] == ' '
			&& gameboard[yPos + 1][xPos + 4] == ' ') {

			for (int i = 1; i < 5; i++) {
				gameboard[yPos + i + 1][xPos + 1] = ' ';
				gameboard[yPos + 1][xPos + i] = piece[i - 1][0];
			}

			tilt = 1;
			
		}
		else if (tilt == 1
			&& gameboard[yPos + 2][xPos + 1] == ' '
			&& gameboard[yPos + 3][xPos + 1] == ' '
			&& gameboard[yPos + 4][xPos + 1] == ' ') {
		
			for (int i = 1; i < 5; i++) {
				gameboard[yPos + 1][xPos + i + 1] = ' ';
				gameboard[yPos + i][xPos + 1] = piece[i - 1][0];
			}

			tilt = 0;
			
		}


	}

};

// Box Piece

class Box : public Piece {

public:

	// Check the definition of Piece class to get
	// an idea about function definition and functionality.

	// We do not need a destructor because parent class handles
	// all deallocation.

	// Box Piece ->

	//	.	.
	//	.	.

	Box() {

		piece = new string[2];
		
		for (int i = 0; i < 2; i++) {
			
			piece[i].resize(2);

			for (int j = 0; j < 2; j++) {
				piece[i][j] = char(177);
			}
		}

	}

	void print(Board& board) {
	
		string* gameboard = board.getBoard();

		for (int i = 0; i < 2; i++) {

			for (int j = 0; j < 2; j++) {

				gameboard[yPos + 1 + i][xPos + 1 + j] = piece[i][j];

			}

		}

	}

	void moveDown(Board& board) {

		string* gameboard = board.getBoard();

		for (int i = 0; i < 2; i++) {

			for (int j = 0; j < 2; j++) {

				gameboard[yPos + 1 + i][xPos + 1 + j] = ' ';

			}

		}

		++yPos;

		for (int i = 0; i < 2; i++) {

			for (int j = 0; j < 2; j++) {

				gameboard[yPos + 1 + i][xPos + 1 + j] = piece[i][j];

			}

		}


	
	}

	bool downBound(const Board& board) const {
	
		if (yPos + 4 == board.getHeight()) {

			return true;

		}
		else {

			for (int i = 0; i < 2; i++) {

				if (board.getBoard()[yPos + 3][xPos + 1 + i] != ' ') {
					return true;
				}

			}

		}

		return false;

	}

	bool rightBound(const Board& board) const {


		string* gameboard = board.getBoard();
		
		for (int i = 0; i < 2; i++) {

			if (gameboard[yPos + 2 + i][xPos + 3] != ' ')
				return false;

		}

		return true;


	}

	bool leftBound(const Board& board) const {

		string* gameboard = board.getBoard();

		for (int i = 0; i < 2; i++) {

			if (gameboard[yPos + i][xPos] != ' ')
				return false;

		}

		return true;

	}

	void moveRight(Board& board) {

		string* gameboard = board.getBoard();

		for (int i = 0; i < 2; i++) {

			for (int j = 0; j < 2; j++) {

				gameboard[yPos + 1 + i][xPos + 1 + j] = ' ';

			}

		}

		if (xPos + 4 < board.getWidth() && rightBound(board)) {
			++xPos;
		}

		for (int i = 0; i < 2; i++) {

			for (int j = 0; j < 2; j++) {

				gameboard[yPos + 1 + i][xPos + 1 + j] = piece[i][j];

			}

		}

	}

	void moveLeft(Board& board) {

		string* gameboard = board.getBoard();

		for (int i = 0; i < 2; i++) {

			for (int j = 0; j < 2; j++) {

				gameboard[yPos + 1 + i][xPos + 1 + j] = ' ';

			}

		}

		if (xPos > 0 && leftBound(board)) {
			--xPos;
		}

		for (int i = 0; i < 2; i++) {

			for (int j = 0; j < 2; j++) {

				gameboard[yPos + 1 + i][xPos + 1 + j] = piece[i][j];

			}

		}
	
	}

	void rotate(Board& board) {

		// When a box is rotated, it doesn't do anything.
	
	}

};


// Pyramid Piece
class Pyramid : public Piece {

public:

	// Check the definition of Piece class to get
	// an idea about function definition and functionality.

	// We do not need a destructor because parent class handles
	// all deallocation.

	// Pyramid Piece

	//	 .
	// . . .

	// .
	// . .
	// .

	// . . .
	//	 .

	//   .
	// . .
	//   .

	Pyramid() {

		piece = new string[2];

		piece[0].append(" ");
		piece[0].push_back(177);
		piece[0].append(" ");

		piece[1].push_back(177);
		piece[1].push_back(177);
		piece[1].push_back(177);


	}

	void print(Board& board) {

		if (tilt == 0) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					board.getBoard()[yPos + 1 + i][xPos + 1 + j] = piece[i][j];
		}
		else if (tilt == 1) {

			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < piece[i].size(); j++) {

					board.getBoard()[yPos + 1 + i][xPos + 1 + j] = piece[i][j];

				}

			}

		}
		else if (tilt == 2) {

			board.getBoard()[yPos + 2][xPos + 2] = piece[1][0];
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = piece[0][j];

		}

	}

	void moveDown(Board& board) {

		if (tilt == 0) {

			board.getBoard()[yPos + 1][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 2][xPos + 1 + j] = ' ';

			++yPos;

			board.getBoard()[yPos + 1][xPos + 2] = char(177);
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 2][xPos + 1 + j] = piece[1][j];

		}
		else if (tilt == 1) {

			string* gameboard = board.getBoard();

			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';

			++yPos;


			gameboard[yPos + 1][xPos + 1] = piece[0][0];

			gameboard[yPos + 2][xPos + 1] = piece[1][0];
			gameboard[yPos + 2][xPos + 2] = piece[1][1];

			gameboard[yPos + 3][xPos + 1] = piece[2][0];



		}
		else if (tilt == 2) {

			board.getBoard()[yPos + 2][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = ' ';

			++yPos;

			board.getBoard()[yPos + 2][xPos + 2] = piece[1][0];
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = piece[0][j];

		}
		else if (tilt == 3) {

			string* gameboard = board.getBoard();

			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';

			++yPos;


			gameboard[yPos + 1][xPos + 2] = piece[0][0];

			gameboard[yPos + 2][xPos + 1] = piece[1][0];
			gameboard[yPos + 2][xPos + 2] = piece[1][1];

			gameboard[yPos + 3][xPos + 2] = piece[2][0];

		}

	}

	bool downBound(const Board& board) const {

		if (tilt == 0) {


			for (int i = 0; i < 3; i++) {

				if (board.getBoard()[yPos + 3][xPos + 1 + i] != ' ') return true;

			}

			return false;


		}
		else if (tilt == 1) {

			if (board.getBoard()[yPos + 3][xPos + 2] != ' ' || board.getBoard()[yPos + 4][xPos + 1] != ' ')
				return true;

			return false;

		}
		else if (tilt == 2) {

			if (board.getBoard()[yPos + 2][xPos + 1] != ' ' || board.getBoard()[yPos + 2][xPos + 3] != ' ' || board.getBoard()[yPos + 3][xPos + 2] != ' ')
				return true;

			return false;

		}
		else if (tilt == 3) {
			
			if (board.getBoard()[yPos + 3][xPos + 1] != ' ' || board.getBoard()[yPos + 4][xPos + 2] != ' ')
				return true;

			return false;

		}
		return false;

	}

	bool rightBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 2][xPos + 4] != ' ') {
			
				return true;

			}

			if (gameboard[yPos + 1][xPos + 4] != ' ' && gameboard[yPos + 2][xPos + 4] != ' ') {
			
				return true;
			
			}

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 2][xPos + 3] != ' ' || gameboard[yPos + 3][xPos + 2] != ' ' || gameboard[yPos + 1][xPos + 2] != ' ')
				return true;

		}
		else if (tilt == 2) {

			if (gameboard[yPos + 1][xPos + 4] != ' ' || gameboard[yPos + 2][xPos + 3] != ' ')
				return true;

		}
		else if (tilt == 3) {

			for (int i = 0; i < 3; i++) {

				if (gameboard[yPos + 1][xPos + 3] != ' ')
					return true;

			}

			return false;

		}

		return false;

	}

	bool leftBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 2][xPos] != ' ') {

				return true;

			}

		}
		else if (tilt == 1) {

			for (int i = 0; i < 3; i++) {

				if (gameboard[yPos + 1][xPos] != ' ')
					return true;

			}

			return false;

		}
		else if (tilt == 2) {

			if (gameboard[yPos + 1][xPos] != ' ' || gameboard[yPos + 2][xPos + 1] != ' ')
				return true;

		}
		else if (tilt == 3) {

			if (gameboard[yPos + 2][xPos] != ' ' || gameboard[yPos + 3][xPos + 1] != ' ' || gameboard[yPos + 1][xPos + 1] != ' ')
				return true;

		}

		return false;

	}

	void moveRight(Board& board) {

		if (rightBound(board)) return;

		if (tilt == 0) {

			board.getBoard()[yPos + 1][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 2][xPos + 1 + j] = ' ';

			if (!rightBound(board))
				++xPos;

			board.getBoard()[yPos + 1][xPos + 2] = char(177);
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 2][xPos + 1 + j] = piece[1][j];

		}
		else if (tilt == 1) {


			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < piece[i].size(); j++) {

					board.getBoard()[yPos + 1 + i][xPos + 1 + j] = ' ';

				}

			}


			++xPos;


			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < piece[i].size(); j++) {

					board.getBoard()[yPos + 1 + i][xPos + 1 + j] = piece[i][j];

				}

			}



		}
		else if (tilt == 2) {

			board.getBoard()[yPos + 2][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = ' ';

			++xPos;

			board.getBoard()[yPos + 2][xPos + 2] = piece[1][0];
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = piece[0][j];

		}
		else if (tilt == 3) {


			string* gameboard = board.getBoard();

			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';

			++xPos;


			gameboard[yPos + 1][xPos + 2] = piece[0][0];

			gameboard[yPos + 2][xPos + 1] = piece[1][0];
			gameboard[yPos + 2][xPos + 2] = piece[1][1];

			gameboard[yPos + 3][xPos + 2] = piece[2][0];


		}

	}

	void moveLeft(Board& board) {

		if (leftBound(board)) return;

		if (tilt == 0) {

			board.getBoard()[yPos + 1][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 2][xPos + 1 + j] = ' ';

			if (!leftBound(board))
				--xPos;

			board.getBoard()[yPos + 1][xPos + 2] = char(177);
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 2][xPos + 1 + j] = piece[1][j];

		}
		else if (tilt == 1) {
		

			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < piece[i].size(); j++) {

					board.getBoard()[yPos + 1 + i][xPos + 1 + j] = ' ';

				}

			}

			--xPos;

			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < piece[i].size(); j++) {

					board.getBoard()[yPos + 1 + i][xPos + 1 + j] = piece[i][j];

				}

			}


		}
		else if (tilt == 2) {

			board.getBoard()[yPos + 2][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = ' ';

			--xPos;

			board.getBoard()[yPos + 2][xPos + 2] = piece[1][0];
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = piece[0][j];

		}
		else if (tilt == 3) {

			string* gameboard = board.getBoard();

			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';

			--xPos;


			gameboard[yPos + 1][xPos + 2] = piece[0][0];

			gameboard[yPos + 2][xPos + 1] = piece[1][0];
			gameboard[yPos + 2][xPos + 2] = piece[1][1];

			gameboard[yPos + 3][xPos + 2] = piece[2][0];

		}

	}

	void rotate(Board& board) {


		if (tilt == 0) {

			if (board.getBoard()[yPos + 3][xPos + 1] != ' ' || board.getBoard()[yPos + 1][xPos + 1] != ' ')
				return;


			board.getBoard()[yPos + 1][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 2][xPos + 1 + j] = ' ';


			tilt = 1;

			delete[] piece;

			piece = new string[3];
			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			piece[1].push_back(char(177));
			
			piece[2].push_back(char(177));

		}
		else if (tilt == 1) {


			// '			// - - -
			// ' -  // --> //    -  
			// '

			if (board.getBoard()[yPos + 1][xPos + 2] != ' ' || board.getBoard()[yPos + 1][xPos + 3] != ' ')
				return;

			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < piece[i].size(); j++) {

					board.getBoard()[yPos + 1 + i][xPos + 1 + j] = ' ';

				}

			}

			tilt = 2;

			delete[] piece;

			piece = new string[2];

			piece[0].push_back(char(177));
			piece[0].push_back(char(177));
			piece[0].push_back(char(177));

			piece[1].push_back(char(177));


		}
		else if (tilt == 2) {

			// - - -			//	 -
			//   -		---->   // - -
								//	 -

			if (board.getBoard()[yPos + 3][xPos + 2] != ' ' || board.getBoard()[yPos + 2][xPos + 1] != ' ')
				return;

			board.getBoard()[yPos + 2][xPos + 2] = ' ';
			for (int j = 0; j < 3; j++)
				board.getBoard()[yPos + 1][xPos + 1 + j] = ' ';


			tilt = 3;

			delete[] piece;

			piece = new string[3];

			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			piece[1].push_back(char(177));

			piece[2].push_back(char(177));

		}
		else if (tilt == 3) {

			//	 -				   //  -
			// - -			--->  // - - -
			//	 -

			string* gameboard = board.getBoard();

			if (gameboard[yPos + 2][xPos + 3] != ' ')
				return;

			tilt = 0;


			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';


			delete[] piece;


			piece = new string[2];

			piece[0].append(" ");
			piece[0].push_back(177);
			piece[0].append(" ");

			piece[1].push_back(177);
			piece[1].push_back(177);
			piece[1].push_back(177);



		}


	}

};


// The L Piece
class L : public Piece {

public:

	// Check the definition of Piece class to get
	// an idea about function definition and functionality.

	// We do not need a destructor because parent class handles
	// all deallocation.

	// L Piece

	// . 
	// .
	// . .

	// . . .
	// .

	// . .
	//   .
	//   .

	//     .
	// . . .

	L() {

		piece = new string[3];

		piece[0].push_back(char(177));
		
		piece[1].push_back(char(177));

		piece[2].push_back(char(177));
		piece[2].push_back(char(177));

	}

	void print(Board& board) {
	
		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 1] = piece[0][0];

			gameboard[yPos + 2][xPos + 1] = piece[1][0];

			gameboard[yPos + 3][xPos + 1] = piece[2][0];
			gameboard[yPos + 3][xPos + 2] = piece[2][1];
		
		}
		else if (tilt == 1) {

			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = piece[0][i];
			gameboard[yPos + 2][xPos + 1] = piece[1][0];

		}
		else if (tilt == 2) {


			for (int i = 0; i < 2; i++)
				gameboard[yPos + 1][xPos + 1 + i] = piece[0][0];

			for (int i = 0; i < 2; i++)
				gameboard[yPos + 2 + i][xPos + 2] = piece[0][0];


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = piece[0][0];

			gameboard[yPos + 1][xPos + 3] = piece[0][0];


		}



	}

	void moveDown(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';
			gameboard[yPos + 3][xPos + 2] = ' ';

		}
		else if (tilt == 1) {

			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
			gameboard[yPos + 2][xPos + 1] = ' ';

		}
		else if (tilt == 2) {


			for (int i = 0; i < 2; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			for (int i = 0; i < 2; i++)
				gameboard[yPos + 2 + i][xPos + 2] = ' ';


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';

			gameboard[yPos + 1][xPos + 3] = ' ';


		}

		++yPos;
		print(board);
	
	}
	
	bool downBound(const Board& board) const {
		
		string* gameboard = board.getBoard();



		if (tilt == 0) {

			for (int i = 0; i < 2; i++) {
				if (gameboard[yPos + 4][xPos + 1 + i] != ' ')
					return true;
			}

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 3][xPos + 1] != ' ' ||
				gameboard[yPos + 2][xPos + 2] != ' ' ||
				gameboard[yPos + 2][xPos + 2] != ' ') {
				return true;
			}

		}
		else if (tilt == 2) {

			if (gameboard[yPos + 4][xPos + 2] != ' ' ||
				gameboard[yPos + 2][xPos + 1] != ' ')
				return true;

		}
		else if (tilt == 3) {

			for (int i = 0; i < 3; i++)
				if (gameboard[yPos + 3][xPos + 1 + i] != ' ')
					return true;

		}

		return false;

	}
	
	bool rightBound(const Board& board) const {
		
		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 1][xPos + 2] != ' ' || gameboard[yPos + 2][xPos + 2] != ' ' || gameboard[yPos + 3][xPos + 3] != ' ')
				return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 1][xPos + 4] != ' ' || gameboard[yPos + 2][xPos + 2] != ' ')
				return true;


		}
		else if (tilt == 2) {

			for (int i = 0; i < 3; i++) {
				if (gameboard[yPos + 1][xPos + 3] != ' ')
					return true;
			}


		}
		else if (tilt == 3) {

			for (int i = 0; i < 2; i++) {
				if (gameboard[yPos + 1 + i][xPos + 4] != ' ')
					return true;
			}

		}

		return false;

	}
	
	bool leftBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 3; i++)
				if (gameboard[yPos + 1 + i][xPos] != ' ')
					return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 1][xPos] != ' ' || gameboard[yPos + 2][xPos] != ' ')
				return true;


		}
		else if (tilt == 2) {


			if (gameboard[yPos + 1][xPos] != ' ')
				return true;

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 2 + i][xPos + 1] != ' ')
					return true;


		}
		else if (tilt == 3) {

			if (gameboard[yPos + 1][xPos + 2] != ' ' ||
				gameboard[yPos + 2][xPos] != ' ')
				return true;

		}

		return false;

	}
	
	void moveRight(Board& board) {

		if (rightBound(board)) return;
	
		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';
			gameboard[yPos + 3][xPos + 2] = ' ';

		}
		else if (tilt == 1) {

			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
			gameboard[yPos + 2][xPos + 1] = ' ';


		}
		else if (tilt == 2) {


			for (int i = 0; i < 2; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			for (int i = 0; i < 2; i++)
				gameboard[yPos + 2 + i][xPos + 2] = ' ';


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';

			gameboard[yPos + 1][xPos + 3] = ' ';


		}

		++xPos;
		print(board);

	}
	
	void moveLeft(Board& board) {
	
		if (leftBound(board)) return;

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';
			gameboard[yPos + 3][xPos + 2] = ' ';

		}
		else if (tilt == 1) {

			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
			gameboard[yPos + 2][xPos + 1] = ' ';

		}
		else if (tilt == 2) {


			for (int i = 0; i < 2; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			for (int i = 0; i < 2; i++)
				gameboard[yPos + 2 + i][xPos + 2] = ' ';


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';

			gameboard[yPos + 1][xPos + 3] = ' ';


		}

		--xPos;
		print(board);

	}
	
	void rotate(Board& board) {


		string* gameboard = board.getBoard();

		if (tilt == 0) {

			// .				// . . .
			// .		-->		// .
			// . .				// 


			if (gameboard[yPos + 1][xPos + 2] != ' ' || gameboard[yPos + 1][xPos + 3] != ' ')
				return;

			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';
			gameboard[yPos + 3][xPos + 2] = ' ';

			tilt = 1;

			delete[] piece;

			piece = new string[2];

			piece[0].push_back(char(177));
			piece[0].push_back(char(177));
			piece[0].push_back(char(177));

			piece[1].push_back(char(177));


		}
		else if (tilt == 1) {


			// . . .			 //  . .
			// .			-->  //	   .
			//					 //    .

			if (gameboard[yPos + 2][xPos + 2] != ' ' ||
				gameboard[yPos + 3][xPos + 2] != ' ')
				return;


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
			gameboard[yPos + 2][xPos + 1] = ' ';

			delete[] piece;

			piece = new string[3];

			piece[0].push_back(char(177));
			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			
			piece[2].push_back(char(177));

			tilt = 2;

		}
		else if (tilt == 2) {

			//  . .				//	   .
			//	  .			--> // . . .
			//    .				//
			
			
			if (gameboard[yPos + 1][xPos + 3] != ' ' ||
				gameboard[yPos + 2][xPos + 3] != ' ' ||
				gameboard[yPos + 2][xPos + 1] != ' ')
				return;


			for (int i = 0; i < 2; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			for (int i = 0; i < 2; i++)
				gameboard[yPos + 2 + i][xPos + 2] = ' ';

			delete[] piece;

			piece = new string[2];

			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			piece[1].push_back(char(177));
			piece[1].push_back(char(177));

			tilt = 3;


		}
		else if (tilt == 3) {

			//	   .			// .
			// . . .    -->		// .
			//					// . .

			if (gameboard[yPos + 1][xPos + 1] != ' ' ||
				gameboard[yPos + 3][xPos + 1] != ' ' ||
				gameboard[yPos + 3][xPos + 2] != ' ')
				return;


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';

			gameboard[yPos + 1][xPos + 3] = ' ';

			delete[] piece;

			piece = new string[3];

			piece[0].push_back(char(177));

			piece[1].push_back(char(177));

			piece[2].push_back(char(177));
			piece[2].push_back(char(177));



			tilt = 0;


		}


	}

};


// The L2 Piece
class L2 : public Piece {

public:

	// Check the definition of Piece class to get
	// an idea about function definition and functionality.

	// We do not need a destructor because parent class handles
	// all deallocation.

	// L2 is just a mirrored copy of L

	L2() {

		piece = new string[3];

		piece[0].push_back(char(177));
		piece[1].push_back(char(177));
		piece[2].push_back(char(177));
		piece[2].push_back(char(177));

	}

	void print(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {


			for (int i = 0; i < 3; i++) {
				gameboard[yPos + 1 + i][xPos + 2] = piece[i][0];
			}
			gameboard[yPos + 3][xPos + 1] = piece[2][1];


		}
		else if (tilt == 1) {


			gameboard[yPos + 1][xPos + 1] = piece[0][0];
			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = piece[1][i];


		}
		else if (tilt == 2) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 1] = piece[i][0];

			gameboard[yPos + 1][xPos + 2] = piece[0][1];


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = piece[0][i];

			gameboard[yPos + 2][xPos + 3] = piece[1][0];


		}

	}

	void moveDown(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';


		}
		else if (tilt == 1) {


			gameboard[yPos + 1][xPos + 1] = ' ';
			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';


		}
		else if (tilt == 2) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 1] = ' ';

			gameboard[yPos + 1][xPos + 2] = ' ';


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			gameboard[yPos + 2][xPos + 3] = ' ';


		}

		++yPos;
		print(board);

	}

	bool downBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 4][xPos + 1 + i] != ' ')
					return true;

		}
		else if (tilt == 1) {

			for (int i = 0; i < 3; i++)
				if (gameboard[yPos + 3][xPos + 1 + i] != ' ')
					return true;

		}
		else if (tilt == 2) {

			if (gameboard[yPos + 2][xPos + 2] != ' ' ||
				gameboard[yPos + 4][xPos + 1] != ' ')
				return true;

		}
		else if (tilt == 3) {

			if (gameboard[yPos + 3][xPos + 3] != ' ' ||
				gameboard[yPos + 2][xPos + 1] != ' ' ||
				gameboard[yPos + 2][xPos + 2] != ' ')
				return true;

		}

		return false;

	}

	bool rightBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 3; i++)
				if (gameboard[yPos + 1 + i][xPos + 3] != ' ')
					return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 1][xPos + 2] != ' ' ||
				gameboard[yPos + 2][xPos + 4] != ' ')
				return true;

		}
		else if (tilt == 2) {

			if (gameboard[yPos + 1][xPos + 3] != ' ')
				return true;

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 2 + i][xPos + 2] != ' ')
					return true;

		}
		else if (tilt == 3) {

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 1 + i][xPos + 4] != ' ')
					return true;


		}

		return false;

	}

	bool leftBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 3][xPos] != ' ' ||
				gameboard[yPos + 2][xPos + 1] != ' ' ||
				gameboard[yPos + 1][xPos + 1] != ' ')
				return true;

		}
		else if (tilt == 1) {


			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 1 + i][xPos] != ' ')
					return true;


		}
		else if (tilt == 2) {

			for (int i = 0; i < 3; i++)
				if (gameboard[yPos + 1 + i][xPos] != ' ')
					return true;


		}
		else if (tilt == 3) {

			if (gameboard[yPos + 1][xPos] != ' ' ||
				gameboard[yPos + 2][xPos + 2] != ' ')
				return true;


		}

		return false;

	}

	void moveRight(Board& board) {

		if (rightBound(board)) return;


		string* gameboard = board.getBoard();

		if (tilt == 0) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';


		}
		else if (tilt == 1) {


			gameboard[yPos + 1][xPos + 1] = ' ';
			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';


		}
		else if (tilt == 2) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 1] = ' ';

			gameboard[yPos + 1][xPos + 2] = ' ';


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			gameboard[yPos + 2][xPos + 3] = ' ';


		}

		++xPos;
		print(board);

	}

	void moveLeft(Board& board) {

		if (leftBound(board)) return;

		string* gameboard = board.getBoard();

		if (tilt == 0) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';


		}
		else if (tilt == 1) {


			gameboard[yPos + 1][xPos + 1] = ' ';
			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';


		}
		else if (tilt == 2) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 1] = ' ';

			gameboard[yPos + 1][xPos + 2] = ' ';


		}
		else if (tilt == 3) {


			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			gameboard[yPos + 2][xPos + 3] = ' ';


		}

		--xPos;
		print(board);

	}

	void rotate(Board& board) {

		string* gameboard = board.getBoard();


		if (tilt == 0) {


			//   .			// .
			//   .		--> // . . .
			// . .			// 

			if (gameboard[yPos + 2][xPos + 3] != ' ' ||
				gameboard[yPos + 1][xPos + 1] != ' ' ||
				gameboard[yPos + 2][xPos + 1] != ' ')
				return;

			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';
			

			delete[] piece;

			piece = new string[2];

			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			piece[1].push_back(char(177));
			piece[1].push_back(char(177));

			tilt = 1;


		}
		else if (tilt == 1) {

			// .				// . .
			// . . .	-->		// .
			//					// .

			if (gameboard[yPos + 3][xPos + 1] != ' ' ||
				gameboard[yPos + 1][xPos + 2] != ' ')
				return;

			gameboard[yPos + 1][xPos + 1] = ' ';
			for (int i = 0; i < 3; i++)
				gameboard[yPos + 2][xPos + 1 + i] = ' ';

			delete[] piece;

			piece = new string[3];

			piece[0].push_back(char(177));
			piece[0].push_back(char(177));

			piece[1].push_back(char(177));

			piece[2].push_back(char(177));

			tilt = 2;

		}
		else if (tilt == 2) {

			// . .			// . . .
			// .		-->	//	   .
			// .			//

			if (gameboard[yPos + 1][xPos + 3] != ' ' ||
				gameboard[yPos + 2][xPos + 3] != ' ')
				return;

			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1 + i][xPos + 1] = ' ';

			gameboard[yPos + 1][xPos + 2] = ' ';


			delete[] piece;

			piece = new string[2];

			piece[0].push_back(char(177));
			piece[0].push_back(char(177));
			piece[0].push_back(char(177));

			piece[1].push_back(char(177));

			tilt = 3;

		}
		else if (tilt == 3) {

			// . . .		//	 .
			//	   .	--> //	 .
			//				// . .

			if (gameboard[yPos + 3][xPos + 3] != ' ' ||
				gameboard[yPos + 3][xPos + 1] != ' ')
				return;

			for (int i = 0; i < 3; i++)
				gameboard[yPos + 1][xPos + 1 + i] = ' ';

			gameboard[yPos + 2][xPos + 3] = ' ';


			delete[] piece;

			piece = new string[3];

			piece[0].push_back(char(177));
			piece[1].push_back(char(177));
			piece[2].push_back(char(177));
			piece[2].push_back(char(177));

			tilt = 0;

		}

	}

};


// S Piece
class S : public Piece {

public:

	// Check the definition of Piece class to get
	// an idea about function definition and functionality.

	// We do not need a destructor because parent class handles
	// all deallocation.

	// S Piece

	// .
	// . .
	//   .

	//    . .
	//  . .

	S() {

		piece = new string[3];
		

		piece[0].push_back(char(177));

		piece[1].push_back(char(177));
		piece[1].push_back(char(177));

		piece[2].push_back(char(177));

	}
	
	void print(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {


			gameboard[yPos + 1][xPos + 1] = piece[0][0];

			gameboard[yPos + 2][xPos + 1] = piece[1][0];
			gameboard[yPos + 2][xPos + 2] = piece[1][1];

			gameboard[yPos + 3][xPos + 2] = piece[2][0];


		}
		else if (tilt == 1) {

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 2 + i] = piece[0][i];
				gameboard[yPos + 2][xPos + 1 + i] = piece[1][i];
			}

		}

	}

	void moveDown(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {


			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';


		}
		else if (tilt == 1) {

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 2 + i] = ' ';
				gameboard[yPos + 2][xPos + 1 + i] = ' ';
			}

		}

		++yPos;
		print(board);

	}

	bool downBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 4][xPos + 2] != ' ' ||
				gameboard[yPos + 3][xPos + 1] != ' ')
				return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 3][xPos + 1] != ' ' ||
				gameboard[yPos + 3][xPos + 2] != ' ' ||
				gameboard[yPos + 2][xPos + 3] != ' ')
				return true;

		}

		return false;
	}

	bool rightBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 1][xPos + 2] != ' ')
				return true;

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 2 + i][xPos + 3] != ' ')
					return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 1][xPos + 4] != ' ' ||
				gameboard[yPos + 2][xPos + 3] != ' ')
				return true;

		}

		return false;
	}

	bool leftBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 1 + i][xPos] != ' ')
					return true;

			if (gameboard[yPos + 3][xPos + 1] != ' ')
				return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 1][xPos + 1] != ' ' ||
				gameboard[yPos + 2][xPos] != ' ')
				return true;

		}

		return false;
	}

	void moveRight(Board& board) {

		if (rightBound(board)) return;
		
		string* gameboard = board.getBoard();

		if (tilt == 0) {


			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';


		}
		else if (tilt == 1) {

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 2 + i] = ' ';
				gameboard[yPos + 2][xPos + 1 + i] = ' ';
			}

		}

		++xPos;
		print(board);

	}

	void moveLeft(Board& board) {

		if (leftBound(board)) return;

		string* gameboard = board.getBoard();

		if (tilt == 0) {


			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';


		}
		else if (tilt == 1) {

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 2 + i] = ' ';
				gameboard[yPos + 2][xPos + 1 + i] = ' ';
			}

		}

		--xPos;
		print(board);

	}

	void rotate(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			// .		//	 . .
			// . .	--> // . .
			//	 .		// 

			if (gameboard[yPos + 1][xPos + 2] != ' ' ||
				gameboard[yPos + 1][xPos + 3] != ' ')
				return;

			gameboard[yPos + 1][xPos + 1] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 2] = ' ';

			delete[] piece;

			piece = new string[2];

			piece[0].push_back(char(177));
			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			piece[1].push_back(char(177));

			tilt = 1;
			

		}
		else if (tilt == 1) {

			// .		//	 . .
			// . .	--> // . .
			//	 .		// 

			if (gameboard[yPos + 1][xPos + 1] != ' ' ||
				gameboard[yPos + 3][xPos + 2] != ' ')
				return;
			
			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 2 + i] = ' ';
				gameboard[yPos + 2][xPos + 1 + i] = ' ';
			}

			delete[] piece;

			piece = new string[3];


			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			piece[1].push_back(char(177));

			piece[2].push_back(char(177));

			tilt = 0;


		}

	}

};


// S2 Piece

class S2 : public Piece {

public:

	// Check the definition of Piece class to get
	// an idea about function definition and functionality.

	// We do not need a destructor because parent class handles
	// all deallocation.

	// S2 is just a mirrored copy of S piece.

	S2() {

		piece = new string[3];

		piece[0].push_back(char(177));

		piece[1].push_back(char(177));
		piece[1].push_back(char(177));

		piece[2].push_back(char(177));

	}

	void print(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 2] = piece[0][0];

			gameboard[yPos + 2][xPos + 1] = piece[1][0];
			gameboard[yPos + 2][xPos + 2] = piece[1][1];

			gameboard[yPos + 3][xPos + 1] = piece[0][0];


		}
		else if (tilt == 1) {


			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 1 + i] = char(177);
				gameboard[yPos + 2][xPos + 2 + i] = char(177);
			}


		}

	}

	void moveDown(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';

		}
		else if (tilt == 1) {

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
				gameboard[yPos + 2][xPos + 2 + i] = ' ';
			}

		}

		++yPos;
		print(board);

	}

	bool downBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 4][xPos + 1] != ' ' ||
				gameboard[yPos + 3][xPos + 2] != ' ')
				return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 3][xPos + 2] != ' ' ||
				gameboard[yPos + 3][xPos + 3] != ' ' ||
				gameboard[yPos + 2][xPos + 1] != ' ')
				return true;

		}

		return false;

	}

	bool rightBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			if (gameboard[yPos + 3][xPos + 3] != ' ')
				return true;

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 1 + i][xPos + 3] != ' ')
					return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 1][xPos + 3] != ' ' ||
				gameboard[yPos + 2][xPos + 4] != ' ')
				return true;

		}

		return false;

	}

	bool leftBound(const Board& board) const {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			for (int i = 0; i < 2; i++)
				if (gameboard[yPos + 2 + i][xPos] != ' ')
					return true;

			if (gameboard[yPos + 1][xPos] != ' ')
				return true;

		}
		else if (tilt == 1) {

			if (gameboard[yPos + 1][xPos] != ' ' ||
				gameboard[yPos + 2][xPos + 1] != ' ')
				return true;

		}

		return false;

	}

	void moveRight(Board& board) {

		if (rightBound(board)) return;

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';

		}
		else if (tilt == 1) {

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
				gameboard[yPos + 2][xPos + 2 + i] = ' ';
			}

		}

		++xPos;
		print(board);

	}

	void moveLeft(Board& board) {

		if (leftBound(board)) return;

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';

		}
		else if (tilt == 1) {

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
				gameboard[yPos + 2][xPos + 2 + i] = ' ';
			}

		}

		--xPos;
		print(board);

	}

	void rotate(Board& board) {

		string* gameboard = board.getBoard();

		if (tilt == 0) {

			//   .				// . .
			// . .		-->		//   . .
			// .				// 

			if (gameboard[yPos + 1][xPos + 1] != ' ' ||
				gameboard[yPos + 2][xPos + 3] != ' ')
				return;

			gameboard[yPos + 1][xPos + 2] = ' ';

			gameboard[yPos + 2][xPos + 1] = ' ';
			gameboard[yPos + 2][xPos + 2] = ' ';

			gameboard[yPos + 3][xPos + 1] = ' ';

			delete[] piece;

			piece = new string[2];

			piece[0].push_back(char(177));
			piece[0].push_back(char(177));

			piece[1] = piece[0];

			tilt = 1;

		}
		else if (tilt == 1) {

			//   .				// . .
			// . .		-->		//   . .
			// .				// 

			if (gameboard[yPos + 3][xPos + 1] != ' ')
				return;

			for (int i = 0; i < 2; i++) {
				gameboard[yPos + 1][xPos + 1 + i] = ' ';
				gameboard[yPos + 2][xPos + 2 + i] = ' ';
			}

			delete[] piece;

			piece = new string[3];

			piece[0].push_back(char(177));

			piece[1].push_back(char(177));
			piece[1].push_back(char(177));

			piece[2].push_back(char(177));


			tilt = 0;
		}

	}

};

// Main Tetris Class
class Tetris {

private:
	Board board;							// this keeps the main board object.
	unsigned int score;						// this holds the current score.
	unsigned int speed;						// this keeps the speed depending on what mode we choose.
	
public:

	// Default Constructor
	Tetris() {

		score = 0;
		
	}


	// Game Loop Function
	void init() {

		showMenu();							// taking the level from user.

		Piece* p = nullptr;					// this is the polymorphic pointer that keeps the piece.
		bool isGameOver = false;			// this keeps a track if the game is over or not.

		while (true && !isGameOver) {		// run until inifity or until the game is over.

			srand(time(NULL));
			int randomPiece = rand() % 7;	// generate a random piece.



											// this is where a polymorphic object is generated.
			if (randomPiece == 0) {
				p = new Stick;
			}
			else if (randomPiece == 1) {
				p = new Box;
			}
			else if (randomPiece == 2) {
				p = new Pyramid;
			}
			else if (randomPiece == 3) {
				p = new L;
			}
			else if (randomPiece == 4) {
				p = new L2;
			}
			else if (randomPiece == 5) {
				p = new S;
			}
			else if (randomPiece == 6) {
				p = new S2;
			}

			int rowsTravelled = 0;

			while (!p->downBound(board) && !isGameOver) {

				p->print(board);									// printing the piece on board (polymorphically)
				board.printBoard();									// printing the board.


				if (GetAsyncKeyState(VK_RIGHT) & 0x27000) {			// checking if right key has been pressed.
					
					p->moveRight(board);							// moving right (polymorphically)

				}
				else if (GetAsyncKeyState(VK_LEFT) & 0x25000) {		// checking if the left key has been pressed.

					p->moveLeft(board);								// moving left (polymorphically)

				}
				else if (GetAsyncKeyState(VK_UP) & 0x26000) {		// checking if up key has been pressed.

					p->rotate(board);								// rotating piece (polymorphically)

				}
				else {

					p->moveDown(board);								// moving the piece down (polymorphically)

				}

				Sleep(speed);										// delay function

			}

			board.printBoard();
			score += (100 * board.cleanRows());						// if any rows are cleaning, we add 100 * rows to the score.
			score += 25;											// 25 pts per piece.

			isGameOver = board.checkOver();							// checking if the game is over.

			board.gotoxy(37, 4);
			cout << "SCORE: " << score << endl;

			delete p;												// deleting the polymorphic object.

		}

		board.gotoxy(37, 5);
		cout << "GAME OVER!!" << endl;
		cin.get();
		cin.get();

	}


	// This function handles the menu printing
	void showMenu() {
		
		cout << "+ ------------------------------------------------  +" << endl;
		cout << "+                                                   +" << endl;
		cout << "+       1. Beginner                                 +" << endl;
		cout << "+       2. Medium                                   +" << endl;
		cout << "+       3. Hard                                     +" << endl;
		cout << "+                                                   +" << endl;
		cout << "+ ------------------------------------------------  +" << endl;

		int choice = 1;

		cout << ">> ";
		cin >> choice;

		if (choice == 1)
			speed = 150;	// beginner
		else if (choice == 2)
			speed = 100;	// medium
		else if (choice == 3)
			speed = 50;		// hard
		else
			speed = 150;	// default

		system("cls");		// clearing screen.


		
		board.gotoxy(30, 1);	// tetris logo
		cout << char(176)
			<< char(176)
			<< char(177)
			<< char(178)
			<< "  "
			<< "T E T R I S"
			<< " "
			<< char(178)
			<< char(177)
			<< char(176)
			<< char(176)
			<< endl;

		


	}


	~Tetris() {
	
		// Not needed.

	}

};

int main() {

	Tetris game;		// game object
	game.init();		// initializer function


	return 0;
}