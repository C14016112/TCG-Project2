#ifndef TUPLE_MERGETILE_H
#define TUPLE_MERGETILE_H
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
#include "Tuple_LargeTileCount.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/


class Tuple_MergeTile
{
public:
	Tuple_MergeTile();
	~Tuple_MergeTile();
	
	void SetParameter(int inputindex[4]);
	float getWeight(int board[4][4]);
	float getWeight(int board[4][4], int no);
	void setWeight(int board[4][4], int no, float value);
	void Update(int board[4][4], const float error);
	int GetMergeNumber(int board[4][4], int no);
	void ReadFromWeightTable(const char * filename);
	void WriteToWeightTable(const char * filename);
	int UpsideDown(const int index);
	int Rotate(const int index);
	int pow(int x, int y);
private:
	float *Data;
	float *numerator;
	float *denumorator;
	int index[4][4];
	int iTableSize;
	float normalization_factor;
};

#endif