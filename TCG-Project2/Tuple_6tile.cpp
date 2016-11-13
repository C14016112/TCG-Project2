#include "Tuple_6tile.h"

Tuple_6tile::Tuple_6tile()
{
}

void Tuple_6tile::SetParameter(int input_index[6])
{
	iTableSize = iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound;
	normalization_factor = std::sqrt(8.);
	Constructor();

	for (int i = 0 ; i<4 ; i++){
		for(int j = 0; j<6; j++){
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

Tuple_6tile::~Tuple_6tile()
{
	Desturctor();
}

float Tuple_6tile::getWeight(int board[4][4])
{
	float value = getWeight(board, 0) + getWeight(board, 1) + getWeight(board, 2)
		+ getWeight(board, 3) + getWeight(board, 4) + getWeight(board, 5) 
		+ getWeight(board, 6) + getWeight(board, 7);
	return value;
}

float Tuple_6tile::getWeight(int board[4][4], int no)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = board[index[no][0] / 4][index[no][0] % 4]
	+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
	+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][4] / 4][index[no][4] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][5] / 4][index[no][5] % 4];
	return getWeightFromTable(position, board);
}

void Tuple_6tile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	
	int position = board[index[no][0] / 4][index[no][0] % 4]
	+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
	+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][4] / 4][index[no][4] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][5] / 4][index[no][5] % 4];
	setWeightToTable(position, weight, board);
}

void Tuple_6tile::Update(int board[4][4], const float error)
{
	for (int no = 0 ; no < 8 ; no++){
		int position = board[index[no][0] / 4][index[no][0] % 4]
		+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
		+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][4] / 4][index[no][4] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][5] / 4][index[no][5] % 4];

		float weight = 1;
		if (board[index[no][0] / 4][index[no][0] % 4] > board[index[no][1] / 4][index[no][1] % 4]) {
			for (int j = 0; j < 5; j++) {
				if (board[index[no][j] / 4][index[no][j] % 4] == board[index[no][j + 1] / 4][board[no][j + 1] % 4] + 2)
					weight *= 1.1;
			}
		}
		else {
			for (int j = 0; j < 5; j++) {
				if (board[index[no][j] / 4][index[no][j] % 4] == board[index[no][j + 1] / 4][board[no][j + 1] % 4] - 2)
					weight *= 1.1;
			}
		}
		weight -= 1;
		UpdateTable(position, error + (float)std::abs(error) * weight, board);
		//UpdateTable(position, error, board);
	}
}
