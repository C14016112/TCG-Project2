#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/MoveDirection.h"
#include "Feature_4tile.h"
#include "Feature_6tile.h"
#include "Feature_TileNumber.h"
#include "Feature_MergeTile.h"
#include "Feature_MergeCount.h"
#include <stack>
#include "GameBoard_Extend.h"
#include <map>
#include "Mode_Definition.h"


struct Array_Board{
	int state[4][4];
	int award;
};

class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	MoveDirection FindBestDirection(int board[4][4]);
	float Evaluate(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);
	void Learning();
	void WriteToWeightTable();
	void ReadFromWeightTable();
	void WriteLog();
	int GetMaxTile(int board[4][4]);
private:
#ifdef __INSIDELINEMODE__
	Feature_4tile Line_Inside;
#endif
#ifdef __OUTSIDELINEMODE__
	Feature_4tile Line_Outside;
#endif
#ifdef __OUTSIDEAXEMODE__
	Feature_6tile Axe_Outside;
#endif
#ifdef __INSIDEAXEMODE__
	Feature_6tile Axe_Inside;
#endif
#ifdef __OUTSIDERECMODE__
	Feature_6tile Rec_Outside;
#endif
#ifdef __INSIDERECMODE__
	Feature_6tile Rec_Inside;
#endif
#ifdef __TRIANGLEMODE__
	Feature_6tile Triangle;
#endif
#ifdef __BOXATANGLEMODE__
	Feature_4tile Box_Angle;
#endif
#ifdef __BOXATMIDDLEMODE__
	Feature_4tile Box_Middle;
#endif
#ifdef __BOXATSIDEMODE__
	Feature_4tile Box_Side;
#endif
#ifdef __COUNTTILENUMBERMODE__
	Feature_TileNumber Tile_Num;
#endif
#ifdef __MERGETILEMODE__
	Feature_MergeTile MergeTile_Row1;
	Feature_MergeTile MergeTile_Row2;
#endif
#ifdef __MERGECOUNTMODE__
	Feature_MergeCount MergeCount_Row1;
	Feature_MergeCount MergeCount_Row2;
#endif
#ifdef __CONSTANTVALUEMODE__
	float Adjust_Weight;
#endif
	MakeMoveTable Move;
	std::stack<Array_Board> Array_Board_Stack;
	bool isSameBoard(int board1[4][4], int board2[4][4]);
	std::map<int, int> mapFibOrder;  
	int feature_number ;
};

#endif