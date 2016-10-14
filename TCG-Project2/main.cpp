#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"
#include "MakeMoveTable.h"

using namespace std;

int main(int argc, char* argv[])
{

	double start, end;
	double start2, end2;
	start = clock();

	bool isRead = false;
	bool isWrite = false;
	/*if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}
	int iPlayRounds = atoi(argv[1]);*/
	
	int iPlayRounds = 100000;
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);

	if(isRead == true)
		ai.ReadWeightTable();

	// initialize statistic data
	Statistic statistic;
	statistic.setStartTime();
	// play each round

	start2 = clock();

	for(int i = 0;i < iPlayRounds;i++) {

		
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while(!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard);
			
			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if(originalBoard == gameBoard)
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
		if (isWrite == true && i > 0 && i % 500001 == 0)
			ai.WriteWeightTable();
		
		if(i % 1000 == 0)
			printf(" %d %d  \n", i, iScore);

		if ( i > 0 && i %  10000 == 0){
			statistic.setFinishTime();
			printf("\n-----------------------------------------------\n");
			statistic.show();
			printf("\n-----------------------------------------------\n");
			statistic.setStartTime();
		}
	}
	end2 = clock();

	printf("\nThe finish time without reading and writing data is : %f \n", (end2 - start2 ) / CLOCKS_PER_SEC);
	statistic.setFinishTime();

	// output statistic data
	
	statistic.show();

	if (isWrite == true)
		ai.WriteWeightTable();

	end = clock();

	printf("The finish time including reading and writing data is : %f \n", (end - start )/CLOCKS_PER_SEC );
	return 0;
}