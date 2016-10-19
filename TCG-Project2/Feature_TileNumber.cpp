#include "Feature_TileNumber.h"


Feature_TileNumber::Feature_TileNumber(void)
{
	Data = new float[pow(12, iUpperbound - iLowerBound)];
	for (int i = 0 ; i< pow(12, iUpperbound - iLowerBound); i++)
		Data[i] = 0;
}


Feature_TileNumber::~Feature_TileNumber(void)
{
	delete Data;
}

float Feature_TileNumber::getWeight(int board[4][4])
{
	int tile_count[iUpperbound - iLowerBound] = {};
	for (int i = 0 ; i < 4; i++){
		for (int j = 0 ; j< 4 ;j ++){
			if(board[i][j] > iLowerBound){
				tile_count[board[i][j] - iLowerBound]++;
			}
		}
	}
	int position = 0;
	for(int i = 0 ; i< iUpperbound - iLowerBound; i++){
		position += pow(12, i) * tile_count[i] ;
	}
	return Data[position];
}

void Feature_TileNumber::setWeight(int board[4][4], const float weight)
{
	int tile_count[iUpperbound - iLowerBound] = {};
	for (int i = 0 ; i < 4; i++){
		for (int j = 0 ; j< 4 ;j ++){
			if(board[i][j] > iLowerBound){
				tile_count[board[i][j] - iLowerBound]++;
			}
		}
	}
	int position = 0;
	for(int i = 0 ; i< iUpperbound - iLowerBound; i++){
		position += pow(12, i) * tile_count[i] ;
	}
	Data[position] = weight;
}
void Feature_TileNumber::ReadFromWeightTable(char * filename)
{
	{
		ifstream fin;
		fin.open(filename, ios::in | ios::binary );

		if( !fin.is_open()){
			printf("The file '%s' was not open\n", filename);
			return ;
		}

		fin.read(reinterpret_cast<char*>(Data), (pow(12, iUpperbound - iLowerBound)) * sizeof(float));
		fin.close();
	}
}

void Feature_TileNumber::WriteToWeightTable(char * filename)
{
	ofstream fout;
	fout.open(filename, ios::out | ios::binary );

	if( !fout.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fout.write(reinterpret_cast<char*>(Data), (pow(12, iUpperbound - iLowerBound)) * sizeof(float));
	fout.close();
}

int Feature_TileNumber::pow(int x, int y)
{
	int value = 1;
	for (int i = 0; i< y ; i++)
		value *= x;
	return value;
}

