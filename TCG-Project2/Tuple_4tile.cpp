#include "Tuple_4tile.h"

Tuple_4tile::Tuple_4tile()
{
}

void Tuple_4tile::SetParameter(int input_index[4])
{
	normalization_factor = (float)std::sqrt(8.);
	for(int i = 0; i < STAGENUM; i++) {
		iTableSize[i] = stage_upperbound[i]* stage_upperbound[i]* stage_upperbound[i]* stage_upperbound[i];
	}
	

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

float Tuple_4tile::getWeight(int board[4][4], int stage){

	float value = getWeight(board, 0, stage) + getWeight(board, 1, stage) + getWeight(board, 2, stage)
		+ getWeight(board, 3, stage) + getWeight(board, 4, stage) + getWeight(board, 5, stage)
		+ getWeight(board, 6, stage) + getWeight(board, 7, stage);
	return value;
}



float Tuple_4tile::getWeight(int board[4][4], int no, int stage)
{

#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = board[index[no][0] >> 2][index[no][0] & (4-1) ]
		+ stage_upperbound[stage] * board[index[no][1] >> 2][index[no][1] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][2] >> 2][index[no][2] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][3] >> 2][index[no][3] & (4-1) ];
	return  getWeightFromTable(position, board, stage);
}

void Tuple_4tile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int stage = GetStage(board);
	int position = board[index[no][0] >> 2][index[no][0] & (4-1) ]
		+ stage_upperbound[stage] * board[index[no][1] >> 2][index[no][1] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][2] >> 2][index[no][2] & (4-1) ]
		+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[no][3] >> 2][index[no][3] & (4-1) ];
	setWeightToTable(position, weight, board, stage);
}

void Tuple_4tile::Update(int board[4][4],const float error){
	
	int stage = GetStage(board);
	for (int i = 0; i < 8; i++) {
		int position = board[index[i][0] >> 2][index[i][0] & (4-1) ]
			+ stage_upperbound[stage] * board[index[i][1] >> 2][index[i][1] & (4-1) ]
			+ stage_upperbound[stage] * stage_upperbound[stage] * board[index[i][2] >> 2][index[i][2] & (4-1) ]
			+ stage_upperbound[stage] * stage_upperbound[stage] * stage_upperbound[stage] * board[index[i][3] >> 2][index[i][3] & (4-1) ];
		UpdateTable(position, error, board, stage);

	}
}
