#include "Tuple_LargeTileCount.h"


Tuple_LargeTileCount::Tuple_LargeTileCount(void)
{
	normalization_factor = 1;
	iTableSize = pow(4, iRange);
	Data = new float[iTableSize];
	numerator = new float[iTableSize];
	denumorator = new float[iTableSize];
	for (int i = 0 ; i< iTableSize; i++){
		Data[i] = 0;
		numerator[i] = 0.00000001;
		denumorator[i] = 0.00000001;
	}
}


Tuple_LargeTileCount::~Tuple_LargeTileCount(void)
{
	delete Data;
	delete numerator;
	delete denumorator;
}

float Tuple_LargeTileCount::getWeight(int board[4][4])
{
	return Data[getPosition(board)];
}

void Tuple_LargeTileCount::setWeight(int board[4][4], const float weight)
{
	Data[getPosition(board)] = weight;
}

int Tuple_LargeTileCount::getPosition(int board[4][4])
{
	return 0;
	int tile_count[iRange] = {};
	for (int i = 0 ; i < 4; i++){
		for (int j = 0 ; j< 4 ;j ++){
			if(board[i][j] >= iLowerBound){
				tile_count[board[i][j] - iLowerBound]++;
			}
		}
	}
	int position = 0;
	for(int i = 0 ; i< iRange; i++){
		position += pow(12, i) * std::min(tile_count[i],4) ;
	}
	return position;
}

void Tuple_LargeTileCount::Update(int board[4][4], const float error)
{
	int position = getPosition(board);
	denumorator[position] += abs(error);
	numerator[position] += error;
	Data[position] += LEARNING_RATE * error * abs(numerator[position]) / denumorator[position] / normalization_factor;
}
void Tuple_LargeTileCount::ReadFromWeightTable(char * filename)
{
	{
		ifstream fin;
		fin.open(filename, ios::in | ios::binary );

		if( !fin.is_open()){
			printf("The file '%s' was not open\n", filename);
			return ;
		}

		fin.read(reinterpret_cast<char*>(Data), (iTableSize) * sizeof(float));
		fin.close();
	}
}

void Tuple_LargeTileCount::WriteToWeightTable(char * filename)
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

int Tuple_LargeTileCount::pow(int x, int y)
{
	int value = 1;
	for (int i = 0; i< y ; i++)
		value *= x;
	return value;
}

