#ifndef TUPLE_MERGECOUNT_H
#define TUPLE_MERGECOUNT_H
#pragma once
#include "Tuple.h"
class Tuple_MergeCount : public Tuple
{
public:
	Tuple_MergeCount();
	~Tuple_MergeCount();
	void SetParameter(const int input_index[4]);
	virtual float getWeight(int board[4][4], int stage);
	virtual float getWeight(int board[4][4], int no, int stage);
	virtual void setWeight(int board[4][4], int no, float value);
	virtual void Update(int board[4][4], const float error);
	int MergeableNumber(const int board[4][4], const int no);
	bool isMergeable(const int x, const int y);
private:
	int index[8][4];
};

#endif