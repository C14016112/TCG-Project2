#include "Feature_MergeTile.h"

Feature_MergeTile::Feature_MergeTile()
{
	
}

Feature_MergeTile::~Feature_MergeTile()
{
	delete Data;
}

void Feature_MergeTile::SetParameter(int inputindex[4])
{
	iTableSize = 1;
	for (int i = 0 ;i < iRange; i++)
		iTableSize *= 3;
	Data = new float[iTableSize];
	for (int i = 0 ; i< iTableSize; i++){
		Data[i] = 0;
	}

	index[0][0] = inputindex[0];
	index[0][1] = inputindex[1];
	index[0][2] = inputindex[2];
	index[0][3] = inputindex[3];
	for (int i = 1 ; i<4 ; i++){
		for(int j = 0; j<4; j++){
			index[i][j] = Rotate(index[i-1][j]);
		}
	}
}

float Feature_MergeTile::getWeight(int board[4][4]){

	float value = getWeight(board, 0) + getWeight(board, 1) + getWeight(board, 2)
		+ getWeight(board, 3);
	return value;
}


float Feature_MergeTile::getWeight(int board[4][4], int no)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 4);
#endif
	return  Data[GetMergeNumber(board, no)];
}

void Feature_MergeTile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 4);
#endif
	Data[GetMergeNumber(board, no)] = weight;
}

void Feature_MergeTile::Update(int board[4][4], const float error)
{
	for (int i = 0 ;i<4 ; i++)
		Data[GetMergeNumber(board,i)] += error;
}
int Feature_MergeTile::GetMergeNumber(int board[4][4], int no)
{
	int position = 0;
	int tile_count[iRange] = {};
	for (int i = 0 ; i< 3 ; i++){
		if( board[index[no][i] / 4][index[no][i] % 4] == board[index[no][i+1] / 4][index[no][1+1] % 4] + 1 || 
			board[index[no][i] / 4][index[no][i] % 4] == board[index[no][i+1] / 4][index[no][i+1] % 4] - 1)
		{
			if( board[index[no][i] / 4][index[no][i] % 4] > iLowerBound)
				tile_count[ board[index[no][i] / 4][index[no][i] % 4] - iLowerBound ]++;
			if( board[index[no][i+1] / 4][index[no][i+1] % 4] > iLowerBound)
				tile_count[ board[index[no][i+1] / 4][index[no][i+1] % 4] - iLowerBound ]++;
		}
	}
	for(int i = 0 ;i<iRange ;i++){
		position += pow(3, i) * tile_count[i];
	}
	return position;
}
void Feature_MergeTile::ReadFromWeightTable(const char * filename){

	ifstream fin;
	fin.open(filename, ios::in | ios::binary );

	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fin.read(reinterpret_cast<char*>(Data), (iTableSize) * sizeof(float));
	fin.close();



}


void Feature_MergeTile::WriteToWeightTable(const char * filename)
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



int Feature_MergeTile::UpsideDown(const int index){
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}


int Feature_MergeTile::Rotate(const int index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}

int Feature_MergeTile::pow(int x, int y){
	int value = 1;
	for (int i = 0 ; i<y ; i++)
		value *= x;
	return  value;
}