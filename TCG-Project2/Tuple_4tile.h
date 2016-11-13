#ifndef TUPLE_4TILE_H
#define TUPLE_4TILE_H
#pragma once
#include "Tuple.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/


class Tuple_4tile : public Tuple
{
public:
	Tuple_4tile();
	~Tuple_4tile();
	void SetParameter(int input_index[4]);
	/*
	get the corresponding data if giving a board
	*/
	virtual float getWeight(int board[4][4]);
	virtual float getWeight(int board[4][4], int no);
	virtual void setWeight(int board[4][4], int no, float value);
	virtual void Update(int board[4][4],const float error);
private:
	int index[8][4];
};

#endif