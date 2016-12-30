#include "MakeMoveTable.h"

MakeMoveTable::MakeMoveTable()
{
	iTableSize = iupperbound * iupperbound * iupperbound * iupperbound *5;
	Move_Table = new int[iTableSize];
	isMove_Table = new bool[iupperbound * iupperbound * iupperbound * iupperbound];
	for (int i = 0 ; i< iTableSize ; i++)
		Move_Table[i] = 0;
	// move table for moving to left
	for (int i = 0 ; i< iupperbound ; i++){
		for (int j = 0 ; j< iupperbound ; j++){
			for (int k = 0 ; k< iupperbound ; k++){
				for (int l = 0 ; l < iupperbound ; l++){
					int cur_pos = i + j * iupperbound + k * iupperbound * iupperbound + l * iupperbound * iupperbound * iupperbound;
					isMove_Table[cur_pos] = false;
					// the fifth element is award

					int index[5] = {i, j, k, l, 0};

					// pull the element to the left side
					int head = 0; 
					int tail = 0;
					while(tail < 4){
						if(index[tail] != 0){
							int tmp = index[head];
							index[head] = index[tail];
							index[tail] = tmp;
							head++;
							tail++;
							if(head != tail)
								isMove_Table[cur_pos] = true;
						}
						else{
							tail++;
						}
					}

					int check_position = 0;
					while(check_position < 3){
						int next_position = check_position + 1;
						if(index[check_position] != 0 && index[next_position] != 0 
							&& ( abs(index[check_position] - index[next_position]) == 1) || (index[check_position] == 1 && index[check_position+1] == 1)){
								if(index[check_position] == index[next_position] - 1){
									index[check_position] = index[check_position] + 2;
									index[next_position] = 0;
									index[4] = index[4] + fibonacci_seq[index[check_position]]; // award
								}
								else{
									index[check_position] = index[check_position] + 1;
									index[next_position] = 0;
									index[4] = index[4] + fibonacci_seq[index[check_position]];// award
								}
								check_position = check_position + 2;
								isMove_Table[cur_pos] = true;
						}
						else{
							check_position = check_position + 1;
						}
					}

					// pull to left again
					head = 0; 
					tail = 0;
					while(tail < 4){
						if(index[tail] != 0 ){
							int tmp = index[head];
							index[head] = index[tail];
							index[tail] = tmp;
							head++;
							tail++;
							if (head != tail)
								isMove_Table[cur_pos] = true;
						}
						else{
							tail++;
						}
					}
					for (int m = 0 ; m < 5 ; m++){
						Move_Table[5 * i + 5 * j * iupperbound + 5 * k *iupperbound * iupperbound + 5 * l * iupperbound*iupperbound*iupperbound + m] = index[m];
					}
				}
			}
		}
	}
}

MakeMoveTable::~MakeMoveTable()
{
	delete Move_Table;
}

int MakeMoveTable::MoveLeft(int CurrentBoard[16], bool &isMoved)
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] ={CurrentBoard[4*i], CurrentBoard[4*i+1], CurrentBoard[4*i+2], CurrentBoard[4*i+3] };
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex, isMoved);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[4*i+j] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveRight(int CurrentBoard[16], bool &isMoved)
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] = { CurrentBoard[4 * i + 3], CurrentBoard[4 * i + 2], CurrentBoard[4 * i + 1], CurrentBoard[4 * i] };
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex, isMoved);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[4 * i + 3 - j] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveUp(int CurrentBoard[16], bool &isMoved)
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] = { CurrentBoard[i], CurrentBoard[4 + i], CurrentBoard[8 + i], CurrentBoard[12 + i] };
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex, isMoved);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[4 * j + i] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveDown(int CurrentBoard[16], bool & isMoved)
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] = { CurrentBoard[12 + i], CurrentBoard[8 + i], CurrentBoard[4 + i], CurrentBoard[i] };
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex, isMoved);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[4 * ( 3 - j ) + i] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::Move(int action, int CurrentBoard[16], bool &isMoved){
#ifdef _DEBUG
	assert(action >= 0 && action < 4);
#endif
	switch (action) {
	case 2:
		return MoveDown(CurrentBoard, isMoved);
	case 0:
		return MoveUp(CurrentBoard, isMoved);
	case 1:
		return MoveRight(CurrentBoard, isMoved);
	case 3:
		return MoveLeft(CurrentBoard, isMoved);
	default:
		return -1;
	}

}


void MakeMoveTable::GetDataFromMoveTable(const int i, const int j, const int k, const int l, int index[5], bool & isMoved)
{
	index[0] = Move_Table[ 5 * i + 5 * j * iupperbound + 5 * k * iupperbound * iupperbound + 5 * l * iupperbound * iupperbound * iupperbound + 0];
	index[1] = Move_Table[ 5 * i + 5 * j * iupperbound + 5 * k * iupperbound * iupperbound + 5 * l * iupperbound * iupperbound * iupperbound + 1];
	index[2] = Move_Table[ 5 * i + 5 * j * iupperbound + 5 * k * iupperbound * iupperbound + 5 * l * iupperbound * iupperbound * iupperbound + 2];
	index[3] = Move_Table[ 5 * i + 5 * j * iupperbound + 5 * k * iupperbound * iupperbound + 5 * l * iupperbound * iupperbound * iupperbound + 3];
	index[4] = Move_Table[ 5 * i + 5 * j * iupperbound + 5 * k * iupperbound * iupperbound + 5 * l * iupperbound * iupperbound * iupperbound + 4];
	isMoved = isMoved | isMove_Table[i + j * iupperbound + k * iupperbound * iupperbound + l * iupperbound * iupperbound * iupperbound];
}

