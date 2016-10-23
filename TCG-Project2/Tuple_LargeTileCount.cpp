#include "Tuple_LargeTileCount.h"


Tuple_LargeTileCount::Tuple_LargeTileCount(void)
{
	normalization_factor = 1;
	iTableSize = pow(4, iRange);
	Data = new float[iTableSize];
#ifdef __TCLMODE__
	numerator = new float[iTableSize];
	denumorator = new float[iTableSize];
#endif
	for (int i = 0 ; i< iTableSize; i++){
		Data[i] = 0;
#ifdef __TCLMODE__
		numerator[i] = 0.00000001;
		denumorator[i] = 0.00000001;
#endif
	}
}


Tuple_LargeTileCount::~Tuple_LargeTileCount(void)
{
	delete Data;
#ifdef __TCLMODE__
	delete numerator;
	delete denumorator;
#endif
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
#ifdef __TCLMODE__
	denumorator[position] += abs(error);
	numerator[position] += error;
	Data[position] += LEARNING_RATE * error * abs(numerator[position]) / denumorator[position] / normalization_factor;
#else
	Data[position] += LEARNING_RATE * error / normalization_factor;
#endif
}
void Tuple_LargeTileCount::ReadFromWeightTable(char * filename)
{
	ifstream fin;
	fin.open(filename, ios::in | ios::binary );
	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}
	fin.read(reinterpret_cast<char*>(Data), (iTableSize) * sizeof(float));
	fin.close();
#ifdef __TCLMODE__
	char name[100] = {0};
	char name2[100] = {0};
	sprintf(name, "%s_coherence_numerator", filename);
	fin.open(name, ios::in | ios::binary );
	if( !fin.is_open()){
		printf("The file '%s' was not open\n", name);
		return ;
	}
	fin.read(reinterpret_cast<char*>(numerator), (iTableSize) * sizeof(float));
	fin.close();
	sprintf(name2, "%s_coherence_denumorator", filename);
	fin.open(name2, ios::in | ios::binary );
	if( !fin.is_open()){
		printf("The file '%s' was not open\n", name2);
		return ;
	}
	fin.read(reinterpret_cast<char*>(denumorator), (iTableSize) * sizeof(float));
	fin.close();
#endif
}

void Tuple_LargeTileCount::WriteToWeightTable(char * filename)
{
	ofstream fout;
#ifdef __TCLMODE__
	char name[100] = {0};
	char name2[100] = {0};
	sprintf(name, "%s_coherence_numerator", filename);
	fout.open(name, ios::out | ios::binary );
	if( !fout.is_open()){
		printf("The file '%s' was not open\n", name);
		return ;
	}
	fout.write(reinterpret_cast<char*>(numerator), (iTableSize) * sizeof(float));
	fout.close();

	sprintf(name2, "%s_coherence_denumorator", filename);
	fout.open(name2, ios::out | ios::binary );
	if( !fout.is_open()){
		printf("The file '%s' was not open\n", name2);
		return ;
	}
	fout.write(reinterpret_cast<char*>(denumorator), (iTableSize) * sizeof(float));
	fout.close();
#endif
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

