#ifndef __TUPLE_LARGETILECOUNT_H__
#define __TUPLE_LARGETILECOUNT_H__
#include "Fib2584/BitBoard.h"
#include "Mode_Definition.h"
#include"GameBoard_Extend.h"
#include <iostream>
#include <fstream>
#pragma once
class Tuple_LargeTileCount
{
public:
	Tuple_LargeTileCount(void);
	~Tuple_LargeTileCount(void);
	float getWeight(int board[4][4]);
	void setWeight(int board[4][4], const float weight);
	int getPosition(int board[4][4]);
	void Update(int board[4][4], const float error);
	void ReadFromWeightTable(char * filename);
	void WriteToWeightTable(char * filename);
	int pow(int x, int y);
private:
#ifdef __TCLMODE__
	float *numerator;
	float *denumorator;
#endif
	float *Data;
	int iTableSize;
	float normalization_factor;
};
#endif