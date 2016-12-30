#ifndef TUPLE_6TILE_H
#define TUPLE_6TILE_H
#pragma once
#include "Tuple.h"

class Tuple_6tile : public Tuple
{
public:
	Tuple_6tile();
	~Tuple_6tile();
	void SetParameter(int input_index[6]);
	/*
	get the corresponding data if giving a board
	*/
	virtual float getWeight(int board[16], int stage);
	virtual float getWeight(int board[16], int no, int stage);
	virtual void Update(int board[16], const float error, int stage);
	void test();
private:
	int index[8][6];
};

#endif