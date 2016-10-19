#ifndef __STATISTIC_H__
#define __STATISTIC_H__

#include <ctime>
#include <iostream>

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
private:
	int iMaxTileOverall_;
	int iWinGame_610;
	int iWinGame_2584;
	int iWinGame_6765;
	int iWinGame_10946;
	int iMaxScoreOverall_;
	int iTotalScore_;
	int iGameCount_;
	int iMoveCount_;
	clock_t timeDifference_;
};

#endif