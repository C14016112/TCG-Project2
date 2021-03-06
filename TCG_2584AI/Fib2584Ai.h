#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/MoveDirection.h"
#include "Tuple_4tile.h"
#include "Tuple_6tile.h"
#include "Tuple_LargeTileCount.h"
#include "Tuple_MergeTile.h"
#include "Tuple_MergeCount.h"
#include <stack>
#include <map>
#include "Mode_Definition.h"
#include "float.h"
struct Array_Board{
	int state[16];
	int award;
};

class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
#ifdef __PARALLELMODE__
	MoveDirection generateMove(int board[4][4], std::stack<Array_Board> &);
	void gameOver(int board[4][4], int iScore, std::stack<Array_Board> &);
	void gameOver(std::stack<Array_Board> &);
	void Learning(std::stack<Array_Board> &);
#else
	MoveDirection generateMove(int board[4][4]);
	void gameOver(int board[4][4], int iScore);
	void Learning();
#endif
	int generateEvilMove(int board[4][4]);
	MoveDirection FindBestDirection(int board[16]);
	float Evaluate(int board[16]);
	void WriteToWeightTable();
	void ReadFromWeightTable();
	int SetBoard(int board[16], const int board2[16]);
	double Scout(int board[16], double alpha, double beta, int depth);
	double alphabeta_Max(int board[16], double alpha, double beta, int depth);
	double alphabeta_Min(int board[16], double alpha, double beta, int depth);
	int getTileSum(int board[16]);
private:
#ifdef __INSIDELINEMODE__
	Tuple_4tile Line_Inside;
#endif
#ifdef __OUTSIDELINEMODE__
	Tuple_4tile Line_Outside;
#endif
#ifdef __OUTSIDEAXEMODE__
	Tuple_6tile Axe_Outside;
#endif
#ifdef __INSIDEAXEMODE__
	Tuple_6tile Axe_Inside;
#endif
#ifdef __OUTSIDERECMODE__
	Tuple_6tile Rec_Outside;
#endif
#ifdef __INSIDERECMODE__
	Tuple_6tile Rec_Inside;
#endif
#ifdef __TRIANGLEMODE__
	Tuple_6tile Triangle;
#endif
#ifdef __BOXATANGLEMODE__
	Tuple_4tile Box_Angle;
#endif
#ifdef __BOXATMIDDLEMODE__
	Tuple_4tile Box_Middle;
#endif
#ifdef __BOXATSIDEMODE__
	Tuple_4tile Box_Side;
#endif
#ifdef __COUNTTILENUMBERMODE__
	Tuple_LargeTileCount Tile_Num;
#endif
#ifdef __MERGETILEMODE__
	Tuple_MergeTile MergeTile_Row1;
	Tuple_MergeTile MergeTile_Row2;
#endif
#ifdef __MERGECOUNTMODE__
	Tuple_MergeCount MergeCount_Row1;
	Tuple_MergeCount MergeCount_Row2;
#endif
#ifdef __CONSTANTVALUEMODE__
	float Adjust_Weight;
#endif
	int icurRound;
	MakeMoveTable Move;
	std::stack<Array_Board> Array_Board_Stack;
	bool isSameBoard(int board1[16], int board2[16]);
	std::map<int, int> mapFibOrder;  
	int feature_number ;
};

#endif