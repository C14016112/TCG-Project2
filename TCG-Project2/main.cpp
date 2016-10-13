#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"

using namespace std;

int main(int argc, char* argv[])
{
	double start, end;

	start = clock();

	bool isRead = true;
	bool isWrite = true;
	/*if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}
	int iPlayRounds = atoi(argv[1]);*/
	
		
	int iPlayRounds = 1000;
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);

	if(isRead == true)
		ai.ReadWeightTable();

	// initialize statistic data
	Statistic statistic;
	statistic.setStartTime();
	// play each round
	for(int i = 0;i < iPlayRounds;i++) {

		if ( i > 0 && i % ( iPlayRounds / 10 ) == 0)
			printf(" %d \n", i);
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
		if (isWrite == true && i > 0 && i % 500000 == 0)
			ai.WriteWeightTable();
		if(i > 0 && i % 100000 == 0 ){
			statistic.show();
			printf("\n");
		}
	}
	statistic.setFinishTime();

	// output statistic data
	
	statistic.show();

	if (isWrite == true)
		ai.WriteWeightTable();

	end = clock();

	printf(" Running time is %f \n", (end - start )/CLOCKS_PER_SEC );
	system("pause");
	return 0;
}