#include "MakeMoveTable.h"

MakeMoveTable::MakeMoveTable()
{
	Move_Table = new int[pow(iUpperbound, 4)*5];
	for (int i = 0 ; i< pow(iUpperbound, 4)*5 ; i++)
		Move_Table[i] = 0;
	// move table for moving to left
	for (int i = 0 ; i< iUpperbound ; i++){
		for (int j = 0 ; j< iUpperbound ; j++){
			for (int k = 0 ; k< iUpperbound ; k++){
				for (int l = 0 ; l < iUpperbound ; l++){
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
						}
						else{
							tail++;
						}
					}
					for (int m = 0 ; m < 5 ; m++){
						Move_Table[5 * i + 5 * j * iUpperbound + 5 * k * pow(iUpperbound, 2) + 5 * l * pow(iUpperbound, 3) + m] = index[m];
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

int MakeMoveTable::MoveLeft(int CurrentBoard[4][4])
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] ={CurrentBoard[i][0], CurrentBoard[i][1], CurrentBoard[i][2], CurrentBoard[i][3] };
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[i][j] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveRight(int CurrentBoard[4][4])
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] ={CurrentBoard[i][3], CurrentBoard[i][2], CurrentBoard[i][1], CurrentBoard[i][0] };
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[i][3-j] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveUp(int CurrentBoard[4][4])
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] ={CurrentBoard[0][i], CurrentBoard[1][i], CurrentBoard[2][i], CurrentBoard[3][i]};
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[j][i] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::MoveDown(int CurrentBoard[4][4])
{
	int award = 0;
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int boardindex[4] ={CurrentBoard[3][i], CurrentBoard[2][i], CurrentBoard[1][i], CurrentBoard[0][i]};
		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard[3-j][i] = newindex[j];
		}
	}
	return award;
}

int MakeMoveTable::Move(int action, int CurrentBoard[4][4]){
#ifdef _DEBUG
	assert(action >= 0 && action < 4);
#endif
	switch (action) {
	case 2:
		return MoveDown(CurrentBoard);
	case 0:
		return MoveUp(CurrentBoard);
	case 1:
		return MoveRight(CurrentBoard);
	case 3:
		return MoveLeft(CurrentBoard);
	default:
		return -1;
	}

}


void MakeMoveTable::GetDataFromMoveTable(const int i, const int j, const int k, const int l, int index[5])
{
	index[0] = Move_Table[ 5 * i + 5 * j * iUpperbound + 5 * k * pow(iUpperbound, 2) + 5 * l *pow(iUpperbound, 3) + 0];
	index[1] = Move_Table[ 5 * i + 5 * j * iUpperbound + 5 * k * pow(iUpperbound, 2) + 5 * l *pow(iUpperbound, 3) + 1];
	index[2] = Move_Table[ 5 * i + 5 * j * iUpperbound + 5 * k * pow(iUpperbound, 2) + 5 * l *pow(iUpperbound, 3) + 2];
	index[3] = Move_Table[ 5 * i + 5 * j * iUpperbound + 5 * k * pow(iUpperbound, 2) + 5 * l *pow(iUpperbound, 3) + 3];
	index[4] = Move_Table[ 5 * i + 5 * j * iUpperbound + 5 * k * pow(iUpperbound, 2) + 5 * l *pow(iUpperbound, 3) + 4];
}
