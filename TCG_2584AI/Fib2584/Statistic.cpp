#include "Statistic.h"

Statistic::Statistic()
{
	reset();
}

void Statistic::reset()
{
	iMaxTileOverall_ = 0;
	iWinGame_610 = 0;
	iWinGame_2584 = 0;
	iWinGame_6765 = 0;
	iWinGame_10946 = 0;
	iWinGame_17711 = 0;
	iWinGame_28657 = 0;
	iWinGame_46368 = 0;
	iMaxScoreOverall_ = 0;
	iTotalScore_ = 0;
	iGameCount_ = 0;
	iMoveCount_ = 0;
	timeDifference_ = 0;
}

void Statistic::show()
{
	cout << "Win rate(610)  : " << iWinGame_610 / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Win rate(2584) : " << iWinGame_2584 / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Win rate(6765) : " << iWinGame_6765 / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Win rate(10946): " << iWinGame_10946 / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Win rate(17711): " << iWinGame_17711 / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Win rate(28657): " << iWinGame_28657 / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Win rate(46368): " << iWinGame_46368 / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Max score: " << iMaxScoreOverall_ << endl;
	cout << "Average score: " << iTotalScore_ / iGameCount_ << endl;
	cout << "Max tile: " << iMaxTileOverall_ << endl;
	double dTotalTime = timeDifference_ / (double)CLOCKS_PER_SEC;
	cout << dTotalTime / (double)iMoveCount_ << " sec/move" << endl;
	cout << iMoveCount_ / dTotalTime << " moves/sec" << endl;
	cout << "Total Time: " << dTotalTime << endl;
	cout << "Total Count: " << iGameCount_ << endl;
}

void Statistic::increaseOneGame()
{
	iGameCount_++;
}

void Statistic::increaseOneMove()
{
	iMoveCount_++;
}

void Statistic::updateScore(int iScore)
{
	iTotalScore_ += iScore;
	iMaxScoreOverall_ = iScore > iMaxScoreOverall_?iScore:iMaxScoreOverall_;
}

void Statistic::updateMaxTile(int iTile)
{
	iWinGame_610 += iTile >= 610?1:0;
	iWinGame_2584 += iTile >= 2584?1:0;
	iWinGame_6765 += iTile >= 6765?1:0;
	iWinGame_10946 += iTile >= 10946?1:0;
	iWinGame_17711 += iTile >= 17711 ? 1 : 0;
	iWinGame_28657 += iTile >= 28657 ? 1 : 0;
	iWinGame_46368 += iTile >= 46368 ? 1 : 0;
	iMaxTileOverall_ = iTile > iMaxTileOverall_?iTile:iMaxTileOverall_;
}

void Statistic::setStartTime()
{
	timeDifference_ -= clock();
}

void Statistic::setFinishTime()
{
	timeDifference_ += clock();
}

void Statistic::WriteLog(int Round)
{
#ifdef __TRAININGMODE__
	FILE * pFile;
	pFile = fopen ("Log.txt","a");
	fprintf (pFile, "Round: %d, MaxTile = %d, MaxScore = %d, Average Score = %2.2f\n"
		, Round, iMaxTileOverall_, iMaxScoreOverall_, iTotalScore_*1. / iGameCount_);
	fprintf( pFile, "610: %2.2f%%, 2584: %2.2f%%, 6765: %2.2f%%, 10946: %2.2f%%\n17711: %2.2f%%, 28657: %2.2f%%, 46368: %2.2f%% \n\n",
		iWinGame_610 / (double)iGameCount_*100.0, iWinGame_2584 / (double)iGameCount_ * 100.0,
		iWinGame_6765 / (double)iGameCount_ * 100.0, iWinGame_10946 / (double)iGameCount_ * 100.0,
		iWinGame_17711 / (double)iGameCount_ * 100.0, iWinGame_28657 / (double)iGameCount_ * 100.0, 
		iWinGame_46368 / (double)iGameCount_ * 100.0);

	fclose (pFile);

	pFile = fopen("Log.csv", "a");
	fprintf(pFile, "%d, %d, %d, %f, %2.2f%%, %2.2f%%, %2.2f%%, %2.2f%%, %2.2f%%, %2.2f%%, %2.2f%%\n", Round, iMaxTileOverall_,
		iMaxScoreOverall_,  iTotalScore_ * 1. / iGameCount_, iWinGame_610 / (double)iGameCount_*100.0,
		iWinGame_2584 / (double)iGameCount_ * 100.0,iWinGame_6765 / (double)iGameCount_ * 100.0, iWinGame_10946 / (double)iGameCount_ * 100.0, 
		iWinGame_17711 / (double)iGameCount_ * 100.0, iWinGame_28657 / (double)iGameCount_ * 100.0,
		iWinGame_46368 / (double)iGameCount_ * 100.0);
	fclose(pFile);
#else
	FILE * pFile;
	pFile = fopen("Log_Search.txt", "a");
	fprintf(pFile, "Round: %d, MaxTile = %d, MaxScore = %d, Average Score = %2.2f\n"
		, Round, iMaxTileOverall_, iMaxScoreOverall_, iTotalScore_*1. / iGameCount_);
	fprintf(pFile, "610: %2.2f%%, 2584: %2.2f%%, 6765: %2.2f%%, 10946: %2.2f%%\n17711: %2.2f%%, 28657: %2.2f%%, 46368: %2.2f%% \n\n",
		iWinGame_610 / (double)iGameCount_*100.0, iWinGame_2584 / (double)iGameCount_ * 100.0,
		iWinGame_6765 / (double)iGameCount_ * 100.0, iWinGame_10946 / (double)iGameCount_ * 100.0,
		iWinGame_17711 / (double)iGameCount_ * 100.0, iWinGame_28657 / (double)iGameCount_ * 100.0,
		iWinGame_46368 / (double)iGameCount_ * 100.0);

	fclose(pFile);
#endif
}