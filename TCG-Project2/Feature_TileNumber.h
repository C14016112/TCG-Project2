#ifndef __FEATURE_TILENUMBER_H__
#define __FEATURE_TILENUMBER_J__
#include "Fib2584/BitBoard.h"
#include "Board.h"
#include"GameBoard_Extend.h"
#include <iostream>
#include <fstream>
#define iRange (iUpperbound - iLowerBound)
#pragma once
class Feature_TileNumber
{
public:
	Feature_TileNumber(void);
	~Feature_TileNumber(void);
	float getWeight(int board[4][4]);
	void setWeight(int board[4][4], const float weight);
	void Update(int board[4][4], const float error);
	void ReadFromWeightTable(char * filename);
	void WriteToWeightTable(char * filename);
	int pow(int x, int y);
private:
	float *numerator;
	float *denumorator;
	float *Data;
	int iTableSize;
};
#endif