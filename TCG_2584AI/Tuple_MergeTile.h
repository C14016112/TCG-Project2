#ifndef TUPLE_MERGETILE_H
#define TUPLE_MERGETILE_H
#pragma once
#include "Tuple.h"
class Tuple_MergeTile : public Tuple
{
public:
	Tuple_MergeTile();
	~Tuple_MergeTile();
	void SetParameter(int inputindex[4]);
	virtual float getWeight(int board[16], int stage);
	virtual float getWeight(int board[16], int no, int stage);
	virtual void Update(int board[16], const float error, int stage);
	int GetMergeNumber(int board[16], int no);
	int pow(int x, int y);
private:
	int index[4][4];
};

#endif