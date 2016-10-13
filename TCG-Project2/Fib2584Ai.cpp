#include "Fib2584Ai.h"


Fib2584Ai::Fib2584Ai()
{
	LEARNING_RATE = 0.0025*3;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	for (int i = 0 ; i<4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			nextboard_moved[i][j] = 0;
		}
	}
	srand(time(NULL));
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

	return currentaction;
}

void Fib2584Ai::gameOver(int finalboard[4][4], int iScore)
{
	Learn_Evaluation(finalboard, iScore);
	
}

float Fib2584Ai::Evaluate(int board[4][4])
{
	return record_rec.getScore(board) + record_axe.getScore(board);

}


void Fib2584Ai::Learn_Evaluation(int finalboard[4][4], int finalscore)
{
	for (int i = 0 ; i<4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			nextboard_moved[i][j] = finalboard[i][j];
		}
	}
	
	float next_value = 0;
	float now_value = 0;
	float delta = 0;
	bool isFinal = true;

	while(boardstack.empty() == false){
		
		now_value = Evaluate(boardstack.top().state);
		if (isFinal == true){
			delta = LEARNING_RATE * now_value * -1;
			isFinal = false;
		}
		else{
			next_value = Evaluate(nextboard_moved);
			delta = LEARNING_RATE * ((float)(finalscore - boardstack.top().score) + next_value - now_value);
		}

		for (int i = 0; i < 8; i++){
			float new_value1 = record_rec.get_OneFeature_Score(1, boardstack.top().state, i) + delta ;
			record_rec.set_OneFeature_Score(1, boardstack.top().state, i, new_value1);

			float new_value2 = record_rec.get_OneFeature_Score(2, boardstack.top().state, i) + delta;
			record_rec.set_OneFeature_Score(2, boardstack.top().state, i, new_value2);

			float new_value3 = record_axe.get_OneFeature_Score(1, boardstack.top().state, i) + delta ;
			record_axe.set_OneFeature_Score(1, boardstack.top().state, i, new_value3);
			
			float new_value4 = record_axe.get_OneFeature_Score(2, boardstack.top().state, i) + delta ;
			record_axe.set_OneFeature_Score(2, boardstack.top().state, i, new_value4);
			
			float new_value5 = record_axe.get_OneFeature_Score(3, boardstack.top().state, i) + delta ;
			record_axe.set_OneFeature_Score(3, boardstack.top().state, i, new_value5);

		}
		
		for (int i = 0 ; i<4 ; i++){
			for (int j = 0 ; j<4 ; j++){
				nextboard_moved[i][j] = boardstack.top().state[i][j];
			}
		}
		boardstack.pop();
	}

	
}

MoveDirection Fib2584Ai::FindBestDirection(int board[4][4])
{
	int nextaction = 0;
	float score[4] = {};
	int award[4] = {};
	int tmpboard[4][4][4] = {};
	Board board_stack;

	for (int i = 0 ; i<4 ; i++){
		int moveboard[4][4] = {};
		for (int j = 0 ; j<4 ; j++){
			for (int k = 0 ;k<4 ;k++){
				moveboard[j][k] = board[j][k];
			}
		}

		int tmpaward = 0;
		move.Move(i, moveboard, tmpaward);
		award[i] = tmpaward;
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

	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			if(tmpboard[nextaction][i][j] != board[i][j]){
				board_stack.score = award[nextaction];
				for (int k = 0 ; k<4 ; k++){
					for (int l = 0 ; l < 4 ;l++){
						board_stack.state[k][l] = tmpboard[nextaction][k][l];
					}
				}
				boardstack.push(board_stack);
				return static_cast<MoveDirection>(nextaction);
			}
		}
	}
	
	nextaction = rand() % 4;
	board_stack.score = award[nextaction];
	for (int k = 0 ; k<4 ; k++){
		for (int l = 0 ; l < 4 ;l++){
			board_stack.state[k][l] = tmpboard[nextaction][k][l];
		}
	}
	boardstack.push(board_stack);

	return static_cast<MoveDirection>(nextaction);
}

void Fib2584Ai::ReadWeightTable()
{
	char filename[30] = "WeightTable_Rec_1.bin";
	char filename2[30] = "WeightTable_Rec_2.bin";
	char filename3[30] = "WeightTable_Axe_1.bin";
	char filename4[30] = "WeightTable_Axe_2.bin";
	char filename5[30] = "WeightTable_Axe_3.bin";

	ifstream fin(filename, ios::in | ios::binary );
	ifstream fin2(filename2, ios::in | ios::binary );
	ifstream fin3(filename3, ios::in | ios::binary );
	ifstream fin4(filename4, ios::in | ios::binary );
	ifstream fin5(filename5, ios::in | ios::binary );

	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	if( !fin2.is_open()){
		printf("The file '%s' was not open\n", filename2);
		return ;
	}

	if( !fin3.is_open()){
		printf("The file '%s' was not open\n", filename3);
		return ;
	}

	if( !fin4.is_open()){
		printf("The file '%s' was not open\n", filename4);
		return ;
	}

	if( !fin5.is_open()){
		printf("The file '%s' was not open\n", filename5);
		return ;
	}

	for (int i = 0 ; i<iUpperBound_6tile;i ++){
		for (int j = 0 ; j<iUpperBound_6tile ; j++){
			for (int k = 0 ; k<iUpperBound_6tile ; k++){
				for (int l = 0 ; l<iUpperBound_6tile ; l++){
					for (int m = 0 ; m < iUpperBound_6tile ; m++){
						for (int n = 0 ; n < iUpperBound_6tile ; n++){
							float value = 0 ;
							int inputindex[6] = {i, j, k, l, m, n};
							fin.read((char *)&value, sizeof(float));
							record_rec.setScore(1, inputindex, value);

							fin2.read((char *)&value, sizeof(float));
							record_rec.setScore(2, inputindex, value);
							
							fin3.read((char *)&value, sizeof(float));
							record_axe.setScore(1, inputindex, value);
							
							fin4.read((char *)&value, sizeof(float));
							record_axe.setScore(2, inputindex, value);
							
							fin5.read((char *)&value, sizeof(float));
							record_axe.setScore(3, inputindex, value);
							
						}
					}
				}
			}
		}
	}
	fin.close();
	fin2.close();
	fin3.close();
	fin4.close();
	fin5.close();
}
void Fib2584Ai::WriteWeightTable()
{

	char filename[30] = "WeightTable_Rec_1.bin";
	char filename2[30] = "WeightTable_Rec_2.bin";
	char filename3[30] = "WeightTable_Axe_1.bin";
	char filename4[30] = "WeightTable_Axe_2.bin";
	char filename5[30] = "WeightTable_Axe_3.bin";

	ofstream fout(filename, ios::out | ios::binary);
	ofstream fout2(filename2, ios::out | ios::binary);
	ofstream fout3(filename3, ios::out | ios::binary);
	ofstream fout4(filename4, ios::out | ios::binary);
	ofstream fout5(filename5, ios::out | ios::binary);

	if(!fout.is_open()){
		printf("The file '%s' was not open\n", filename);
	}

	if(!fout2.is_open()){
		printf("The file '%s' was not open\n", filename2);
	}

	if(!fout3.is_open()){
		printf("The file '%s' was not open\n", filename3);
	}

	if(!fout4.is_open()){
		printf("The file '%s' was not open\n", filename4);
	}

	if(!fout5.is_open()){
		printf("The file '%s' was not open\n", filename5);
	}
	
	for (int i = 0 ; i<iUpperBound_6tile;i ++){
		for (int j = 0 ; j<iUpperBound_6tile ; j++){
			for (int k = 0 ; k<iUpperBound_6tile ; k++){
				for (int l = 0 ; l<iUpperBound_6tile ; l++){
					for (int m = 0 ; m < iUpperBound_6tile ; m++){
						for (int n = 0 ; n < iUpperBound_6tile ; n++){

							float value = 0 ;
							int inputindex[6] = {i, j, k, l, m, n};
							
							value = record_rec.getScore(1, inputindex);
							fout.write((char *)&value, sizeof(float));

							value = record_rec.getScore(2, inputindex);
							fout2.write((char *)&value, sizeof(float));

							value = record_axe.getScore(1, inputindex);
							fout3.write((char *)&value, sizeof(float));

							value = record_axe.getScore(2, inputindex);
							fout4.write((char *)&value, sizeof(float));
							
							value = record_axe.getScore(3, inputindex);
							fout5.write((char *)&value, sizeof(float));
						}
					}
				}
			}
		}
	}

	fout.close();
	fout2.close();
	fout3.close();
	fout4.close();
	fout5.close();
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
