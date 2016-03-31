#include "StdAfx.h"
#include "Board.h"


CBoard::CBoard(int size, int numplayers)
{
	_size = size;
	_numplayers = numplayers;

	// Before creating board, check to see if this game is winnable
	if (FALSE == CheckWinnable())
	{
		// display warning to user	
	}

	_board = new int*[_size];

	for (int i = 0; i < _size; i++)
		_board[i] = new int[_size];

	InitializeBoard();

}


CBoard::~CBoard(void)
{
	//deallocate for 2D array
	for (int i = 0; i < _size; ++i)
	    delete [] _board[i];
	delete [] _board;

}

bool CBoard::CheckWinnable()
{
	return true;

}

void CBoard::DumpBoard()
{
	/*
	for (int i=0; i< _size; i++) 
		for (int j=0; j < _size; j++) 

			//_board[i][j] 		}
	*/
}

void CBoard::InitializeBoard() 
{
	int size = _size;

	//set everything to zero
	for (int i=0; i< size; i++) {
		for (int j=0; j < size; j++) {
			_board[i][j] = 0;			
		}
	}

}


// row: last move made by player
// col: last move made by player

int CBoard::CalcWinner(__in CMove *cmove)
{

	


	return 0;

}

// Brute force method, assuming no knowledge of previous user, returns id of winner
int CBoard::CalcWinner()
{

	int size = _size;
	int player = 0;
	bool winner = true;

	// check rows
	for (int i=0; i < size; ++i ) {
		player = _board[i][0];
		for (int j=1; j < size; ++j) {
			if ((_board[i][j] != player) || (_board[i][j] == -1)) {
				winner = false;
				break;
			}
		}	
		// if we have a winner, return immediately
		if (winner == true)
			return player;
	} // for 

	// check columns
	for (int i=0; i < size; ++i ) {
		player = _board[0][i];
		for (int j=1; j < size; ++j) {
			if ((_board[j][i] != player) || (_board[j][i] == -1)) { 
				winner = false;
				break;
			}
		}	
		// if we have a winner, return immediately
		if (winner == true)
			return player;
	} // for	

	// check diagonals

	// TODO: add error checking for the case where board size is smaller than size 1
	// left diagonal
	player = _board[0][0];
	for (int i=1; i < size; ++i ) {
		if ((_board[i][i] != player) || (_board[i][i] == -1)) {
				winner = false;
				break;
		}	
	} //for	
	
	if (winner == true)
		return player;

	// right diagonal
	player = _board[0][size];
	for (int i=0; i < size; ++i ) {
		if ((_board[i][size - i] != player) || (_board[i][i] == -1)) {
				winner = false;
				break;
		}		
	} // for	
	return 0;
}

bool CBoard::TakeTurn(int player,int row, int col)
{
	if (Validate(player, row, col))
		_board[row][col] = player;
	else 
		return false;

	// More efficient technique
	CMove *cmove = new CMove(player, row, col);
	CalcWinner(cmove);

	// Brute force
	CalcWinner();

	return true;
}

bool CBoard::Validate(int player, int row, int col)
{
	if ((row < 0 || row >= _size) || (col < 0 || col >= _size))
		return false;

	if ( (player < 1) || (player > _numplayers))
		return false;

	return true;
}

