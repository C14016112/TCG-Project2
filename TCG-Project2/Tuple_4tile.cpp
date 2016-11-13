#include "Tuple_4tile.h"

Tuple_4tile::Tuple_4tile()
{
}

void Tuple_4tile::SetParameter(int input_index[4])
{
	normalization_factor = (float)std::sqrt(8.);
	iTableSize = iUpperbound*iUpperbound*iUpperbound*iUpperbound;
	Constructor();
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

Tuple_4tile::~Tuple_4tile()
{
	Desturctor();
}

float Tuple_4tile::getWeight(int board[4][4]){

	float value = getWeight(board, 0) + getWeight(board, 1) + getWeight(board, 2)
		+ getWeight(board, 3) + getWeight(board, 4) + getWeight(board, 5) 
		+ getWeight(board, 6) + getWeight(board, 7);
	return value;
}


float Tuple_4tile::getWeight(int board[4][4], int no)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = board[index[no][0] / 4][index[no][0] % 4]
		+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
		+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4];
	return  getWeightFromTable(position, board);
}

void Tuple_4tile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = board[index[no][0] / 4][index[no][0] % 4]
		+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
		+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4];
	setWeightToTable(position, weight, board);
}

void Tuple_4tile::Update(int board[4][4],const float error){
	
	for (int i = 0 ;i<8 ; i++){
		int position = board[ index[i][0] / 4][index[i][0] % 4]
		+ iUpperbound * board[index[i][1] / 4][index[i][1] % 4]
		+ iUpperbound * iUpperbound * board[index[i][2] / 4][index[i][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[i][3] / 4][index[i][3] % 4];
		
		float weight = 1;
		if (board[index[i][0] / 4][index[i][0] % 4] > board[index[i][1] / 4][index[i][1] % 4]) {
			for (int j = 0; j < 3; j++) {
				if (board[index[i][j] / 4][index[i][j] % 4] == board[index[i][j + 1] / 4][board[i][j + 1] % 4] + 2)
					weight *= 1.1;
			}
		}
		else {
			for (int j = 0; j < 3; j++) {
				if (board[index[i][j] / 4][index[i][j] % 4] == board[index[i][j + 1] / 4][board[i][j + 1] % 4] - 2)
					weight *= 1.1;
			}
		}
		weight -= 1;
		UpdateTable(position, error + (float) std::abs(error) * weight, board);
	}
}
