#ifndef __TUPLE_LARGETILECOUNT_H__
#define __TUPLE_LARGETILECOUNT_H__
#include "Tuple.h"
#pragma once
class Tuple_LargeTileCount : public Tuple
{
public:
	Tuple_LargeTileCount(void);
	~Tuple_LargeTileCount(void);
	virtual float getWeight(int board[16], int stage);
	virtual void Update(int board[16], const float error, int stage);
	int getPosition(int board[16]);
	int pow(int x, int y);
private:

};
#endif