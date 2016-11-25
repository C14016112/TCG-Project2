#ifndef __TUPLE_H__
#define __TUPLE_H__
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
#include <algorithm>
/*
Class that save the data of strategy, only deal with four tiles one time

*/


class Tuple
{
public:
	Tuple();
	~Tuple();
	void SetParameter(int input_index[4]);
	/*
	get the corresponding data if giving a board
	*/
	virtual float getWeight(int board[4][4]) { return 0; };
	virtual float getWeight(int board[4][4], int no) { return 0; };
	virtual void setWeight(int board[4][4], int no, float value) {};
	virtual void Update(int board[4][4], const float error) {};
	void ReadFromWeightTable(const char * filename);
	void WriteToWeightTable(const char * filename);
	int UpsideDown(const int index);
	int Rotate(const int index);
	void UpdateTable(int pos, const float err, int board[4][4], int stage);
	float getWeightFromTable(int position, int board[4][4], int stage);
	void setWeightToTable(int position, float value, int board[4][4], int stage);
	int GetMaxTile(int board[4][4]);
	void Constructor();
	void Desturctor();
	int GetStage(int board[4][4]);
protected:
	float **Data;
#ifdef __TCLMODE__
	float **numerator;
	float **denumorator;
#endif
	int iTableSize[STAGENUM];
	float normalization_factor;
};

#endif