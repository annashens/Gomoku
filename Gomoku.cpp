#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include <sstream>

using namespace std;

const int HEIGHT = 15;
const int WIDTH = 15;
const int EMPTY = 0, BLACK = 1, WHITE = 2;
const int WIN = 5;

bool isBlack (int numTurn);

void printBoard(int goBoard[HEIGHT][WIDTH]);

void playerMove(int goBoard[HEIGHT][WIDTH], int &player, int &numTurn, 
	int &rowMove, int &colMove);

bool winnerFound(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove);

bool horizontalCheck(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove);
bool verticalCheck(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove);
bool diagonalCheck(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove);

int main()
{
	int goBoard[HEIGHT][WIDTH] = {0};
	
	int numTurn = 1;
	bool isWinner = false;
	int player = BLACK;

	int rowMove = 0, colMove = 0;
	
	//print rules
	cout << "Please enter coordinates in hexadecimal according to the labled axis"
		<< endl << "The first player to get five in a row wins" << endl << endl
		<< "Now the black player will start" << endl;
	cout << "Hit any button to continue" << endl << endl;
	system("PAUSE");
	system ("CLS");
	
	
	//so long as there is no winner 
	while(winnerFound(goBoard, player, rowMove, colMove) == false && numTurn <= 15*15)
	{
		printBoard(goBoard);
		playerMove(goBoard, player, numTurn, rowMove, colMove);
		system ("CLS");
	}
	
	printBoard(goBoard);
	
	if(winnerFound(goBoard, player, rowMove, colMove))
	{
		if(player == BLACK)
		{
			cout << "BLack has won" << endl;
		}
		else if(player == WHITE)
		{
			cout << "White has won" << endl;
		}
	}
	if(numTurn == 15 *15)
	{
		cout << "It is a tie" << endl;
	}
	return 0;
}

void printBoard(int goBoard[HEIGHT][WIDTH])
{
	char coordinate[16] = {'0','1','2','3','4','5','6','7','8','9',
		'A','B','C','D','E','F'};
	cout << endl << " "; 
	for(int col = 0; col < WIDTH; col++)
	{
		cout << "   " << coordinate[col];
	}
	cout << endl;
	for(int row = 0; row < HEIGHT; row++)
	{
		cout << " ";
		for(int col = 0; col < WIDTH; col++)
		{
			cout << "   |";
		}
		cout << endl; 
		cout << coordinate[row];
		for(int col = 0; col < WIDTH; col++)
		{
			cout << "---";
			if(goBoard[row][col] == EMPTY)
				cout << "-";
			else if(goBoard[row][col] == BLACK)
				cout << "B";
			else if(goBoard[row][col] == WHITE)
				cout << "W";
			 goBoard[row][col];
		}
		cout << "---" << endl;
	}
	cout << " ";
	for(int col = 0; col < WIDTH; col++)
	{
		cout << "   |";
	}
	cout << endl;
}

void playerMove(int goBoard[HEIGHT][WIDTH], int &player, int &numTurn, 
	int &rowMove, int &colMove)
{
	cout << "please enter a move" << endl;

	//loop to ensure move is valid
	do{
		//row check
		do{
			cout << "row: ";
			cin >> std::hex >> rowMove;
			if(rowMove > HEIGHT)
				cout << "this move is out of bounds" << endl;;
		}while(rowMove > HEIGHT && rowMove < 0);
		
		//column check
		do{
			cout << "col: ";
			cin >> std::hex >> colMove;
			if(colMove > WIDTH || colMove < 0)
				cout << "this move is out of bounds" << endl;;
		}while(colMove > WIDTH && colMove < 0);	
		
		//location check (ensure is empty)
		if(goBoard[rowMove][colMove] != EMPTY)
			cout << "this space is already taken" << endl;
	} while(goBoard[rowMove][colMove] != EMPTY);

	goBoard[rowMove][colMove] = player;
	
	numTurn++;
	if(isBlack(numTurn))
		player = BLACK;
	else if (!isBlack(numTurn))
		player = WHITE;
}

bool isBlack (int numTurn)
{
	return numTurn%2 != 0;
}

bool winnerFound(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove)
{
	bool horizontalWin = horizontalCheck(goBoard, player, rowMove, colMove);
	bool verticalWin = verticalCheck(goBoard, player, rowMove, colMove);
	bool diagonalWin =  diagonalCheck(goBoard, player, rowMove, colMove);

	return verticalWin || horizontalWin || diagonalWin;
}


bool horizontalCheck(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove)
{
	int count = 1, score = 1; bool won = false;
	
	//right check
	while((colMove + count) < WIDTH && won == false  
		&& goBoard[rowMove][colMove + count] == player)	
	{
		count++;
		score++;
		if(score == WIN)
		{
			won = true;
		}
		//cout << "right score: " << score << endl;
	}
	
	//left check
	count = 1;
	while((colMove - count) >= 0 && won == false  
		&& goBoard[rowMove][colMove - count] == player)	
	{
		count++;
		score++;
		if(score == WIN)
		{
			won = true;
		}
		//cout << "right score: " << score << endl;
	}
	
	return won;
}

bool verticalCheck(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove)
{
	int count = 1, score = 1; bool won = false;
	
	//down check
	while((rowMove + count) < HEIGHT && won == false && goBoard[rowMove + count][colMove] == player)
	{
		count++;
		score++;
		if(score == WIN)
		{
			won = true;
		}
	}
	
	//up check
	count = 1;
	while((rowMove - count) >= 0 && won == false && goBoard[rowMove - count][colMove] == player)
	{
		count++;
		score++;
		if(score == WIN)
		{
			won = true;
		}
	}
	
	return won;
}

bool diagonalCheck(int goBoard[HEIGHT][WIDTH], int player, int rowMove, int colMove)
{
	int count = 1, score = 1; bool won = false;
	//upper left corner
	count = 1;
	while((colMove + count) < WIDTH && (rowMove + count) < HEIGHT
		&& goBoard[rowMove + count][colMove + count] == player)
	{
		count ++;
		score++;
		if(score == WIN)
		{
			return true;
		}
	}
	
	//lower left corner
	count = 1;
	while((colMove - count) >= 0 && (rowMove + count) < HEIGHT
		&& goBoard[rowMove + count][colMove - count] == player)
	{
		count++;
		score++;
		if(score == WIN)
		{
			return true;
		}
	}
	
	//upper left corner
	count = 1;
	while((colMove + count) < WIDTH && (rowMove - count) >= 0 
		&& goBoard[rowMove - count][colMove + count] == player)
	{
		count++;
		score++;
		if(score == WIN)
		{
			return true;
		}
	}
	
	//lower right corner
	count = 1;
	while((colMove - count) >= 0 && (rowMove - count) >= 0 
		&& goBoard[rowMove - count][colMove - count] == player)
	{
		count++;
		score++;
		if(score == WIN)
		{
			return true;
		}
	}
	return false;
}

