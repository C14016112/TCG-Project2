#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"
#include <map>
#include <omp.h>
#include <stack>

#ifdef __PARALLELMODE__
void PlayGame(Fib2584Ai &, Statistic &, std::stack<Array_Board> &);
#else
void PlayGame(Fib2584Ai &, Statistic &);
#endif

void WriteLog();

int main(int argc, char* argv[])
{
#ifdef __TESTMOVESPPEDMODE__
	MakeMoveTable move;
	double start1, start2, end1, end2;
	double totaltime1 = 0, totaltime2 = 0;
#endif
	WriteLog();
	/*if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}*/
	//int iPlayRounds = atoi(argv[1]);
	int iPlayRounds = PlayRound;
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);
	
	// initialize statistic data
	Statistic statistic;
	statistic.setStartTime();
	// play each round
	std::stack<Array_Board> Array_Board_Stack1;
	std::stack<Array_Board> Array_Board_Stack2;
	std::stack<Array_Board> Array_Board_Stack3;
	for (int i = 1; i <= iPlayRounds; i++){
		printf(" %d ", i);
		if (i % 10 == 0)
			printf("\n");
#ifdef __PARALLELMODE__
#pragma omp parallel sections
	{

#pragma omp section
		{
			PlayGame(ai, statistic, Array_Board_Stack1);
		}
#pragma omp section
		{
			PlayGame(ai, statistic, Array_Board_Stack2);
		}
#pragma omp section
		{
			PlayGame(ai, statistic, Array_Board_Stack3);
		}
	}
#else 
		for (int j = 0; j < 3; j++){
			PlayGame(ai, statistic);
		}
#endif
#ifdef __WRITELOGMODE__
		statistic.WriteLog(i);
#endif
		
		if (i % 10 == 0) {
			printf("----------[ Show  statistic ]----------\n");
			statistic.setFinishTime();
			printf(" Game Count: %d \n", i);
			statistic.show();
			statistic.reset();
			statistic.setStartTime();
		}
		if (i % 50 == 0) {
			ai.WriteToWeightTable();
		}
	}
		
	
	//statistic.setFinishTime();
	//statistic.show();
	//ai.WriteToWeightTable();
	
	return 0;
}

#ifdef __PARALLELMODE__
void PlayGame(Fib2584Ai &ai, Statistic &statistic, std::stack<Array_Board> & arrayboard_stack)
{
	for (int i = 0; i< LogPeriod; i++){
		
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while (!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard, arrayboard_stack);

			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if (originalBoard == gameBoard) {
				cout << "ilegalmove" << endl;
				continue;
			}
				
			statistic.increaseOneMove();
			gameBoard.addRandomTile();
			
		}
		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore, arrayboard_stack);
		statistic.increaseOneGame();

		// update statistic data
		statistic.updateScore(iScore);
		statistic.updateMaxTile(gameBoard.getMaxTile());
	}

}
#else
void PlayGame(Fib2584Ai &ai, Statistic &statistic)
{
	for (int i = 0; i< LogPeriod; i++){
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while (!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard);

			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if (originalBoard == gameBoard) {
				cout << "ilegalmove" << endl;
				continue;
			}
			statistic.increaseOneMove();
			gameBoard.addRandomTile();
		}
		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore);
		statistic.increaseOneGame();

		// update statistic data
		statistic.updateScore(iScore);
		statistic.updateMaxTile(gameBoard.getMaxTile());
	}
}
#endif

void WriteLog()
{
	// show the time and write in the log
	struct tm *ptr;
	time_t lt;
	lt = time(NULL);
	ptr = gmtime(&lt);
	printf(ctime(&lt));

	FILE * pFile;
#ifdef __TRAININGMODE__
	pFile = fopen("Log.txt", "a");
	fprintf(pFile, "Train Mode is open!\n");
#else
	pFile = fopen("Log_Search.txt", "a");
	fprintf(pFile, "Cut-Off-Depth = %d \n", CUT_OFF_DEPTH);
#endif
	fprintf(pFile, ctime(&lt));
	fprintf(pFile, "LogPeriod = %d, Learning Rate = %f\n", LogPeriod * 3, LEARNING_RATE);
#ifdef __TCLAMBDAMODE__
	fprintf(pFile, "Lambda = %f \n", LAMBDA);
#endif
#ifdef __TCLMODE__
	fprintf(pFile, "Tcl Mode is opened.\n");
#endif
#ifdef __SEARCHMODE__ 
	fprintf(pFile, "Search Mode is opened. %d layers. \n", CUT_OFF_DEPTH);
#endif
#ifdef __UCTMODE__
	fprintf(pFile, "UCT Mode is opened. \n");
#endif
#ifdef __TCLAMBDAMODE__ 
	fprintf(pFile, "TC Lambda Mode is opened. \n");
#endif
#ifdef __MULTISTAGE_MAXTILEMODE__
	fprintf(pFile, "Multi-Stage MaxTile Mode is opened.\n");
#endif
#ifdef __MULTISTAGE_TILENUMMODE__
	fprintf(pFile, "Multi_Stage TileNumber Mode is opened. \n");
#endif
#ifdef __PARALLELMODE__
	fprintf(pFile, "Parallel: Parallel Mode is opened\n");
#endif
#ifdef __TCLAMBDAMODE__
	fprintf(pFile, "TC Lambda Mode is opened\n");
#endif
#ifdef __INSIDELINEMODE__
	fprintf(pFile, "Feature: Line Inside is used\n");
#endif
#ifdef __OUTSIDELINEMODE__
	fprintf(pFile, "Feature: Line Outside is used\n");
#endif
#ifdef __OUTSIDEAXEMODE__
	fprintf(pFile, "Feature: Axe Outside is used\n");
#endif
#ifdef __INSIDEAXEMODE__
	fprintf(pFile, "Feature: Axe Inside is used\n");
#endif
#ifdef __OUTSIDERECMODE__
	fprintf(pFile, "Feature: Rec Outside is used\n");
#endif
#ifdef __INSIDERECMODE__
	fprintf(pFile, "Feature: Rec Inside is used\n");
#endif
#ifdef __TRIANGLEMODE__
	fprintf(pFile, "Feature: Triangle is used\n");
#endif
#ifdef __BOXATANGLEMODE__
	fprintf(pFile, "Feature: Box_Angle is used\n");
#endif
#ifdef __BOXATMIDDLEMODE__
	fprintf(pFile, "Feature: Box_Middle is used\n");
#endif
#ifdef __BOXATSIDEMODE__
	fprintf(pFile, "Feature: Box_Side is used\n");
#endif
#ifdef __COUNTTILENUMBERMODE__
	fprintf(pFile, "Feature: Tile Number is used\n");
#endif
#ifdef __MERGETILEMODE__
	fprintf(pFile, "Feature: MergeTile is used\n");
#endif
#ifdef __MERGECOUNTMODE__
	fprintf(pFile, "Feature: MergeCount is used\n");
#endif
	fprintf(pFile, "\n\n");
	fclose(pFile);
}