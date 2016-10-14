#include "Fib2584Ai.h"


Fib2584Ai::Fib2584Ai()
{
//	LEARNING_RATE = 0.0025;
	LEARNING_RATE = 0.01;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
	move.MakeTable();
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	for (int i = 0 ;i<4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			board[i][j] = GetFibOrder(board[i][j]);
		}
	}
	return FindBestDirection(board);
}

void Fib2584Ai::gameOver(int finalboard[4][4], int iScore)
{
	Learn_Evaluation(finalboard, iScore);
	
}

float Fib2584Ai::Evaluate(int board[4][4])
{
		return record_rec.getScore(board) + record_axe.getScore(board) + record_straightline.getScore((board));

}


MoveDirection Fib2584Ai::FindBestDirection(int board[4][4])
{
	
	int nextaction = rand() % 4;
	int next_tmp = nextaction;
	float score[4] = {};
	int award[4] = {};
	int moveboard[4][4][4] = {};
	Board board_stack;
	
	for (int i = 0 ; i<4 ; i++){
		int direction = ( i + next_tmp ) % 4;
		
		for (int j = 0 ; j<4 ; j++){
			for (int k = 0 ;k<4 ;k++){
				moveboard[i][j][k] = board[j][k];
			}
		}

		int tmpaward = 0;
		move.Move(direction, moveboard[i], tmpaward);
		award[direction] = tmpaward;
		score[direction] = Evaluate(moveboard[i]) + tmpaward;

		if(score[direction] >= score[nextaction]){
			nextaction = direction;

			for (int j = 0 ; j<4 ; j++){
				for (int k = 0 ;k<4 ;k++){
					board_stack.state[j][k] = moveboard[i][j][k];
				}
			}
		}
	}
	
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			if(board_stack.state[i][j] != board[i][j]){
				board_stack.score = award[nextaction];
				board_stack.weight = score[nextaction] - award[nextaction];
				boardstack.push(board_stack);
				return static_cast<MoveDirection>(nextaction);
			}
		}
	}
	
	for (int i = 0 ; i<4 ; i++){
		for (int j = 0 ;j<4 ;j++){
			board_stack.state[i][j] = moveboard[next_tmp][i][j];
		}
	}
	
	nextaction = next_tmp;
	board_stack.score = award[nextaction];
	board_stack.weight = score[nextaction] - award[nextaction];
	boardstack.push(board_stack);
	return static_cast<MoveDirection>(nextaction);
}


void Fib2584Ai::Learn_Evaluation(int finalboard[4][4], int finalscore)
{
	Board nextboard;
	float next_value = 0;
	float now_value = 0;
	float delta = 0;
	bool isFinal = true;

	while(boardstack.empty() == false){

		now_value = boardstack.top().weight;
		if (isFinal == true){
			delta = LEARNING_RATE * now_value * -1;
			isFinal = false;
		}
		else{
			next_value = nextboard.weight;
			delta = LEARNING_RATE * ((float)(finalscore - boardstack.top().score) + next_value - now_value);
		}
		for (int i = 0; i < 8; i++){
			float new_value1 = record_rec.get_OneFeature_Score(1, boardstack.top().state, i) + delta ;
			record_rec.set_OneFeature_Score(1, boardstack.top().state, i, new_value1);

			float new_value2 = record_rec.get_OneFeature_Score(2, boardstack.top().state, i) + delta;
			record_rec.set_OneFeature_Score(2, boardstack.top().state, i, new_value2);

			float new_value3 = record_axe.get_OneFeature_Score(1, boardstack.top().state, i) + delta ;
			record_axe.set_OneFeature_Score(1, boardstack.top().state, i, new_value3);

			float new_value = record_straightline.get_OneFeature_Score(boardstack.top().state, i) + delta;
			record_straightline.set_OneFeature_Score(boardstack.top().state, i, new_value);
		}

		nextboard = boardstack.top();
		boardstack.pop();
	}

}


void Fib2584Ai::ReadWeightTable()
{
	record_axe.ReadWeightTable();
	record_rec.ReadWeightTable();
	record_straightline.ReadWeightTable();
	/*char filename[30] = "WeightTable_Rec_1.bin";
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
	fin5.close();*/
}
void Fib2584Ai::WriteWeightTable()
{
	record_axe.WriteWeightTable();
	record_rec.WriteWeightTable();
	record_straightline.WriteWeightTable();
	/*char filename[30] = "WeightTable_Rec_1.bin";
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
	fout5.close();*/
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

int Fib2584Ai::GetFibOrder(int Fibnumber)
{
	switch(Fibnumber){
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 5:
		return 4;
		break;
	case 8:
		return 5;
		break;
	case 13:
		return 6;
		break;
	case 21:
		return 7;
		break;
	case 34:
		return 8;
		break;
	case 55:
		return 9;
		break;
	case 89:
		return 10;
		break;
	case 144:
		return 11;
		break;
	case 233:
		return 12;
		break;
	case 377:
		return 13;
		break;
	case 610:
		return 14;
		break;
	case 987:
		return 15;
		break;
	case 1597:
		return 16;
		break;
	case 2584:
		return 17;
		break;
	case 4181:
		return 18;
		break;
	case 6765:
		return 19;
		break;
	case 10946:
		return 20;
		break;
	case 17711:
		return 21;
		break;
	case 28657:
		return 22;
		break;
	case 46368:
		return 23;
		break;
	case 75025:
		return 24;
		break;
	case 121393:
		return 25;
		break;
	case 196418:
		return 26;
		break;
	case 317811:
		return 27;
		break;
	case 514229:
		return 28;
		break;
	case 832040:
		return 29;
		break;
	case 1346269:
		return 30;
		break;
	case 2178309:
		return 31;
		break;
	default	:
		return -1;
		break;
	}
}


/**********************************
You can implement any additional functions
you may need.
**********************************/
