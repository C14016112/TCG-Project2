#ifndef __MAKEMOVETABLE_H__
#define __MAKEMOVETABLE_H__
#pragma once
#include "assert.h"
#include "Fib2584/MoveDirection.h"
#include "stdio.h"
#include "Board.h"
const int fibonacci_seq[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

class MakeMoveTable{
public:
	MakeMoveTable();
	~MakeMoveTable();
	int Move(int, int CurrentBoard[4][4]);
	void GetDataFromMoveTable(const int i, const int j, const int k, const int l, int index[5]);
	
private:
	int MoveLeft(int CurrentBoard[4][4]);
	int MoveUp(int CurrentBoard[4][4]);
	int MoveDown(int CurrentBoard[4][4]);
	int MoveRight(int CurrentBoard[4][4]);
	int *Move_Table;
	int iTableSize;
	
};


#endif