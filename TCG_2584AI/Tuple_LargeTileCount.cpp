#include "Tuple_LargeTileCount.h"


Tuple_LargeTileCount::Tuple_LargeTileCount(void)
{
	normalization_factor = 1;
	for (int i = 0; i < STAGENUM; i++)
		iTableSize[i] = pow(5, iRange);
	Constructor();
}


Tuple_LargeTileCount::~Tuple_LargeTileCount(void)
{
	Desturctor();
}

float Tuple_LargeTileCount::getWeight(int board[16], int stage)
{
	int position = getPosition(board);
	return getWeightFromTable(position, board, stage);
}

int Tuple_LargeTileCount::getPosition(int board[16])
{
	int tile_count[iRange] = {};
	for (int i = 0 ; i < 16; i++){
		if(board[i] >= iLowerBound){
			tile_count[board[i] - iLowerBound]++;
		}
	}
	int position = 0;
	for(int i = 0 ; i< iRange; i++){
		position += pow(5, i) * std::min(tile_count[i],4) ;
	}
	return position;
}

void Tuple_LargeTileCount::Update(int board[16], const float error, int stage)
{
	int position = getPosition(board);
	UpdateTable(position, error, board, stage);
}

int Tuple_LargeTileCount::pow(int x, int y)
{
	int value = 1;
	for (int i = 0; i< y ; i++)
		value *= x;
	return value;
}

