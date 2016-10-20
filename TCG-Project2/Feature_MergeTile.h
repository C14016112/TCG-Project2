#ifndef FEATURE_MERGETILE_H
#define FEATURE_MERGETILE_H
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


class Feature_MergeTile
{
public:
	Feature_MergeTile();
	~Feature_MergeTile();
	
	void SetParameter(int inputindex[4]);
	float getWeight(int board[4][4]);
	float getWeight(int board[4][4], int no);
	void setWeight(int board[4][4], int no, float value);
	void ReadFromWeightTable(const char * filename);
	void WriteToWeightTable(const char * filename);
	int UpsideDown(const int index);
	int Rotate(const int index);
	int pow(int x, int y);
private:
	float *Data;
	int index[4][4];
	int iTableSize;
};

#endif