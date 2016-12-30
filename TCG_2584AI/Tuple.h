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
#include <vector>
#include <omp.h>
#include <float.h>

using namespace std;
class Tuple
{
public:
	Tuple();
	~Tuple();
	void SetParameter(int input_index[4]);
	/*
	get the corresponding data if giving a board
	*/
	virtual float getWeight(int board[16], int stage) { return 0; };
	virtual float getWeight(int board[16], int no, int stage) { return 0; };
	virtual void setWeight(int board[16], int no, float value) {};
	virtual void Update(int board[16], const float error) {};
	int UpsideDown(const int index);
	int Rotate(const int index);
	void UpdateTable(int pos, const float err, int board[16], int stage);
	float getWeightFromTable(int position, int board[16], int stage);
	int GetMaxTile(int board[16]);
	void Constructor();
	void Desturctor();
	int GetStage(int board[16]);
	void ReadFromWeightTable(const char * filename);
	void WriteToWeightTable(const char * filename);
	void TableReserve(int stage);
	void Tuple::WriteArrayTable(const char * filename);
protected:
	float *Data[STAGENUM];
	int *UseData[STAGENUM];
#ifdef __TCLMODE__
	float *numerator[STAGENUM];
	float *denumorator[STAGENUM];
#endif
protected:
	int iTableSize[STAGENUM];
	float normalization_factor;
	int iTableCapacity[STAGENUM];
	int iCurentTableSize[STAGENUM];
};

#endif