#include "Feature_6tile.h"

Feature_6tile::Feature_6tile()
{
}

void Feature_6tile::SetParameter(int input_index[6])
{
	for (int i = 0 ; i<4 ; i++){
		for(int j = 0; j<6; j++){
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
	Data = new float[pow(iUpperbound, 6)];
	for (int i = 0 ; i< pow(iUpperbound, 6); i++){
		Data[i] = 0;
	}
}

Feature_6tile::~Feature_6tile()
{
	delete Data;
}

float Feature_6tile::getWeight(int board[4][4]){

	float value = 0;
	for (int i = 0 ; i< 8 ; i++){
		value = value + getWeight(board, i);
	}
	return value;
}

float Feature_6tile::getWeight(int board[4][4], int no)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = 0;
	for (int i = 0 ; i< 6 ;i++){
		position += pow(iUpperbound, i) * board[index[no][i] / 4][index[no][i] % 4];
	}
	return Data[position];
}

void Feature_6tile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	
	int position = 0;
	for (int i = 0 ; i< 6 ;i++){
		position += pow(iUpperbound, i) * board[index[no][i] / 4][index[no][i] % 4];
	}
	Data[position] = weight;
}


void Feature_6tile::ReadWeightTable(const char *filename){

	ifstream fin;
	fin.open(filename, ios::in | ios::binary );

	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fin.read(reinterpret_cast<char*>(Data), (pow(iUpperbound, 6)) * sizeof(float));
	fin.close();
}


void Feature_6tile::WriteWeightTable(const char *filename)
{
	ofstream fout;
	fout.open(filename, ios::out | ios::binary );

	if( !fout.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fout.write(reinterpret_cast<char*>(Data), (pow(iUpperbound, 6)) * sizeof(float));
	fout.close();
}



int Feature_6tile::UpsideDown(const int index){
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}


int Feature_6tile::Rotate(const int index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}
