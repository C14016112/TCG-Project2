#ifndef __STATISTIC_H__
#define __STATISTIC_H__

#include <ctime>
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include "GameBoard.h"

using std::cout;
using std::endl;

class Statistic
{
public:
	Statistic();
	void reset();
	void show();
	void increaseOneGame();
	void increaseOneMove();
	void updateScore(int iScore);
	void updateMaxTile(int iTile);
	void setStartTime();
	void setFinishTime();
	void WriteLog(int Round);
private:
	int iMaxTileOverall_;
	int iWinGame_377;
	int iWinGame_610;
	int iWinGame_1597;
	int iWinGame_2584;
	int iWinGame_4181;
	int iWinGame_6765;
	int iWinGame_10946;
	int iWinGame_17711;
	int iMaxScoreOverall_;
	unsigned long long int iTotalScore_;
	int iGameCount_;
	int iMoveCount_;
	clock_t timeDifference_;
};

#endif