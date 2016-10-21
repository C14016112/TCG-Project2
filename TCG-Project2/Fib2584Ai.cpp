#include "Fib2584Ai.h"

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	feature_number = 0;
	srand(time(NULL));
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


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	return FindBestDirection(board);
}

MoveDirection Fib2584Ai::FindBestDirection(int board[4][4])
{

	for (int j = 0 ; j<4 ;j ++){
		for (int k = 0 ;k<4 ;k++){
			board[j][k] = mapFibOrder[(board[j][k])];
		}
	}
	Array_Board b_struct;
	MoveDirection next_dir = static_cast<MoveDirection>(0);
	float evaluation[4] = {};
	int award[4] = {};
	int movedboard[4][4][4] = {};
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ; j<4 ;j ++){
			for (int k = 0 ;k<4 ;k++){
				movedboard[i][j][k] = board[j][k];
			}
		}
		award[i] = Move.Move(i, movedboard[i]);

		if(isSameBoard(movedboard[i], board) == true)
			award[i] = NOMOVEPENALTY;
		evaluation[i] = Evaluate(movedboard[i]);
		if( award[i] + evaluation[i] >= award[next_dir] + evaluation[next_dir])
			next_dir = static_cast<MoveDirection>(i);
	}
	for (int i = 0 ; i<4 ; i++){
		for (int j = 0 ; j<4 ; j++){
			b_struct.state[i][j] = movedboard[next_dir][i][j];
		}
	}
	b_struct.award = award[next_dir];
	Array_Board_Stack.push(b_struct);
	return next_dir;


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

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
#ifdef __TRAININGMODE__
	Learning();
#endif
	return;
}

void Fib2584Ai::Learning()
{
	int nextaward = 0;
	int nextvalue = 0;
	float delta = 0;

	while(Array_Board_Stack.empty() == false){
		delta = (nextaward + nextvalue - Evaluate(Array_Board_Stack.top().state)) / feature_number;

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
			Box_Middle.setWeight(Array_Board_Stack.top().state, i, box_angle_newvalue);
#endif
#ifdef __BOXATSIDEMODE__
			Box_Side.setWeight(Array_Board_Stack.top().state, i, box_middle_newvalue);
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
		nextvalue = Evaluate(Array_Board_Stack.top().state);
		nextaward = Array_Board_Stack.top().award;
		Array_Board_Stack.pop();
	}
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
