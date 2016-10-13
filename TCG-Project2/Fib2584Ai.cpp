#include "Fib2584Ai.h"


Fib2584Ai::Fib2584Ai()
{
	LEARNING_RATE = 0.0025*3;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			lastboard_moved[i][j] = 0;
		}
	}
	move.MakeTable();
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	for (int i = 0 ;i<4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			for (int k = 0 ; k<32 ; k++){
				if(board[i][j] == GameBoard::fibonacci_[k]){
					board[i][j] = k;
				}
			}
		}
	}

	MoveDirection currentaction = FindBestDirection(board);
	int tmpaward;
	move.Move((int)currentaction, board, tmpaward);
	if(isEmpty(lastboard_moved) == false){
		Learn_Evaluation(lastboard_moved, board, tmpaward);
	}

	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			lastboard_moved[i][j] = board[i][j];
		}
	}
	
	return currentaction;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			lastboard_moved[i][j] = 0;
		}
	}
}

float Fib2584Ai::Evaluate(int board[4][4])
{
	return record.getScore(board);

}


void Fib2584Ai::Learn_Evaluation( int b1_moved[4][4], int b2_moved[4][4], int tmpaward)
{

	float next_value = 0;
	float now_value = 0;
	float delta = 0;
	now_value = record.getScore(b1_moved);
	if (isFull(b2_moved) == true){
		delta = LEARNING_RATE * now_value * -1;
	}
	else{
		next_value = record.getScore(b2_moved);
		delta = LEARNING_RATE * ((float)tmpaward + next_value - now_value);
	}
		
	for (int i = 0; i < 8; i++){
		float new_value1 = record.get_OneFeature_Score(1, b1_moved, i) + delta ;
		record.set_OneFeature_Score(1, b1_moved, i, new_value1);

		float new_value2 = record.get_OneFeature_Score(2, b1_moved, i) + delta;
		record.set_OneFeature_Score(2, b1_moved, i, new_value2);

		float new_value3 = record.get_OneFeature_Score(3, b1_moved, i) + delta;
		record.set_OneFeature_Score(3, b1_moved, i, new_value3);
	}
}

MoveDirection Fib2584Ai::FindBestDirection(int board[4][4])
{
	int nextaction = 0;
	float score[4] = {};
	int tmpboard[4][4][4] = {};

	for (int i = 0 ; i<4 ; i++){
		int moveboard[4][4] = {};
		for (int j = 0 ; j<4 ; j++){
			for (int k = 0 ;k<4 ;k++){
				moveboard[j][k] = board[j][k];
			}
		}

		int tmpaward = 0;
		move.Move(i, moveboard, tmpaward);
		score[i] = Evaluate(moveboard) + tmpaward;
		
		if(score[i] > score[nextaction]){
			nextaction = i;
		}
		for (int j = 0 ; j<4 ; j++){
			for (int k = 0 ;k<4 ;k++){
				tmpboard[i][j][k] = moveboard[j][k];
			}
		}
	}

	bool isSame = true;

	
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			if(tmpboard[nextaction][i][j] != board[i][j]){
				isSame = false;
				return static_cast<MoveDirection>(nextaction);
			}
		}
	}
	
	return static_cast<MoveDirection>(rand() % 4);
}

void Fib2584Ai::ReadWeightTable()
{
	char filename[30] = "WeightTable1.bin";
	char filename2[30] = "WeightTable2.bin";
	char filename3[30] = "WeightTable3.bin";

	ifstream fin(filename, ios::in | ios::binary );
	ifstream fin2(filename2, ios::in | ios::binary );
	ifstream fin3(filename3, ios::in | ios::binary );

	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
	}

	if( !fin2.is_open()){
		printf("The file '%s' was not open\n", filename2);
	}

	if( !fin3.is_open()){
		printf("The file '%s' was not open\n", filename3);
	}

	for (int i = 0 ; i<iUpperBound_6tile;i ++){
		for (int j = 0 ; j<iUpperBound_6tile ; j++){
			for (int k = 0 ; k<iUpperBound_6tile ; k++){
				for (int l = 0 ; l<iUpperBound_6tile ; l++){
					for (int m = 0 ; m < iUpperBound_6tile ; m++){
						for (int n = 0 ; n < iUpperBound_6tile ; n++){
							float value = 0 ;
							float value2 = 0;
							float value3 = 0;
							fin.read((char *)&value, sizeof(float));
							fin2.read((char *)&value2, sizeof(float));
							fin3.read((char *)&value3, sizeof(float));
							int inputindex[6] = {i, j, k, l, m, n};
							record.setScore(1, inputindex, value);
							record.setScore(2, inputindex, value2);
							record.setScore(3, inputindex, value3);
						}
					}
				}
			}
		}
	}
	fin.close();
	fin2.close();
	fin3.close();
}
void Fib2584Ai::WriteWeightTable()
{

	char filename[30] = "WeightTable1.bin";
	char filename2[30] = "WeightTable2.bin";
	char filename3[30] = "WeightTable3.bin";

	ofstream fout(filename, ios::out | ios::binary);
	ofstream fout2(filename2, ios::out | ios::binary);
	ofstream fout3(filename3, ios::out | ios::binary);

	if(!fout.is_open()){
		printf("The file '%s' was not open\n", filename);
		abort();
	}

	if(!fout2.is_open()){
		printf("The file '%s' was not open\n", filename2);
		abort();
	}

	if(!fout3.is_open()){
		printf("The file '%s' was not open\n", filename3);
		abort();
	}
	
	for (int i = 0 ; i<iUpperBound_6tile;i ++){
		for (int j = 0 ; j<iUpperBound_6tile ; j++){
			for (int k = 0 ; k<iUpperBound_6tile ; k++){
				for (int l = 0 ; l<iUpperBound_6tile ; l++){
					for (int m = 0 ; m < iUpperBound_6tile ; m++){
						for (int n = 0 ; n < iUpperBound_6tile ; n++){
							int inputindex[6] = {i, j, k, l, m, n};
							float value1 = record.getScore(1, inputindex);
							float value2 = record.getScore(2, inputindex);
							float value3 = record.getScore(3, inputindex);
							fout.write((char *)&value1, sizeof(float));
							fout2.write((char *)&value2, sizeof(float));
							fout3.write((char *)&value3, sizeof(float));
						}
					}
				}
			}
		}
	}

	fout.close();
	fout2.close();
	fout3.close();
}

bool Fib2584Ai::isFull(int board[4][4])
{
	for (int i = 0 ;i < 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			if(board[i][j] == 0)
				return false;
		}
	}
	return true;
}

bool Fib2584Ai::isEmpty(int board[4][4])
{
	for (int i = 0 ;i < 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			if(board[i][j] != 0)
				return false;
		}
	}
	return true;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
