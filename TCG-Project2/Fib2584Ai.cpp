#include "Fib2584Ai.h"

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	feature_number = 0;
	srand(time(NULL));
#ifdef __TCLMODE
	printf("Tcl Mode is opened.\n ");
#endif
#ifdef __RESEARCHMODE__ 
	printf("Research Mode is opened. \n");
#endif
#ifdef __TCLAMBDAMODE__ 
	printf("TC Lambda Mode is opened. \n");
#endif
#ifdef __MULTISTAGE_MAXTILEMODE__
	printf("Multi-Stage MaxTile Mode is opened.\n");
#endif
#ifdef __MULTISTAGE_TILENUMMODE__
	printf("Multi_Stage TileNumber Mode is opened. \n");
#endif
#ifdef __PARALLELMODE__
	printf("Parallel: Parallel Mode is opened\n");
#endif
#ifdef __TCLAMBDAMODE__
	printf("TC Lambda Mode is opened\n");
#endif
#ifdef __INSIDELINEMODE__
	int line_inside_index[4] = {1, 5, 9, 13};
	Line_Inside.SetParameter(line_inside_index);
	printf("Feature: Line Inside is used\n");
	feature_number++;
#endif
#ifdef __OUTSIDELINEMODE__
	int line_outside_index[4] = {0, 4, 8, 12};
	Line_Outside.SetParameter(line_outside_index);
	printf("Feature: Line Outside is used\n");
	feature_number++;
#endif
#ifdef __OUTSIDEAXEMODE__
	int axe_outside_index[6] = {12, 8, 4, 0, 1, 5};
	Axe_Outside.SetParameter(axe_outside_index);
	printf("Feature: Axe Outside is used\n");
	feature_number++;
#endif
#ifdef __INSIDEAXEMODE__
	int axe_inside_index[6] = {13, 9, 5, 1, 2, 6};
	Axe_Inside.SetParameter(axe_inside_index);
	printf("Feature: Axe Inside is used\n");
	feature_number++;
#endif
#ifdef __OUTSIDERECMODE__
	int rec_outside_index[6] = {8, 4, 0, 1, 5, 9};
	Rec_Outside.SetParameter(rec_outside_index);
	printf("Feature: Rec Outside is used\n");
	feature_number++;
#endif
#ifdef __INSIDERECMODE__
	int rec_inside_index[6] = {9, 5, 1, 2, 6, 10};
	Rec_Inside.SetParameter(rec_inside_index);
	printf("Feature: Rec Inside is used\n");
	feature_number++;
#endif
#ifdef __TRIANGLEMODE__
	int triangle_index[6] = {0, 1, 2, 4, 5, 8};
	Triangle.SetParameter(triangle_index);
	printf("Feature: Triangle is used\n");
	feature_number++;
#endif
#ifdef __BOXATANGLEMODE__
	int box_angle_index[4] = {0, 1, 4, 5};
	Box_Angle.SetParameter(box_angle_index);
	printf("Feature: Box_Angle is used\n");
	feature_number++;
#endif
#ifdef __BOXATMIDDLEMODE__
	int box_middle_index[4] = {5, 6, 9, 10};
	Box_Middle.SetParameter(box_middle_index);
	printf("Feature: Box_Middle is used\n");
	feature_number++;
#endif
#ifdef __BOXATSIDEMODE__
	int box_side_index[4] = {1, 2, 5, 6};
	Box_Side.SetParameter(box_side_index);
	printf("Feature: Box_Side is used\n");
	feature_number++;
#endif
#ifdef __COUNTTILENUMBERMODE__
	printf("Feature: Tile Number is used\n");
	feature_number++;
#endif
#ifdef __MERGETILEMODE__
	int row1[4] = {0, 1, 2, 3};
	int row2[4] = {4, 5, 6, 7};
	MergeTile_Row1.SetParameter(row1);
	MergeTile_Row2.SetParameter(row2);
 	printf("Feature: MergeTile is used\n");
	feature_number++;
	feature_number++;
#endif
#ifdef __MERGECOUNTMODE__
	int mergecount_row1[4] = {0, 1, 2, 3};
	int mergecount_row2[4] = {4, 5, 6, 7};
	MergeCount_Row1.SetParameter(mergecount_row1);
	MergeCount_Row2.SetParameter(mergecount_row2);
	printf("Feature: MergeCount is used\n");
#endif
#ifdef __CONSTANTVALUEMODE__
	Adjust_Weight = 0;
#endif
#ifdef __WRITELOGMODE__
	printf("Write Log Mode is opened\n");
#endif
	mapFibOrder[0] = 0;
	mapFibOrder[1] = 1;
	mapFibOrder[2] = 2;
	mapFibOrder[3] = 3;
	mapFibOrder[5] = 4;
	mapFibOrder[8] = 5;
	mapFibOrder[13] = 6;
	mapFibOrder[21] = 7;
	mapFibOrder[34] = 8;
	mapFibOrder[55] = 9;
	mapFibOrder[89] = 10;
	mapFibOrder[144] = 11;
	mapFibOrder[233] = 12;
	mapFibOrder[377] = 13;
	mapFibOrder[610] = 14;
	mapFibOrder[987] = 15;
	mapFibOrder[1597] = 16;
	mapFibOrder[2584] = 17;
	mapFibOrder[4181] = 18;
	mapFibOrder[6765] = 19;
	mapFibOrder[10946] = 20;
	mapFibOrder[17711] = 21;
	mapFibOrder[28657] = 22;
	mapFibOrder[46368] = 23;
	mapFibOrder[75025] = 24;
	mapFibOrder[121393] = 25;
	mapFibOrder[196418] = 26;
	mapFibOrder[317811] = 27;
	mapFibOrder[514229] = 28;
	mapFibOrder[832040] = 29;
	mapFibOrder[1346269] = 30;
	mapFibOrder[2178309] = 31;
	ReadFromWeightTable();
	return;
}

#ifdef __PARALLELMODE__
MoveDirection Fib2584Ai::generateMove(int board[4][4], std::stack<Array_Board> & Array_Board_Stack)
#else
MoveDirection Fib2584Ai::generateMove(int board[4][4])
#endif
{
	for (int j = 0; j<4; j++) {
		for (int k = 0; k<4; k++) {
			board[j][k] = mapFibOrder[(board[j][k])];
		}
	}
	Array_Board b_struct;
	MoveDirection next_dir = static_cast<MoveDirection>(0);
#ifdef __RESEARCHMODE__
	int movedboard[4][4][4] = { 0 };
	int award[4] = { 0 };
	float evaluation[4] = { 0 };

	for (int i = 0; i < 4; i++) {
		SetBoard(movedboard[i], board);
		award[i] = Move.Move(i, movedboard[i]);
		if (isSameBoard(movedboard[i], board) == true) {
			evaluation[i] = NOMOVEPENALTY;
			continue;
		}

		// search one layer
		int empty_count = 0;
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (movedboard[i][j][k] == 0)
				{
					empty_count++;
					int tmpboard1[4][4] = { 0 };
					int tmpboard2[4][4] = { 0 };
					SetBoard(tmpboard1, movedboard[i]);
					SetBoard(tmpboard2, movedboard[i]);
					tmpboard1[j][k] = 1;
					tmpboard2[j][k] = 3;
					MoveDirection tmp_dir1 = FindBestDirection(tmpboard1);
					MoveDirection tmp_dir2 = FindBestDirection(tmpboard2);
					evaluation[i] += Move.Move(tmp_dir1, tmpboard1) * 3 / 4 + Move.Move(tmp_dir2, tmpboard2) / 4;
					evaluation[i] += Evaluate(tmpboard1) * 3 / 4 + Evaluate(tmpboard2) / 4;
				}
			}
		}
		if (empty_count > 0)
			evaluation[i] = evaluation[i] / empty_count;
		else
			evaluation[i] = NOMOVEPENALTY;
		if (evaluation[i] > evaluation[next_dir]) {
			next_dir = static_cast<MoveDirection>(i);
		}
	}
	SetBoard(b_struct.state, movedboard[next_dir]);
	b_struct.award = award[next_dir];
#else
	int tmpboard[4][4] = {};
	SetBoard(tmpboard, board);
	next_dir = FindBestDirection(tmpboard);
	b_struct.award = Move.Move(next_dir, tmpboard);
	SetBoard(b_struct.state, tmpboard);
#endif
#ifdef __TRAININGMODE__
	Array_Board_Stack.push(b_struct);
#endif
	return next_dir;
}


MoveDirection Fib2584Ai::FindBestDirection(int board[4][4])
{
	MoveDirection best_dir = static_cast<MoveDirection>(0);

	float evaluation[4] = {};
	float search_evaluation[5] = {};
	int award[4] = {};
	int movedboard[4][4][4] = {};
	for (int i = 0; i< 4; i++) {
		SetBoard(movedboard[i], board);
		award[i] = Move.Move(i, movedboard[i]);

		if (isSameBoard(movedboard[i], board) == true)
			award[i] = NOMOVEPENALTY;
		evaluation[i] = Evaluate(movedboard[i]);
		if (award[i] + evaluation[i] >= award[best_dir] + evaluation[best_dir])
			best_dir = static_cast<MoveDirection>(i);
	}

	return best_dir;
}


float Fib2584Ai::Evaluate(int board[4][4])
{
	float value = 0;
#ifdef __INSIDELINEMODE__
	value += Line_Inside.getWeight(board);
#endif
#ifdef __OUTSIDELINEMODE__
	value += Line_Outside.getWeight(board);
#endif
#ifdef __OUTSIDEAXEMODE__
	value += Axe_Outside.getWeight(board);
#endif
#ifdef __INSIDEAXEMODE__
	value += Axe_Inside.getWeight(board);
#endif
#ifdef __OUTSIDERECMODE__
	value += Rec_Outside.getWeight(board);
#endif
#ifdef __INSIDERECMODE__
	value += Rec_Inside.getWeight(board);
#endif
#ifdef __TRIANGLEMODE__
	value += Triangle.getWeight(board);
#endif
#ifdef __BOXATANGLEMODE__
	value += Box_Angle.getWeight(board);
#endif
#ifdef __BOXATMIDDLEMODE__
	value += Box_Middle.getWeight(board);
#endif
#ifdef __BOXATSIDEMODE__
	value += Box_Side.getWeight(board);
#endif
#ifdef __COUNTTILENUMBERMODE__
	value += Tile_Num.getWeight(board);
#endif
#ifdef __MERGETILEMODE__
	if(GetMaxTile(board) > iLowerBound){
		value += MergeTile_Row1.getWeight(board) + MergeTile_Row2.getWeight(board);
	}
#endif
#ifdef __MERGECOUNTMODE__
	value += MergeCount_Row1.getWeight(board) + MergeCount_Row2.getWeight(board);
#endif
#ifdef __CONSTANTVALUEMODE__
	value += Adjust_Weight;
#endif
	return value;
}

#ifdef __PARALLELMODE__
void Fib2584Ai::gameOver(int board[4][4], int iScore, std::stack<Array_Board> & Array_Board_Stack)
{
#ifdef __TRAININGMODE__
	Learning(Array_Board_Stack);
#endif
	return;
}
#else
void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
#ifdef __TRAININGMODE__
	Learning();
#endif
}
#endif

#ifdef __PARALLELMODE__
void Fib2584Ai::Learning(std::stack<Array_Board> & Array_Board_Stack)
#else
void Fib2584Ai::Learning()
#endif
{
	// TD(lambda)
	// delta_(t-1) = S_(t-1) + F_(t-1)
	// where S_(t-1) = Lambda * S_t + r_t * ( 1 - lambda^(T - t) ) + ( 1 - labmda ) * V(state_t)
	//       F_(t-1) = F_t * lambda + lambda^(T-t) * r_t
	// S_T = F_T = 0

	float S_t = 0;
	float F_t = 0;
	float lambda_power = 1 / LAMBDA;

	int nextaward = 0;
	float nextvalue = 0;
	float nextaward_weight = 0;
	float totalvalue = 0;
	float delta = 0;
	float FinalTerm = 0;
	bool isFinal = true;

	while(Array_Board_Stack.empty() == false){
#ifdef __TCLAMBDAMODE__
		delta = ((S_t + F_t) - Evaluate(Array_Board_Stack.top().state)) / feature_number;
#else
		delta = (nextaward + nextvalue - Evaluate(Array_Board_Stack.top().state)) / feature_number;
#endif
#ifdef __INSIDELINEMODE__
		Line_Inside.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __OUTSIDEAXEMODE__
		Axe_Outside.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __INSIDEAXEMODE__
		Axe_Inside.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __OUTSIDERECMODE__
		Rec_Outside.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __OUTSIDELINEMODE__
		Line_Outside.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __INSIDERECMODE__
		Rec_Inside.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __TRIANGLEMODE__
		Triangle.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __BOXATANGLEMODE__
		Box_Angle.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __BOXATMIDDLEMODE__
		Box_Middle.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __BOXATSIDEMODE__
		Box_Side.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __MERGECOUNTMODE__
		MergeCount_Row1.Update(Array_Board_Stack.top().state, delta);
		MergeCount_Row2.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __COUNTTILENUMBERMODE__
		Tile_Num.Update(Array_Board_Stack.top().state, delta);
#endif
#ifdef __MERGETILEMODE__
	if(GetMaxTile(Array_Board_Stack.top().state )> iLowerBound){
		MergeTile_Row1.Update(Array_Board_Stack.top().state, delta);
		MergeTile_Row2.Update(Array_Board_Stack.top().state, delta);
	}
#endif

#ifdef __CONSTANTVALUEMODE__
		Adjust_Weight += delta;
#endif
#ifdef __TCLAMBDAMODE__
		nextvalue = Evaluate(Array_Board_Stack.top().state);
		nextaward = Array_Board_Stack.top().award;
		
		if (isFinal == true) {
			lambda_power *= LAMBDA;
			S_t = 0;
			F_t = nextaward + nextvalue;
			isFinal = false;
		}
		else {
			lambda_power *= LAMBDA;
			S_t = LAMBDA * S_t + nextaward * (1 - lambda_power) + (1 - LAMBDA) * nextvalue;
			F_t = F_t * LAMBDA + lambda_power * nextaward;
		}
		
#else
		nextvalue = Evaluate(Array_Board_Stack.top().state);
		nextaward = Array_Board_Stack.top().award;
#endif
		
		Array_Board_Stack.pop();
	}
}

int Fib2584Ai::SetBoard(int b1[4][4], const int b2[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			b1[i][j] = b2[i][j];
	return 0;
}

void Fib2584Ai::WriteToWeightTable()
{
#ifdef __WRITEWEIGHTTABLEMODE__
	printf("Write WeightTable Mode is opened\n");
#ifdef __INSIDELINEMODE__
	Line_Inside.WriteToWeightTable("Line_Inside_WeightTable");
#endif
#ifdef __OUTSIDELINEMODE__
	Line_Outside.WriteToWeightTable("Line_Outside_WeightTable");
#endif
#ifdef __OUTSIDEAXEMODE__
	Axe_Outside.WriteToWeightTable("Axe_Outside_WeightTable");
#endif
#ifdef __INSIDEAXEMODE__
	Axe_Inside.WriteToWeightTable("Axe_Inside_WeightTable");
#endif
#ifdef __OUTSIDERECMODE__
	Rec_Outside.WriteToWeightTable("Rec_Outside_WeightTable");
#endif
#ifdef __INSIDERECMODE__
	Rec_Inside.WriteToWeightTable("Rec_Inside_WeightTable");
#endif
#ifdef __TRIANGLEMODE__
	Triangle.WriteToWeightTable("Triangle_WeightTable");
#endif
#ifdef __BOXATANGLEMODE__
	Box_Angle.WriteToWeightTable("Box_Angle_WeightTable");
#endif
#ifdef __BOXATMIDDLEMODE__
	Box_Middle.WriteToWeightTable("Box_Middle_WeightTable");
#endif
#ifdef __BOXATSIDEMODE__
	Box_Side.WriteToWeightTable("Box_Side_WeightTable");
#endif
#ifdef __COUNTTILENUMBERMODE__
	Tile_Num.WriteToWeightTable("Tile_Num_WeightTable");
#endif
#ifdef __MERGETILEMODE__
	MergeTile_Row1.WriteToWeightTable("Merge_Tile_WeightTable1");
	MergeTile_Row2.WriteToWeightTable("Merge_Tile_WeightTable2");
#endif
#ifdef __MERGECOUNTMODE__
	MergeCount_Row1.WriteToWeightTable("Merge_Count_WeightTable1");
	MergeCount_Row2.WriteToWeightTable("Merge_Count_WeightTable2");
#endif
#endif
}

void Fib2584Ai::ReadFromWeightTable()
{
#ifdef __READWEIGHTTABLEMODE__
	printf("Read WeightTable Mode is opened\n");
#ifdef __INSIDELINEMODE__
	Line_Inside.ReadFromWeightTable("Line_Inside_WeightTable");
#endif
#ifdef __OUTSIDELINEMODE__
	Line_Outside.ReadFromWeightTable("Line_Outside_WeightTable");
#endif
#ifdef __OUTSIDEAXEMODE__
	Axe_Outside.ReadFromWeightTable("Axe_Outside_WeightTable");
#endif
#ifdef __INSIDEAXEMODE__
	Axe_Inside.ReadFromWeightTable("Axe_Inside_WeightTable");
#endif
#ifdef __OUTSIDERECMODE__
	Rec_Outside.ReadFromWeightTable("Rec_Outside_WeightTable");
#endif
#ifdef __INSIDERECMODE__
	Rec_Inside.ReadFromWeightTable("Rec_Inside_WeightTable");
#endif
#ifdef __TRIANGLEMODE__
	Triangle.ReadFromWeightTable("Triangle_WeightTable");
#endif
#ifdef __BOXATANGLEMODE__
	Box_Angle.ReadFromWeightTable("Box_Angle_WeightTable");
#endif
#ifdef __BOXATMIDDLEMODE__
	Box_Middle.ReadFromWeightTable("Box_Middle_WeightTable");
#endif
#ifdef __BOXATSIDEMODE__
	Box_Side.ReadFromWeightTable("Box_Side_WeightTable");
#endif
#ifdef __COUNTTILENUMBERMODE__
	Tile_Num.ReadFromWeightTable("Tile_Num_WeightTable");
#endif
#ifdef __MERGETILEMODE__
	MergeTile_Row1.ReadFromWeightTable("Merge_Tile_WeightTable1");
	MergeTile_Row2.ReadFromWeightTable("Merge_Tile_WeightTable2");
#endif
#ifdef __MERGECOUNTMODE__
	MergeCount_Row1.ReadFromWeightTable("Merge_Count_WeightTable1");
	MergeCount_Row2.ReadFromWeightTable("Merge_Count_WeightTable2");
#endif
#endif
}

void Fib2584Ai::WriteLog()
{
#ifdef __WRITELOGMODE__

#endif
}

bool Fib2584Ai::isSameBoard( int board1[4][4], int board2[4][4])
{
	for (int i = 0 ; i<4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			if(board1[i][j] != board2[i][j])
				return false;
		}
	}
	return true;
}

int Fib2584Ai::GetMaxTile(int board[4][4])
{
	int max = 0;
	for (int i = 0 ;i<4 ; i++){
		for (int j = 0 ;j<4 ; j++){
			if(board[i][j] > max)
				max = board[i][j];
		}
	}
	return max;
}
/**********************************
You can implement any additional functions
you may need.
**********************************/
