#ifndef TUPLE_6TILE_H
#define TUPLE_6TILE_H
#pragma once
#include "assert.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "Fib2584/GameBoard.h"
#include "MakeMoveTable.h"
#include "Mode_Definition.h"
#include "math.h"
#include "string.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/


class Tuple_6tile
{
public:
	Tuple_6tile();
	~Tuple_6tile();
	void SetParameter(int input_index[6]);
	/*
	get the corresponding data if giving a board
	*/
	float getWeight(int board[4][4]);
	float getWeight(int board[4][4], int no);
	void setWeight(int board[4][4], int no, float value);
	void Update(int board[4][4], const float error);
	void ReadFromWeightTable(const char *filename);
	void WriteToWeightTable(const char *filename);
	int UpsideDown(const int index);
	int Rotate(const int index);
private:
	float *Data;
	float *numerator;
	float *denumorator;
	int index[8][6];
	int iTableSize;
	float normalization_factor;
};

#endif