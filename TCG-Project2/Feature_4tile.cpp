#include "Feature_4tile.h"

Feature_4tile::Feature_4tile()
{
}

void Feature_4tile::SetParameter(int input_index[4])
{
	iTableSize = iUpperbound*iUpperbound*iUpperbound*iUpperbound;
	for (int i = 0 ; i<4 ; i++){
		for(int j = 0; j<4; j++){
			if(i == 0){
				index[i][j] = input_index[j];
				index[i+4][j] = UpsideDown(index[i][j]);
			}
			else{
				index[i][j] = Rotate(index[i-1][j]);
				index[i+4][j] = Rotate(index[i+4-1][j]);
			}
		}
	}

	Data = new float[iTableSize];
	numerator = new float[iTableSize];
	denumorator = new float[iTableSize];
	for (int i = 0 ; i< iTableSize; i++){
		Data[i] = 0;
		numerator[i] = 0.00000001;
		denumorator[i] = 0.00000001;
	}
}

Feature_4tile::~Feature_4tile()
{
	delete Data;
}

float Feature_4tile::getWeight(int board[4][4]){

	float value = getWeight(board, 0) + getWeight(board, 1) + getWeight(board, 2)
		+ getWeight(board, 3) + getWeight(board, 4) + getWeight(board, 5) 
		+ getWeight(board, 6) + getWeight(board, 7);
	return value;
}


float Feature_4tile::getWeight(int board[4][4], int no)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = board[index[no][0] / 4][index[no][0] % 4]
		+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
		+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4];
	return  Data[position];
}

void Feature_4tile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = board[index[no][0] / 4][index[no][0] % 4]
		+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
		+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4];
	Data[position] = weight;
}

void Feature_4tile::Update(int board[4][4],const float error){
	
	for (int i = 0 ;i<8 ; i++){
		int position = board[ index[i][0] / 4][index[i][0] % 4]
		+ iUpperbound * board[index[i][1] / 4][index[i][1] % 4]
		+ iUpperbound * iUpperbound * board[index[i][2] / 4][index[i][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[i][3] / 4][index[i][3] % 4];
		denumorator[position] += abs(error);
		numerator[position] = abs(numerator[position] + error);
		Data[position] += error * numerator[position] / denumorator[position];
	}
}

void Feature_4tile::ReadFromWeightTable(const char * filename){

	ifstream fin;
	fin.open(filename, ios::in | ios::binary );

	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fin.read(reinterpret_cast<char*>(Data), (iTableSize) * sizeof(float));
	fin.close();



}


void Feature_4tile::WriteToWeightTable(const char * filename)
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



int Feature_4tile::UpsideDown(const int index){
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}


int Feature_4tile::Rotate(const int index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}
