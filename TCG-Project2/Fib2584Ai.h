#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/GameBoard.h"
#include "MakeMoveTable.h"
#include "Record_Rectangle.h"
#include <iostream>
#include <fstream>
class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);
	void WriteWeightTable();
	void ReadWeightTable();
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
private:
	float Evaluate(int board[4][4]);
	MoveDirection FindBestDirection(int board[4][4]);
	void Learn_Evaluation( int b1_moved[4][4], int b2_moved[4][4], int tmpaward);
	bool isFull(int board[4][4]);
	bool isEmpty(int board[4][4]);
private:
	float LEARNING_RATE;
	Record_Rectangle record;
	int lastboard_moved[4][4];
	MakeMoveTable move;
};

#endif