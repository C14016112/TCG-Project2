#include "Fib2584Ai.h"

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	icurRound = 0;
	feature_number = 0;
	srand(time(NULL));
#ifdef __TCLMODE
	printf("Tcl Mode is opened.\n ");
#endif
#ifdef __SEARCHMODE__ 
	printf("Search Mode -%d layer- is opened. \n", CUT_OFF_DEPTH);
#endif
#ifdef __UCTMODE__
	printf("UCT Mode is opened. \n");
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
MoveDirection Fib2584Ai::generateMove(int Fibboard[4][4], std::stack<Array_Board> & Array_Board_Stack)
#else
MoveDirection Fib2584Ai::generateMove(int Fibboard[4][4])
#endif
{
	int board[16] = {};
	for (int i = 0; i < 16; i++)
		board[i] = mapFibOrder[Fibboard[i >> 2][i % 4]];
	
	Array_Board b_struct;
	MoveDirection next_dir = static_cast<MoveDirection>(0);
#ifdef __SEARCHMODE__
	float evaluation[4] = {0};
	int award[4] = {0};
	int movedboard[4][16] = {0};
	int depth = ((Tile_Num.GetStage(board) + 1)) * CUT_OFF_DEPTH;
	for (int i = 0; i < 4; i++) {
		SetBoard(movedboard[i], board);
		bool ismoved = false;
		award[i] = Move.Move(i, movedboard[i], ismoved);
		if (ismoved == false) {
			award[i] = NOMOVEPENALTY;
			continue;
		}
		else {
			evaluation[i] = Scout(movedboard[i], -FLT_MAX, FLT_MAX, depth*2);
		}
		if (award[i] + evaluation[i] >= award[next_dir] + evaluation[next_dir])
			next_dir = static_cast<MoveDirection>(i);
	}
	b_struct.award = award[next_dir];
	SetBoard(b_struct.state, movedboard[next_dir]);
#elif defined __UCTMODE__
	next_dir = static_cast<MoveDirection>(Simulation(board, b_struct));
#else
	int tmpboard[16] = {};
	SetBoard(tmpboard, board);
	next_dir = FindBestDirection(tmpboard);
	bool ismoved = false;
	b_struct.award = Move.Move(next_dir, tmpboard, ismoved);
	SetBoard(b_struct.state, tmpboard);
#endif
#ifdef __TRAININGMODE__
	Array_Board_Stack.push(b_struct);
#endif
	return next_dir;
}

int Fib2584Ai::generateEvilMove(int Fibboard[4][4])
{
	int board[16] = {};
	for (int i = 0; i < 16; i++)
		board[i] = mapFibOrder[Fibboard[i >> 2][i % 4]];
	
	int depth = ((Line_Inside.GetStage(board) + 1) >> 1) + 1;
	int cur_round = getTileSum(board) % 6;
	float evaluation[16] = { 0 };
	for (int i = 0; i < 16; i++)
		evaluation[i] = FLT_MAX;
	int worst_index = 0;

	for (int i = 0; i < 16; i++) {
		if (board[i] == 0) {
			int tmpboard[16] = {};
			SetBoard(tmpboard, board);
			if (cur_round == 3)
				tmpboard[i] = 3;
			else
				tmpboard[i] = 1;
			evaluation[i] = alphabeta_Max(tmpboard, -FLT_MAX, FLT_MAX, depth);
		}
		if (evaluation[i] < evaluation[worst_index])
			worst_index = i;
	}
	return worst_index;
}

MoveDirection Fib2584Ai::FindBestDirection(int board[16])
{
	MoveDirection best_dir = static_cast<MoveDirection>(0);

	float evaluation[4] = {};
	int award[4] = {};
	int movedboard[4][16] = {};
	for (int i = 0; i< 4; i++) {
		SetBoard(movedboard[i], board);
		bool ismoved = false;
		award[i] = Move.Move(i, movedboard[i], ismoved);
		if (ismoved == false)
			award[i] = NOMOVEPENALTY;
		evaluation[i] = Evaluate(movedboard[i]);
		if (award[i] + evaluation[i] >= award[best_dir] + evaluation[best_dir])
			best_dir = static_cast<MoveDirection>(i);
	}
	return best_dir;
}

#ifdef __MULTITHREADMODE__
float Fib2584Ai::Evaluate(int board[16])
{
	int stage = Line_Inside.GetStage(board);
	float value = 0;
#pragma omp parallel sections num_threads(THREADNUM)
	{
#ifdef __INSIDELINEMODE__
#pragma omp section
	{
		value += Line_Inside.getWeight(board, stage);
	}
#endif
#ifdef __OUTSIDELINEMODE__
#pragma omp section
	{
		value += Line_Outside.getWeight(board, stage);
	}
#endif
#ifdef __OUTSIDEAXEMODE__
#pragma omp section
	{
		value += Axe_Outside.getWeight(board, stage);
	}
#endif
#ifdef __INSIDEAXEMODE__
#pragma omp section
	{
		value += Axe_Inside.getWeight(board, stage);
	}
#endif
#ifdef __OUTSIDERECMODE__
#pragma omp section
	{
		value += Rec_Outside.getWeight(board, stage);
	}
#endif
#ifdef __INSIDERECMODE__
#pragma omp section
	{
		value += Rec_Inside.getWeight(board, stage);
	}
#endif
#ifdef __TRIANGLEMODE__
#pragma omp section
	{
		value += Triangle.getWeight(board, stage);
	}
#endif
#ifdef __BOXATANGLEMODE__
#pragma omp section
	{
		value += Box_Angle.getWeight(board, stage);
	}
#endif
#ifdef __BOXATMIDDLEMODE__
#pragma omp section
	{
		value += Box_Middle.getWeight(board, stage);
	}
#endif
#ifdef __BOXATSIDEMODE__
#pragma omp section
	{
		value += Box_Side.getWeight(board, stage);
	}
#endif
#ifdef __COUNTTILENUMBERMODE__
#pragma omp section
	{
		value += Tile_Num.getWeight(board, stage);
	}
#endif
#ifdef __MERGETILEMODE__
#pragma omp section
	{
		if (Mergetile_Row1.getMaxTile(board) > iLowerBound) {
			value += MergeTile_Row1.getWeight(board) + MergeTile_Row2.getWeight(board, stage);
		}
	}
#endif
#ifdef __MERGECOUNTMODE__
#pragma omp section
	{
		value += MergeCount_Row1.getWeight(board, stage) + MergeCount_Row2.getWeight(board, stage);
	}
#endif
#ifdef __CONSTANTVALUEMODE__
#pragma omp section
	{
		value += Adjust_Weight;
	}
#endif
	}
	return value;
}

#else
float Fib2584Ai::Evaluate(int board[16])
{
	// if there are some tiles larger than max tile, let them be max tile
	for (int i = 0; i < 16; i++)
		board[i] = (board[i] > iUpperbound) ? iUpperbound : board[i];

	int stage = Line_Inside.GetStage(board);
	float value = 0;
#ifdef __INSIDELINEMODE__
	value += Line_Inside.getWeight(board, stage);
#endif
#ifdef __OUTSIDELINEMODE__
	value += Line_Outside.getWeight(board, stage);
#endif
#ifdef __OUTSIDEAXEMODE__
	value += Axe_Outside.getWeight(board, stage);
#endif
#ifdef __INSIDEAXEMODE__
	value += Axe_Inside.getWeight(board, stage);
#endif
#ifdef __OUTSIDERECMODE__
	value += Rec_Outside.getWeight(board, stage);
#endif
#ifdef __INSIDERECMODE__
	value += Rec_Inside.getWeight(board, stage);
#endif
#ifdef __TRIANGLEMODE__
	value += Triangle.getWeight(board, stage);
#endif
#ifdef __BOXATANGLEMODE__
	value += Box_Angle.getWeight(board, stage);
#endif
#ifdef __BOXATMIDDLEMODE__
	value += Box_Middle.getWeight(board, stage);
#endif
#ifdef __BOXATSIDEMODE__
	value += Box_Side.getWeight(board, stage);
#endif
#ifdef __COUNTTILENUMBERMODE__
	value += Tile_Num.getWeight(board, stage);
#endif
#ifdef __MERGETILEMODE__
	if(Mergetile_Row1.getMaxTile(board) > iLowerBound){
		value += MergeTile_Row1.getWeight(board) + MergeTile_Row2.getWeight(board, stage);
	}
#endif
#ifdef __MERGECOUNTMODE__
	value += MergeCount_Row1.getWeight(board, stage) + MergeCount_Row2.getWeight(board, stage);
#endif
#ifdef __CONSTANTVALUEMODE__
	value += Adjust_Weight;
#endif
	return value;
}
#endif


#ifdef __PARALLELMODE__
void Fib2584Ai::gameOver(int board[4][4], int iScore, std::stack<Array_Board> & Array_Board_Stack)
{
#ifdef __TRAININGMODE__
	Learning(Array_Board_Stack);
#endif
	return;
}
void Fib2584Ai::gameOver(std::stack<Array_Board> & Array_Board_Stack)
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

#ifdef __MULTITHREADMODE__
void Fib2584Ai::Learning()
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

	float delta = 0;
#ifdef __TCLAMBDAMODE__
	float nextaward_weight = 0;
	float totalvalue = 0;
	float FinalTerm = 0;
	bool isFinal = true;
#endif
	while (Array_Board_Stack.empty() == false) {

#ifdef __TCLAMBDAMODE__
		delta = ((S_t + F_t) - Evaluate(Array_Board_Stack.top().state)) / feature_number;
#else
		float curValue = Evaluate(Array_Board_Stack.top().state);
		delta = (nextaward + nextvalue - curValue) / feature_number;
#endif
		int stage = Line_Inside.GetStage(Array_Board_Stack.top().state);
#pragma omp parallel sections num_threads(THREADNUM)
		{
#ifdef __INSIDELINEMODE__
#pragma omp section
		{
			Line_Inside.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __OUTSIDEAXEMODE__
#pragma omp section
		{
			Axe_Outside.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __INSIDEAXEMODE__
#pragma omp section
		{
			Axe_Inside.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __OUTSIDERECMODE__
#pragma omp section
		{
			Rec_Outside.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __OUTSIDELINEMODE__
#pragma omp section
		{
			Line_Outside.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __INSIDERECMODE__
#pragma omp section
		{
			Rec_Inside.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __TRIANGLEMODE__
#pragma omp section
		{
			Triangle.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __BOXATANGLEMODE__
#pragma omp section
		{
			Box_Angle.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __BOXATMIDDLEMODE__
#pragma omp section
		{
			Box_Middle.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __BOXATSIDEMODE__
#pragma omp section
		{
			Box_Side.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __MERGECOUNTMODE__
#pragma omp section
		{
			MergeCount_Row1.Update(Array_Board_Stack.top().state, delta, stage);
			MergeCount_Row2.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __COUNTTILENUMBERMODE__
#pragma omp section
		{
			Tile_Num.Update(Array_Board_Stack.top().state, delta, stage);
		}
#endif
#ifdef __MERGETILEMODE__
#pragma omp section
		{
			if (MergeTile_Row1.GetMaxTile(Array_Board_Stack.top().state) > iLowerBound) {
				MergeTile_Row1.Update(Array_Board_Stack.top().state, delta, stage);
				MergeTile_Row2.Update(Array_Board_Stack.top().state, delta, stage);
			}
		}
#endif
#ifdef __CONSTANTVALUEMODE__
#pragma omp section
		{
			Adjust_Weight += delta;
		}
#endif
		}
#ifdef __TCLAMBDAMODE__
		nextvalue = Evaluate(Array_Board_Stack.top().state);
		nextaward = Array_Board_Stack.top().award;

	}
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
		nextvalue = curValue;
		nextaward = Array_Board_Stack.top().award;
#endif
		Array_Board_Stack.pop();
	}
}
#else
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
	
	float delta = 0;
#ifdef __TCLAMBDAMODE__
	float nextaward_weight = 0;
	float totalvalue = 0;
	float FinalTerm = 0;
	bool isFinal = true;
#endif
	while(Array_Board_Stack.empty() == false){
#ifdef __TCLAMBDAMODE__
		delta = ((S_t + F_t) - Evaluate(Array_Board_Stack.top().state)) / feature_number;
#else
		float curValue = Evaluate(Array_Board_Stack.top().state);
		delta = (nextaward + nextvalue - curValue ) / feature_number;
#endif
		int stage = Line_Inside.GetStage(Array_Board_Stack.top().state);
#ifdef __INSIDELINEMODE__
			Line_Inside.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __OUTSIDEAXEMODE__
			Axe_Outside.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __INSIDEAXEMODE__
			Axe_Inside.Update(Array_Board_Stack.top().state, delta, stage);
#endif

#ifdef __COUNTTILENUMBERMODE__
			Tile_Num.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __MERGETILEMODE__
			if (MergeTile_Row1.GetMaxTile(Array_Board_Stack.top().state)> iLowerBound) {
				MergeTile_Row1.Update(Array_Board_Stack.top().state, delta, stage);
				MergeTile_Row2.Update(Array_Board_Stack.top().state, delta, stage);
			}
#endif
#ifdef __CONSTANTVALUEMODE__
			Adjust_Weight += delta;
#endif
#ifdef __OUTSIDERECMODE__
			Rec_Outside.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __OUTSIDELINEMODE__
			Line_Outside.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __INSIDERECMODE__
			Rec_Inside.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __TRIANGLEMODE__
			Triangle.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __BOXATANGLEMODE__
			Box_Angle.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __BOXATMIDDLEMODE__
			Box_Middle.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __BOXATSIDEMODE__
			Box_Side.Update(Array_Board_Stack.top().state, delta, stage);
#endif
#ifdef __MERGECOUNTMODE__
			MergeCount_Row1.Update(Array_Board_Stack.top().state, delta, stage);
			MergeCount_Row2.Update(Array_Board_Stack.top().state, delta, stage);
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
		nextvalue = curValue;
		nextaward = Array_Board_Stack.top().award;
#endif
		Array_Board_Stack.pop();
	}
}
#endif

int Fib2584Ai::SetBoard(int b1[16], const int b2[16])
{
	for (int i = 0; i < 16; i++) {
		b1[i] = b2[i];
	}
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
	Axe_Inside.test();
}

bool Fib2584Ai::isSameBoard( int board1[16], int board2[16])
{
	for (int i = 0 ; i<16 ; i++){
		if(board1[i] != board2[i])
			return false;
	}
	return true;
}

double Fib2584Ai::Scout(int board[16], double alpha, double beta, int depth)
{
	
	/*
	2016/11/21
	alpha beta search
	since the root node is min node, we need to use negamin algorithm
	*/
	int score[30] = {0};
	if (depth == 0)
		return Evaluate(board);
	
	int branch_number = 0;
	int successor_board[30][16] = { 0 };
	// determine the successor board
	if (depth % 2 == 1) {
		// max node
		// move a direction
		for (int i = 0; i < 4; i++) {
			int tmpboard[16] = {0};
			SetBoard(tmpboard, board);
			bool ismoved = false;
			int award = Move.Move(i, tmpboard, ismoved);
			if (ismoved == true) {
				SetBoard(successor_board[branch_number], tmpboard);
				score[branch_number] = award;
				branch_number++;
			}
		}
	}
	else {
		// min node
		// add a random tile in the board
		int curMove = getTileSum(board) % 6;
#ifdef __1113SEARCHMODE__
		if (curMove == 3) {
			for (int i = 0; i < 16; i++) {
				if (board[i] == 0) {
					SetBoard(successor_board[branch_number], board);
					successor_board[branch_number][i] = 3;
					branch_number++;
				}
			}
		}
		else {
			for (int i = 0; i < 16; i++) {
				if (board[i] == 0) {
					SetBoard(successor_board[branch_number], board);
					successor_board[branch_number][i] = 1;
					branch_number++;
				}
			}
		}
#else
		for (int i = 0; i < 16; i++) {
			if (board[i] == 0) {
				SetBoard(successor_board[branch_number], board);
				successor_board[branch_number][i] = 1;
				branch_number++;
				SetBoard(successor_board[branch_number], board);
				successor_board[branch_number][i] = 3;
				branch_number++;

			}
		}
#endif
	}
	if (branch_number == 0) {
		return Evaluate(board);
	}
		

	double min_num = alpha;
	double max_num = FLT_MAX;
	for (int i = 0; i < branch_number; i++) {
		double newvalue = -1 * (Scout(successor_board[i], -1 * std::min(beta, max_num), -1 * min_num, depth - 1) + score[i]);
		if (newvalue < max_num)
			if (min_num == alpha || depth >= ((CUT_OFF_DEPTH*2) - 2))
				max_num = newvalue;
			else
				max_num = -1 * (Scout(successor_board[i], -1 * newvalue, -1 * alpha, depth - 1) + score[i]);
		if (max_num <= alpha)
			return max_num;
		min_num = std::min(beta, max_num) - 1;
	}
	return max_num;
	
}


double Fib2584Ai::alphabeta_Max(int board[16], double alpha, double beta, int depth)
{
	int score[4] = {};
	int branch_number = 0;
	int successor_board[4][16];
	// determine the successor board for max node
	// try four direction
	for (int i = 0; i < 4; i++) {
		int tmpboard[16] = {};
		SetBoard(tmpboard, board);
		bool ismoved = false;
		int award = Move.Move(i, tmpboard, ismoved);
		if (ismoved == true) {
			SetBoard(successor_board[branch_number], tmpboard);
			score[branch_number] = award;
			branch_number++;
		}
	}
	if (branch_number == 0)
		return Evaluate(board) * 0.9;

	double m = alpha;
	for (int i = 0; i < branch_number; i++) {
		double value = alphabeta_Min(successor_board[i], m, beta, depth) + score[i];
		if (value > m)
			m = value;
		if (m >= beta)
			return m;
	}
	return m;
}

double Fib2584Ai::alphabeta_Min(int board[16], double alpha, double beta, int depth)
{
	//if (depth == CUT_OFF_DEPTH) return Evaluate(board);
	if (depth == 0)
		return Evaluate(board);

	int branch_number = 0;
	int successor_board[30][16];
	// determine the successor board for min node
	// try all random tile 
	int curMove = getTileSum(board) % 6;
#ifdef __1113SEARCHMODE__
	if (curMove == 3){
		for (int i = 0; i < 16; i++) {
			if (board[i] == 0) {
				SetBoard(successor_board[branch_number], board);
				successor_board[branch_number][i] = 3;
				branch_number++;
			}
		}
	}
	else {
		for (int i = 0; i < 16; i++) {
			if (board[i] == 0) {
				SetBoard(successor_board[branch_number], board);
				successor_board[branch_number][i] = 1;
				branch_number++;
			}
		}
	}
#else
	for (int i = 0; i < 16; i++) {
		if (board[i] == 0) {
			SetBoard(successor_board[branch_number], board);
			successor_board[branch_number][i] = 1;
			branch_number++;
			SetBoard(successor_board[branch_number], board);
			successor_board[branch_number][i] = 3;
			branch_number++;

		}
	}
#endif

	if (branch_number == 0)
		return Evaluate(board);

	double m = beta;
	for (int i = 0; i < branch_number;) {
#ifdef __1113SEARCHMODE__
		double value = alphabeta_Max(successor_board[i], alpha, m, depth - 1) ;
		i++;
#else
		double value = 0.75*alphabeta_Max(successor_board[i], alpha, m, depth - 1) + 0.25*alphabeta_Max(successor_board[i + 1], alpha, m, depth - 1);
		i = i + 2;
#endif
		if (value < m)
			m = value;
		if (m <= alpha)
			return m;
	}
	return m;
	
}

int Fib2584Ai::getTileSum(int board[16])
{
	int sum = 0;
	for (int i = 0; i < 16; i++)
			sum += fibonacci_seq[ board[i] ];
	return sum;
}