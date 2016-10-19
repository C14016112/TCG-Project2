#include "Board.h"



int GetFibOrder(int Fibnumber)
{
	switch(Fibnumber){
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 5:
		return 4;
		break;
	case 8:
		return 5;
		break;
	case 13:
		return 6;
		break;
	case 21:
		return 7;
		break;
	case 34:
		return 8;
		break;
	case 55:
		return 9;
		break;
	case 89:
		return 10;
		break;
	case 144:
		return 11;
		break;
	case 233:
		return 12;
		break;
	case 377:
		return 13;
		break;
	case 610:
		return 14;
		break;
	case 987:
		return 15;
		break;
	case 1597:
		return 16;
		break;
	case 2584:
		return 17;
		break;
	case 4181:
		return 18;
		break;
	case 6765:
		return 19;
		break;
	case 10946:
		return 20;
		break;
	case 17711:
		return 21;
		break;
	case 28657:
		return 22;
		break;
	case 46368:
		return 23;
		break;
	case 75025:
		return 24;
		break;
	case 121393:
		return 25;
		break;
	case 196418:
		return 26;
		break;
	case 317811:
		return 27;
		break;
	case 514229:
		return 28;
		break;
	case 832040:
		return 29;
		break;
	case 1346269:
		return 30;
		break;
	case 2178309:
		return 31;
		break;
	default	:
		return -1;
		break;
	}
}

bool isEmpty(int board[4][4])
{
	for (int i = 0 ;i < 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			if(board[i][j] != 0)
				return false;
		}
	}
	return true;
}

bool isFull(int board[4][4])
{
	for (int i = 0 ;i < 4 ; i++){
		for (int j = 0 ; j< 4 ; j++){
			if(board[i][j] == 0)
				return false;
		}
	}
	return true;
}

int GetMaxTile(int board[4][4])
{
	int maxtile = 0;
	for (int i = 0 ; i< 4 ; i++){
		for (int j = 0 ;j<4 ;j++){
			if( maxtile < board[i][j] )
				maxtile = board[i][j];
		}
	}
	return maxtile;
}

int pow(int x, int y)
{
	int value = 1;
	for (int i = 0 ; i < y ; i++)
		value *= x;
	return value;
}