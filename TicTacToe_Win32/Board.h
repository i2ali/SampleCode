#pragma once


// represents a move - basically a 3-tuple of player, row, column
class CMove
{
public:
	CMove(int player, int row, int column) : _player(player), _row(row), _column(column) {};

private:
	int _player;
	int _row;
	int _column;

};

/// Board class to represent the names on the board

class CBoard
{
public:
	CBoard(int size, int numplayers);
	virtual ~CBoard(void);

protected:
	virtual bool TakeTurn(int player, int row, int col);
	virtual int CalcWinner(); // brute force
	virtual int CalcWinner(__in CMove* lastmove);

private:
	bool Validate(int player, int row, int col);
	void DumpBoard();
	// internal representation of the board
	int _size;	
	int _numplayers;
	void InitializeBoard();
	bool CheckWinnable();
	int **_board;


};

//TODO::
// Properties in C++??

