#ifndef __TUPLE_LARGETILECOUNT_H__
#define __TUPLE_LARGETILECOUNT_H__
#include "Tuple.h"
#pragma once
class Tuple_LargeTileCount : public Tuple
{
public:
	Tuple_LargeTileCount(void);
	~Tuple_LargeTileCount(void);
	virtual float getWeight(int board[4][4]);
	void setWeight(int board[4][4], float value);
	virtual void Update(int board[4][4], const float error);
	int getPosition(int board[4][4]);
	int pow(int x, int y);
private:

};
#endif