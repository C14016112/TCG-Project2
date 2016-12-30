#include "Tuple_MergeCount.h"

Tuple_MergeCount::Tuple_MergeCount()
{
	for (int i = 0; i < STAGENUM; i++)
		iTableSize[i] = 3;
	normalization_factor = std::sqrt(8.);
	Constructor();
}

void Tuple_MergeCount::SetParameter(const int input_index[4])
{
	for (int i = 0 ; i<4 ; i++){
		for(int j = 0; j<4; j++){
			if(i == 0){
				index[i][j] = input_index[j];
				index[i+4][j] = UpsideDown(index[i][j]);
			}
			else{
				index[i][j] = Rotate(index[i-1][j]);
				index[i+4][j] = Rotate(index[i+4-1][j]);
			}
		}
	}
}

Tuple_MergeCount::~Tuple_MergeCount()
{
	Desturctor();
}

float Tuple_MergeCount::getWeight(int board[16], int stage)
{
	float value = 0;
	for (int i = 0; i < 8; i++)
		value += getWeight(board, i, stage);
	return  value;
}

float Tuple_MergeCount::getWeight(int board[16], int no, int stage)
{
	int position = MergeableNumber(board, no);
	return getWeightFromTable(position, board, stage);
}

void Tuple_MergeCount::Update(int board[16], float error, int stage)
{
	for (int i = 0 ; i < 8 ; i++){
		int position = MergeableNumber(board, i);
		UpdateTable(position, error, board, stage);
	}
}

int Tuple_MergeCount::MergeableNumber(const int board[16], const int no)
{
	if(isMergeable(board[index[no][1]], board[index[no][2]]) == false ){
		if(isMergeable(board[index[no][0]], board[index[no][1]]) == true ){
			if(isMergeable(board[index[no][2]], board[index[no][3]]) == true )
				return 2;
			else
				return 1;
		}
		else return 0;
	}
	return 1;
}
bool Tuple_MergeCount::isMergeable(const int x, const int y)
{
	if(x - y == 1 || y - x == 1)
		return true;
	if( x == y && x == 1)
		return true;
	return false;
}

