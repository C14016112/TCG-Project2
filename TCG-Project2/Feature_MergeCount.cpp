#include "Feature_MergeCount.h"

Feature_MergeCount::Feature_MergeCount()
{
	iTableSize = 16;
	for (int i = 0 ; i< iTableSize; i++){
		Data[i] = 0;
	}
}

Feature_MergeCount::~Feature_MergeCount()
{
}

float Feature_MergeCount::getWeight(int board[4][4])
{
	return  Data[MergeableNumber(board)];
}

void Feature_MergeCount::setWeight(int board[4][4], float weight)
{
	Data[MergeableNumber(board)] = weight;
}

int Feature_MergeCount::MergeableNumber(int board[4][4])
{
	int count = 0;
	for (int i = 0; i<4 ; i++){
		for (int j = 0 ; j<4; j++){
			if(i + 1 < 4){
				if(isMergeable(board[i][j], board[i+1][j]) == true)
					count++;
			}
			if( j + 1 < 4){
				if(isMergeable(board[i][j], board[i][j+1]) == true)
					count++;
			}
		}
	}
	return count;
}
bool Feature_MergeCount::isMergeable(int x, int y)
{
	if(x - y == 1 || y - x == 1)
		return true;
	if( x == y && x == 1)
		return true;
	return false;
}

void Feature_MergeCount::ReadFromWeightTable(const char * filename){

	ifstream fin;
	fin.open(filename, ios::in | ios::binary );

	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fin.read(reinterpret_cast<char*>(Data), (iTableSize) * sizeof(float));
	fin.close();

}


void Feature_MergeCount::WriteToWeightTable(const char * filename)
{
	ofstream fout;
	fout.open(filename, ios::out | ios::binary );

	if( !fout.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fout.write(reinterpret_cast<char*>(Data), (iTableSize) * sizeof(float));
	fout.close();
}
