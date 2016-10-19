#include "Fib2584Ai.h"

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
#ifdef __INSIDELINEMODE__
	int line_inside_index[4] = {1, 5, 9, 13};
	Line_Inside.SetParameter(line_inside_index);
	printf("Feature: Line Inside is used\n");
#endif
#ifdef __OUTSIDELINEMODE__
	int line_outside_index[4] = {0, 4, 8, 12};
	Line_Outside.SetParameter(line_outside_index);
	printf("Feature: Line Outside is used\n");
#endif
#ifdef __OUTSIDEAXEMODE__
	int axe_outside_index[6] = {12, 8, 4, 0, 1, 5};
	Axe_Outside.SetParameter(axe_outside_index);
	printf("Feature: Axe Outside is used\n");
#endif
#ifdef __INSIDEAXEMODE__
	int axe_inside_index[6] = {13, 9, 5, 1, 2, 6};
	Axe_Inside.SetParameter(axe_inside_index);
	printf("Feature: Axe Inside is used\n");
#endif
#ifdef __OUTSIDERECMODE__
	int rec_outside_index[6] = {8, 4, 0, 1, 5, 9};
	Rec_Outside.SetParameter(rec_outside_index);
	printf("Feature: Rec Outside is used\n");
#endif
#ifdef __INSIDERECMODE__
	int rec_inside_index[6] = {9, 5, 1, 2, 6, 10};
	Rec_Inside.SetParameter(rec_inside_index);
	printf("Feature: Rec Inside is used\n");
#endif
#ifdef __TRIANGLEMODE__
	int triangle_index[6] = {0, 1, 2, 4, 5, 8};
	Triangle.SetParameter(triangle_index);
	printf("Feature: Triangle is used\n");
#endif
#ifdef __BOXATANGLEMODE__
	int box_angle_index[6] = {0, 1, 4, 5};
	Box_Angle.SetParameter(box_angle_index);
	printf("Feature: Box_Angle is used\n");
#endif
#ifdef __BOXATMIDDLEMODE__
	int box_middle_index[6] = {5, 6, 9, 10};
	Box_Middle.SetParameter(box_middle_index);
	printf("Feature: Box_Middle is used\n");
#endif
#ifdef __BOXATSIDEMODE__
	int box_side_index[6] = {1, 2, 5, 6};
	Box_Side.SetParameter(box_side_index);
	printf("Feature: Box_Side is used\n");
#endif
#ifdef __COUNTTILENUMBERMODE__
	printf("Feature: Tile Number is used\n");
#endif
#ifdef __CONSTANTVALUEMODE__
	Adjust_Weight = 0;
#endif

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
			board[j][k] = GetFibOrder(board[j][k]);
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
		delta = LEARNING_RATE * ( nextaward + nextvalue - Evaluate(Array_Board_Stack.top().state));

		for(int i = 0 ; i < 8; i++){
#ifdef __INSIDELINEMODE__
			float line_inside_newvalue = Line_Inside.getWeight(Array_Board_Stack.top().state, i) + delta;
			Line_Inside.setWeight(Array_Board_Stack.top().state, i, line_inside_newvalue);
#endif
#ifdef __OUTSIDELINEMODE__
			float line_outside_newvalue = Line_Outside.getWeight(Array_Board_Stack.top().state, i) + delta ;
			Line_Outside.setWeight(Array_Board_Stack.top().state, i, line_outside_newvalue);
#endif
#ifdef __OUTSIDEAXEMODE__
			float axe_outside_newvalue = Axe_Outside.getWeight(Array_Board_Stack.top().state, i) + delta;
			Axe_Outside.setWeight(Array_Board_Stack.top().state, i, axe_outside_newvalue);
#endif
#ifdef __INSIDEAXEMODE__
			float axe_inside_newvalue = Axe_Inside.getWeight(Array_Board_Stack.top().state, i) + delta;
			Axe_Inside.setWeight(Array_Board_Stack.top().state, i, axe_inside_newvalue);
#endif
#ifdef __OUTSIDERECMODE__
			float rec_outside_newvalue = Rec_Outside.getWeight(Array_Board_Stack.top().state, i) + delta;
			Rec_Outside.setWeight(Array_Board_Stack.top().state, i, rec_outside_newvalue);
#endif
#ifdef __INSIDERECMODE__
			float rec_inside_newvalue = Rec_Inside.getWeight(Array_Board_Stack.top().state, i) + delta;
			Rec_Inside.setWeight(Array_Board_Stack.top().state, i, rec_inside_newvalue);
#endif
#ifdef __TRIANGLEMODE__
			float triangle_newvalue = Triangle.getWeight(Array_Board_Stack.top().state, i) + delta;
			Triangle.setWeight(Array_Board_Stack.top().state, i, triangle_newvalue);
#endif
#ifdef __BOXATANGLEMODE__
			float box_angle_newvalue = Box_Angle.getWeight(Array_Board_Stack.top().state, i) + delta;
			Box_Angle.setWeight(Array_Board_Stack.top().state, i, box_angle_newvalue);
#endif
#ifdef __BOXATMIDDLEMODE__
			float box_middle_newvalue = Box_Middle.getWeight(Array_Board_Stack.top().state, i) + delta;
			Box_Middle.setWeight(Array_Board_Stack.top().state, i, box_middle_newvalue);
#endif
#ifdef __BOXATSIDEMODE__
			float box_side_newvalue = Box_Side.getWeight(Array_Board_Stack.top().state, i) + delta;
			Box_Side.setWeight(Array_Board_Stack.top().state, i, box_side_newvalue);
#endif
		}
#ifdef __COUNTTILENUMBERMODE__
		float tile_num_newvalue = Tile_Num.getWeight(Array_Board_Stack.top().state) + delta;
		Tile_Num.setWeight(Array_Board_Stack.top().state, tile_num_newvalue);
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
	Line_Inside.WriteWeightTable("Line_Inside_WeightTable2");
#endif
#ifdef __OUTSIDELINEMODE__
	Line_Outside.WriteWeightTable("Line_Outside_WeightTable2");
#endif
#ifdef __OUTSIDEAXEMODE__
	Axe_Outside.WriteWeightTable("Axe_Outside_WeightTable");
#endif
#ifdef __INSIDEAXEMODE__
	Axe_Inside.WriteWeightTable("Axe_Inside_WeightTable");
#endif
#ifdef __OUTSIDERECMODE__
	Rec_Outside.WriteWeightTable("Rec_Outside_WeightTable");
#endif
#ifdef __INSIDERECMODE__
	Rec_Inside.WriteWeightTable("Rec_Inside_WeightTable");
#endif
#ifdef __TRIANGLEMODE__
	Triangle.WriteWeightTable("Triangle_WeightTable");
#endif
#ifdef __BOXATANGLEMODE__
	Box_Angle.WriteWeightTable("Box_Angle_WeightTable2");
#endif
#ifdef __BOXATMIDDLEMODE__
	Box_Middle.WriteWeightTable("Box_Middle_WeightTable2");
#endif
#ifdef __BOXATSIDEMODE__
	Box_Side.WriteWeightTable("Box_Side_WeightTable2");
#endif
#ifdef __COUNTTILENUMBERMODE__
	Tile_Num.WriteToWeightTable("Tile_Num_WeightTable");
#endif
#endif
}

void Fib2584Ai::ReadFromWeightTable()
{
#ifdef __READWEIGHTTABLEMODE__
	printf("Read WeightTable Mode is opened\n");
#ifdef __INSIDELINEMODE__
	Line_Inside.ReadWeightTable("Line_Inside_WeightTable");
#endif
#ifdef __OUTSIDELINEMODE__
	Line_Outside.ReadWeightTable("Line_Outside_WeightTable");
#endif
#ifdef __OUTSIDEAXEMODE__
	Axe_Outside.ReadWeightTable("Axe_Outside_WeightTable");
#endif
#ifdef __INSIDEAXEMODE__
	Axe_Inside.ReadWeightTable("Axe_Inside_WeightTable");
#endif
#ifdef __OUTSIDERECMODE__
	Rec_Outside.ReadWeightTable("Rec_Outside_WeightTable");
#endif
#ifdef __INSIDERECMODE__
	Rec_Inside.ReadWeightTable("Rec_Inside_WeightTable");
#endif
#ifdef __TRIANGLEMODE__
	Triangle.ReadWeightTable("Triangle_WeightTable");
#endif
#ifdef __BOXATANGLEMODE__
	Box_Angle.ReadWeightTable("Box_Angle_WeightTable");
#endif
#ifdef __BOXATMIDDLEMODE__
	Box_Middle.ReadWeightTable("Box_Middle_WeightTable");
#endif
#ifdef __BOXATSIDEMODE__
	Box_Side.ReadWeightTable("Box_Side_WeightTable");
#endif
#ifdef __COUNTTILENUMBERMODE__
	Tile_Num.ReadFromWeightTable("Tile_Num_WeightTable");
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
/**********************************
You can implement any additional functions
you may need.
**********************************/
