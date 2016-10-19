#include "GameBoard_Extend.h"

const int GameBoard_Extend::fibonacci_[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
Random GameBoard_Extend::random_;

GameBoard_Extend::GameBoard_Extend():
board_(0)
{
}

void GameBoard_Extend::initialize()
{
	board_ = 0;
	addRandomTile();
	addRandomTile();
}

int GameBoard_Extend::move(MoveDirection moveDirection)
{
	BitBoard newBoard = 0;
	int score = 0;
	if(moveDirection == MOVE_UP || moveDirection == MOVE_DOWN) {
		for(int i = 0;i < 4;i++) {
			BitBoard tempColumn = 0;
			tempColumn = getColumn(i);
			newBoard |= restoreColumn(MoveTable::move_table.row_move_table_[moveDirection == MOVE_DOWN][tempColumn], i);
			score += MoveTable::move_table.row_move_score_table_[moveDirection == MOVE_DOWN][tempColumn];
		}
	}
	else {
		for(int i = 0;i < 4;i++) {
			BitBoard tempRow = 0;
			tempRow = getRow(i);
			newBoard |= restoreRow(MoveTable::move_table.row_move_table_[moveDirection == MOVE_RIGHT][tempRow], i);
			score += MoveTable::move_table.row_move_score_table_[moveDirection == MOVE_RIGHT][tempRow];
		}
	}
	board_ = newBoard;
	return score;
}

void GameBoard_Extend::addRandomTile()
{
	int oneTileRate = 6;
	int emptyTileNum = countEmptyTile();
	int randomTileLocation = random_.get_rand_num() % emptyTileNum;
	BitBoard randomTile = (random_.get_rand_num() % 8 < oneTileRate)?0x1:0x3;
	int count = 0;
	for(BitBoard tileMask = 0x1f;tileMask != 0;tileMask <<= 5, randomTile <<= 5) {
		if((board_ & tileMask) != 0)
			continue;
		if(count == randomTileLocation) {
			board_ |= randomTile;
			break;
		}
		count++;
	}
}

int GameBoard_Extend::countEmptyTile()
{
	int count = 0;
	BitBoard tileMask = 0x1f;
	for(;tileMask != 0;tileMask <<= 5) {
		if((board_ & tileMask) == 0)
			count++;
	}
	return count;
}

bool GameBoard_Extend::terminated()
{
	bool movable = false;
	BitBoard tempColumn;
	BitBoard tempRow;
	for(int i = 0;i < 4;i++) {
		tempColumn = getColumn(i);
		movable |= MoveTable::move_table.row_can_move_[0][tempColumn];
		movable |= MoveTable::move_table.row_can_move_[1][tempColumn];
		tempRow = getRow(i);
		movable |= MoveTable::move_table.row_can_move_[0][tempRow];
		movable |= MoveTable::move_table.row_can_move_[1][tempRow];
		if(movable)
			break;
	}
	return !movable;
}

void GameBoard_Extend::getArrayBoard(int board[4][4])
{
	BitBoard tempBoard = board_;
	for(int i = 0;i < 16;i++) {
		board[3 - (i / 4)][3 - (i % 4)] = fibonacci_[(int)(tempBoard & 0x1f)];
		tempBoard = tempBoard >> 5;
	}
}

int GameBoard_Extend::getMaxTile()
{
	BitBoard countBoard = board_;
	int max_tile = 0;
	for(int i = 0;i < 16;i++) {
		if((countBoard & 0x1f) > max_tile)
			max_tile = countBoard & 0x1f;
		countBoard >>= 5;
	}
	return fibonacci_[max_tile];
}

BitBoard GameBoard_Extend::getRow( int row )
{
	return board_ >> (row * 20) & 0xfffff;
}

BitBoard GameBoard_Extend::getColumn( int column )
{
	BitBoard tempBoard = board_ >> (column * 5) & BitBoard(0x0001, 0xf0001f0001f0001f);
	return (tempBoard & BitBoard(0x0001, 0xf000000000000000)) >> 45 |
		(tempBoard & BitBoard(0x0000, 0x00001f0000000000)) >> 30 |
		(tempBoard & BitBoard(0x0000, 0x0000000001f00000)) >> 15 |
		(tempBoard & BitBoard(0x0000, 0x000000000000001f));
}

BitBoard GameBoard_Extend::restoreRow( BitBoard rowBits, int row )
{
	return rowBits << (row * 20);
}

BitBoard GameBoard_Extend::restoreColumn( BitBoard columnBits, int column )
{
	return ((columnBits & BitBoard(0xf8000)) << 45 |
		(columnBits & BitBoard(0x07c00)) << 30 |
		(columnBits & BitBoard(0x003e0)) << 15 |
		(columnBits & BitBoard(0x0001f)) ) << (column * 5);
}

BitBoard GameBoard_Extend::GetBitBoard()
{
	return board_;
}

int GameBoard_Extend::getTile( int row, int column )
{
	int tile = ((board_ >> (row * 20) & 0xfffff) >> (column * 5)) & 0x1f;
	return fibonacci_[tile];
}

void GameBoard_Extend::showBoard()
{
	for(int row = 3;row >= 0;row--) {
		for(int column = 3;column >= 0;column--)
			cout << dec << getTile(row, column) << "\t";
		cout << "\n";
	}
}

bool GameBoard_Extend::operator==(GameBoard_Extend gameBoard)
{
	return board_ == gameBoard.board_;
}

void GameBoard_Extend::setBitBoard(const BitBoard bitboard)
{
	board_ = bitboard;
}

void GameBoard_Extend::setBitBoard(int arrayboard[4][4])
{
	board_ = TransformArrayBoardToBitBoard(arrayboard);
}

BitBoard GameBoard_Extend::TransformArrayBoardToBitBoard(int arrayboard[4][4])
{

	// first, transform the number of array board to order of fibonacci number
	// example, 89 -> F_10
	int fibonacciboard[4][4] = {};
	for (int i = 0 ;i < 4 ; i++){
		for(int j = 0 ; j< 4 ; j++){
			fibonacciboard[i][j] = GetFibOrder(arrayboard[i][j]);
		}
	}

	BitBoard tmpboard = 0;
	for (int i = 15 ;i >= 0 ; i--){
		tmpboard = tmpboard << 5;
		tmpboard |= BitBoard(fibonacciboard[3 - (i / 4)][ 3 - ( i % 4)]);
	}
	return tmpboard;
}

int GameBoard_Extend::GetFibOrder(int Fibnumber)
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