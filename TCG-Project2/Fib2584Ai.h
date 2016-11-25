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
#ifdef __PARALLELMODE__
	MoveDirection generateMove(int board[4][4], std::stack<Array_Board> &);
	void gameOver(int board[4][4], int iScore, std::stack<Array_Board> &);
	void Learning(std::stack<Array_Board> &);
#else
	MoveDirection generateMove(int board[4][4]);
	void gameOver(int board[4][4], int iScore);
	void Learning();
#endif
	MoveDirection FindBestDirection(int board[4][4]);
	float Evaluate(int board[4][4]);
	void WriteToWeightTable();
	void ReadFromWeightTable();
	void WriteLog();
	int GetMaxTile(int board[4][4]);
	int SetBoard(int board[4][4], const int board2[4][4]);
	int Simulation(int board[4][4], Array_Board & b_struct);
	double PlayOut(int board[4][4], int deep);
	bool AddRandomTile(int board[4][4]);
	double ABSearch(int board[4][4], double alpha, double beta, int depth);
	double alphabeta_Max(int board[4][4], double alpha, double beta, int depth);
	double alphabeta_Min(int board[4][4], double alpha, double beta, int depth);
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
	MakeMoveTable Move;
	std::stack<Array_Board> Array_Board_Stack;
	bool isSameBoard(int board1[4][4], int board2[4][4]);
	std::map<int, int> mapFibOrder;  
	int feature_number ;
};

#endif