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

float Tuple_6tile::getWeight(int board[4][4], int stage)
{
	float value = getWeight(board, 0, stage) + getWeight(board, 1, stage) + getWeight(board, 2, stage)
		+ getWeight(board, 3, stage) + getWeight(board, 4, stage) + getWeight(board, 5, stage)
		+ getWeight(board, 6, stage) + getWeight(board, 7, stage);
	return value;
}

float Tuple_6tile::getWeight(int board[4][4], int no, int stage)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	const int position = board[index[no][0] >> 2][index[no][0] & (4-1) ]
		+ stage_upperbound[stage] * board[index[no][1] >> 2][index[no][1] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][2] >> 2][index[no][2] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][3] >> 2][index[no][3] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][4] >> 2][index[no][4] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][5] >> 2][index[no][5] & (4-1) ];
#ifdef __TRAININGMODE__
#ifdef __PARALLELMODE__
	/*lock_tex.lock();
	lock_tex.unlock();*/
#endif
#endif
	return getWeightFromTable(position, board, stage);
}

void Tuple_6tile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int stage = GetStage(board);
	const int upperbound = stage_upperbound[stage];
	int position = board[index[no][0] >> 2][index[no][0] & (4-1) ]
	+ upperbound * board[index[no][1] >> 2][index[no][1] & (4-1) ]
	+ upperbound * upperbound * board[index[no][2] >> 2][index[no][2] & (4-1) ]
	+ upperbound * upperbound * upperbound * board[index[no][3] >> 2][index[no][3] & (4-1) ]
	+ upperbound * upperbound * upperbound * upperbound * board[index[no][4] >> 2][index[no][4] & (4-1) ]
	+ upperbound * upperbound * upperbound * upperbound * upperbound * board[index[no][5] >> 2][index[no][5] & (4-1) ];
	setWeightToTable(position, weight, board, stage);
}

void Tuple_6tile::Update(int board[4][4], const float error)
{
	int stage = GetStage(board);
	for (int no = 0; no < 8; no++) {
		const int upperbound = stage_upperbound[stage];
		int position = board[index[no][0] >> 2][index[no][0] & (4-1) ]
			+ upperbound * board[index[no][1] >> 2][index[no][1] & (4-1) ]
			+ upperbound * upperbound * board[index[no][2] >> 2][index[no][2] & (4-1) ]
			+ upperbound * upperbound * upperbound * board[index[no][3] >> 2][index[no][3] & (4-1) ]
			+ upperbound * upperbound * upperbound * upperbound * board[index[no][4] >> 2][index[no][4] & (4-1) ]
			+ upperbound * upperbound * upperbound * upperbound * upperbound * board[index[no][5] >> 2][index[no][5] & (4-1) ];
		UpdateTable(position, error, board, stage);
	}
}
