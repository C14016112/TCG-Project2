#ifndef TUPLE_MERGECOUNT_H
#define TUPLE_MERGECOUNT_H
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


class Tuple_MergeCount
{
public:
	Tuple_MergeCount();
	~Tuple_MergeCount();
	void SetParameter(const int input_index[4]);
	float getWeight(const int board[4][4]);
	float getWeight(const int board[4][4], const int no);
	void setWeight(const int board[4][4], const int no, const float value);
	void Update(const int board[4][4], const float errer);
	int MergeableNumber(const int board[4][4], const int no);
	bool isMergeable(const int x, const int y);
	void ReadFromWeightTable(const char * filename);
	void WriteToWeightTable(const char * filename);
	int UpsideDown(const int index);
	int Rotate(const int index);
private:
	float Data[3];
	float numerator[3];
	float denumorator[3];
	int index[8][4];
	float normalization_factor;
};

#endif