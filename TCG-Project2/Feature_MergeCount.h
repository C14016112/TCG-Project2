#ifndef FEATURE_MERGECOUNT_H
#define FEATURE_MERGECOUNT_H
#pragma once
#include "assert.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "Fib2584/GameBoard.h"
#include "MakeMoveTable.h"
#include "Board.h"
#include "math.h"
#include "string.h"
#include "Feature_TileNumber.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/


class Feature_MergeCount
{
public:
	Feature_MergeCount();
	~Feature_MergeCount();

	float getWeight(int board[4][4]);
	void setWeight(int board[4][4], float value);
	int MergeableNumber(int board[4][4]);
	bool isMergeable(int x, int y);
	void ReadFromWeightTable(const char * filename);
	void WriteToWeightTable(const char * filename);
private:
	float Data[16];
	int iTableSize;
};

#endif