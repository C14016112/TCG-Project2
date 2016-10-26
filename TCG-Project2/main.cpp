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

int main(int argc, char* argv[])
{
#ifdef __TESTMOVESPPEDMODE__
	MakeMoveTable move;
	double start1, start2, end1, end2;
	double totaltime1 = 0, totaltime2 = 0;
#endif
	// show the time and write in the log
	struct tm *ptr;
	time_t lt;
	lt =time(NULL);
	ptr=gmtime(&lt);
	printf(ctime(&lt));

	FILE * pFile;
	pFile = fopen ("Log.txt","a");
	fprintf(pFile, ctime(&lt));
	fprintf(pFile, "LogPeriod = %d\n\n", LogPeriod*3);
	fclose(pFile);
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
	for (int i = 1; i <= 3000; i++){
		printf(" %d \n", i);
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
	for (int i = 0; i< PlayRound; i++){
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while (!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard, arrayboard_stack);

			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if (originalBoard == gameBoard)
				continue;
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
	for (int i = 0; i< PlayRound; i++){
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while (!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard);

			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if (originalBoard == gameBoard)
				continue;
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