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
#include <mutex>
#include <omp.h>
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
	virtual float getWeight(int board[4][4], int stage) { return 0; };
	virtual float getWeight(int board[4][4], int no, int stage) { return 0; };
	virtual void setWeight(int board[4][4], int no, float value) {};
	virtual void Update(int board[4][4], const float error) {};
	int UpsideDown(const int index);
	int Rotate(const int index);
	void UpdateTable(int pos, const float err, int board[4][4], int stage);
	float getWeightFromTable(int position, int board[4][4], int stage);
	void setWeightToTable(int position, float value, int board[4][4], int stage);
	int GetMaxTile(int board[4][4]);
	void Constructor();
	void Desturctor();
	int GetStage(int board[4][4]);
	void ReadFromWeightTable(const char * filename);
	void WriteToWeightTable(const char * filename);
#ifdef __VECTORTABLEMODE__
	void ConverTable_VectorToArray(const char * filename);
protected:
	std::vector<float> Data[STAGENUM];
	int **UseData;
#ifdef __TCLMODE__
	std::vector<float> numerator[STAGENUM];
	std::vector<float> denumorator[STAGENUM];
#endif
#endif
#ifdef __ARRAYTABLEMODE__
protected:
	float **Data;
#ifdef __TCLMODE__
	float **numerator;
	float **denumorator;
#endif
	void ConverTable_ArrayToVector(const char * filename);
#endif
protected:
	int iTableSize[STAGENUM];
	float normalization_factor;
	mutex lock_tex;
};

#endif