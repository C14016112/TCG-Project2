#include "Tuple_6tile.h"

Tuple_6tile::Tuple_6tile()
{
}

void Tuple_6tile::SetParameter(int input_index[6])
{
	for (int stage = 0; stage < STAGENUM; stage++)
		iTableSize[stage] = stage_upperbound[stage]*stage_upperbound[stage]*stage_upperbound[stage]*stage_upperbound[stage]*stage_upperbound[stage]*stage_upperbound[stage];
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

float Tuple_6tile::getWeight(int board[16], int stage)
{
	float value = getWeight(board, 0, stage) + getWeight(board, 1, stage) + getWeight(board, 2, stage)
		+ getWeight(board, 3, stage) + getWeight(board, 4, stage) + getWeight(board, 5, stage)
		+ getWeight(board, 6, stage) + getWeight(board, 7, stage);
	return value;
}

float Tuple_6tile::getWeight(int board[16], int no, int stage)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	const int position = board[index[no][0]]
		+ stage_upperbound[stage] * board[index[no][1]]
		+ stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][2]]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][3]]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][4]]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][5]];
	return getWeightFromTable(position, board, stage);
}

void Tuple_6tile::Update(int board[16], const float error, int stage)
{
	for (int no = 0; no < 8; no++) {
		const int position = board[index[no][0]]
			+ stage_upperbound[stage] * board[index[no][1]]
			+ stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][2]]
			+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][3]]
			+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][4]]
			+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][5]];
		UpdateTable(position, error, board, stage);
	}
}

void Tuple_6tile::test()
{
	/*for (int j = 0; j < STAGENUM; j++) {
		for (int i = 0; i < iTableSize[j]; i++) {
			if (UseData[j][i] != -1)
				if (Data[j][UseData[j][i]] == 0)
					cout << UseData[j][i] << endl;
		}
	}*/
	
}