#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"
#include <map>

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
	fprintf(pFile, "LogPeriod = %d\n", LogPeriod);
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
	for(int i = 0;i < iPlayRounds;i++) {
		if(i > 0 && i % 1000 == 0)
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

#ifdef __TESTMOVESPPEDMODE__
			start1 = clock();
			originalBoard.move(moveDirection);
			end1 = clock();
			totaltime1 += end1 - start1;
			start2 = clock();
			move.Move(1, arrayBoard);
			end2 = clock();
			totaltime2 += end2 - start2;*/
#endif
		}
		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore);
		statistic.increaseOneGame();

		// update statistic data
		statistic.updateScore(iScore);
		statistic.updateMaxTile(gameBoard.getMaxTile());


		if (i % 10000== 0 && i != 0) {
			printf("----------[ Show  statistic ]----------\n");
			statistic.setFinishTime();
			printf(" Game Count: %d \n", i);
			statistic.show();
			statistic.reset();
			statistic.setStartTime();
#ifdef __TESTMOVESPEEDMODE__
			printf("The move time of framework: %f\n", totaltime1 / CLOCKS_PER_SEC);
			printf("The move time of selftable: %f\n", totaltime2 / CLOCKS_PER_SEC);
			printf("framework / selftable = %f\n", totaltime1/totaltime2);
			printf("---------------------------------------\n" );
			getchar();
#endif
			if (i % 50000 == 0 && i != 0) {
				ai.WriteToWeightTable();
			}
		}
#ifdef __WRITELOGMODE__
		if(i % LogPeriod == 0 && i > 0)
			statistic.WriteLog(i);
#endif
	}
	statistic.setFinishTime();
	
	ai.WriteToWeightTable();
	// output statistic data
	statistic.show();
	//printf(" the difference is %d ", diff);
	system("pause");
	return 0;
}