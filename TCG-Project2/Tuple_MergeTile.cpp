#include "Tuple_MergeTile.h"

Tuple_MergeTile::Tuple_MergeTile()
{
	
}

Tuple_MergeTile::~Tuple_MergeTile()
{
	Desturctor();
}

void Tuple_MergeTile::SetParameter(int inputindex[4])
{
	normalization_factor = std::sqrt(4.);
	for (int i = 0; i < STAGENUM; i++)
		iTableSize[i] = pow(3, iRange);
	Constructor();

	index[0][0] = inputindex[0];
	index[0][1] = inputindex[1];
	index[0][2] = inputindex[2];
	index[0][3] = inputindex[3];
	for (int i = 1 ; i<4 ; i++){
		for(int j = 0; j<4; j++){
			index[i][j] = Rotate(index[i-1][j]);
		}
	}
}

float Tuple_MergeTile::getWeight(int board[4][4], int stage){

	float value = getWeight(board, 0, stage) + getWeight(board, 1, stage) + getWeight(board, 2, stage)
		+ getWeight(board, 3, stage);
	return value;
}


float Tuple_MergeTile::getWeight(int board[4][4], int no, int stage)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 4);
#endif
	int position = GetMergeNumber(board, no);
	return getWeightFromTable(position, board, stage);
}

void Tuple_MergeTile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 4);
#endif
	int stage = GetStage(board);
	int position = GetMergeNumber(board, no);
	setWeightToTable(position, weight, board, stage);
}

void Tuple_MergeTile::Update(int board[4][4], const float error)
{
	int stage = GetStage(board);
	for (int i = 0 ;i<4 ; i++){
		int position = GetMergeNumber(board, i);
		UpdateTable(position, error, board, stage);
	}
}
int Tuple_MergeTile::GetMergeNumber(int board[4][4], int no)
{
	int position = 0;
	int tile_count[iRange] = {};
	for (int i = 0 ; i< 3 ; i++){
		if( board[index[no][i] >> 2][index[no][i] & ( 4 - 1)] == board[index[no][i+1] >> 2][index[no][1+1] & ( 4 - 1)] + 1 || 
			board[index[no][i] >> 2][index[no][i] & ( 4 - 1)] == board[index[no][i+1] >> 2][index[no][i+1] & ( 4 - 1)] - 1)
		{
			if( board[index[no][i] >> 2][index[no][i] & ( 4 - 1)] > iLowerBound)
				tile_count[ board[index[no][i] >> 2][index[no][i] & ( 4 - 1)] - iLowerBound ]++;
			if( board[index[no][i+1] >> 2][index[no][i+1] & ( 4 - 1)] > iLowerBound)
				tile_count[ board[index[no][i+1] >> 2][index[no][i+1] & ( 4 - 1)] - iLowerBound ]++;
		}
	}
	for(int i = 0 ;i<iRange ;i++){
		position += pow(3, i) * tile_count[i];
	}
	return position;
}

int Tuple_MergeTile::pow(int x, int y){
	int value = 1;
	for (int i = 0 ; i<y ; i++)
		value *= x;
	return  value;
}