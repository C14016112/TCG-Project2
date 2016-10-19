#ifndef __GAMEBOARD_EXTEND_H__
#define __GAMEBOARD_EXTEND_H__

#include <iostream>
#include "Fib2584/MoveDirection.h"
#include "Fib2584/MoveTable.h"
#include "Fib2584/BitBoard.h"
#include "Fib2584/Random.h"

using namespace std;

class GameBoard_Extend
{
public:
	static const int fibonacci_[32];
private:
	static Random random_;
public:
	GameBoard_Extend();
	void initialize();
	int move(MoveDirection moveDirection);
	void addRandomTile();
	bool terminated();
	void getArrayBoard(int board[4][4]);
	int getMaxTile();
	void showBoard();
	bool operator==(GameBoard_Extend gameBoard);
	void setBitBoard(const BitBoard bitboard);
	void setBitBoard(int arrayboard[4][4]);
	BitBoard TransformArrayBoardToBitBoard(int arrayboard[4][4]);
	int GetFibOrder(int Fibnumber);
	BitBoard GetBitBoard();
private:
	BitBoard getRow(int row);
	BitBoard getColumn(int column);
	BitBoard restoreRow(BitBoard rowBits, int row);
	BitBoard restoreColumn(BitBoard columnBits, int column);
	int countEmptyTile();
	int getTile(int row, int column);
	int getFibonacci(int index);
private:
	BitBoard board_;
};

#endif