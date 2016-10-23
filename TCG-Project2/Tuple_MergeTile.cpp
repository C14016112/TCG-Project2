#include "Tuple_MergeTile.h"

Tuple_MergeTile::Tuple_MergeTile()
{
	
}

Tuple_MergeTile::~Tuple_MergeTile()
{
	delete Data;
#ifdef __TCLMODE__
	delete numerator;
	delete denumorator;
#endif
}

void Tuple_MergeTile::SetParameter(int inputindex[4])
{
	normalization_factor = std::sqrt(4.);
	iTableSize = 1;
	for (int i = 0 ;i < iRange; i++)
		iTableSize *= 3;
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

float Tuple_MergeTile::getWeight(int board[4][4]){

	float value = getWeight(board, 0) + getWeight(board, 1) + getWeight(board, 2)
		+ getWeight(board, 3);
	return value;
}


float Tuple_MergeTile::getWeight(int board[4][4], int no)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 4);
#endif
	return  Data[GetMergeNumber(board, no)];
}

void Tuple_MergeTile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 4);
#endif
	Data[GetMergeNumber(board, no)] = weight;
}

void Tuple_MergeTile::Update(int board[4][4], const float error)
{
	for (int i = 0 ;i<4 ; i++){
		int position = GetMergeNumber(board, i);
#ifdef __TCLMODE__
		numerator[position] += error;
		denumorator[position] += abs(error);
		Data[position] += LEARNING_RATE * error * abs(numerator[position]) / denumorator[position] / normalization_factor;
#else
		Data[position] += LEARNING_RATE * error / normalization_factor;
#endif
	}
}
int Tuple_MergeTile::GetMergeNumber(int board[4][4], int no)
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
void Tuple_MergeTile::ReadFromWeightTable(const char * filename)
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


void Tuple_MergeTile::WriteToWeightTable(const char * filename)
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



int Tuple_MergeTile::UpsideDown(const int index){
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}


int Tuple_MergeTile::Rotate(const int index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}

int Tuple_MergeTile::pow(int x, int y){
	int value = 1;
	for (int i = 0 ; i<y ; i++)
		value *= x;
	return  value;
}