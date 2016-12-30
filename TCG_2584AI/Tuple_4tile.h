#ifndef TUPLE_4TILE_H
#define TUPLE_4TILE_H
#pragma once
#include "Tuple.h"

class Tuple_4tile : public Tuple
{
public:
	Tuple_4tile();
	~Tuple_4tile();
	void SetParameter(int input_index[4]);
	/*
	get the corresponding data if giving a board
	*/
	virtual float getWeight(int board[16], int stage);
	virtual float getWeight(int board[16], int no, int stage);
	virtual void Update(int board[16],const float error, int stage);
private:
	int index[8][4];
};

#endif