#include "Tuple_6tile.h"

Tuple_6tile::Tuple_6tile()
{
	iTableSize = iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound*iUpperbound;
}

void Tuple_6tile::SetParameter(int input_index[6])
{
	normalization_factor = std::sqrt(8.);
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

Tuple_6tile::~Tuple_6tile()
{
	delete Data;
#ifdef __TCLMODE__
	delete numerator;
	delete denumorator;
#endif
}

float Tuple_6tile::getWeight(int board[4][4])
{
	float value = getWeight(board, 0) + getWeight(board, 1) + getWeight(board, 2)
		+ getWeight(board, 3) + getWeight(board, 4) + getWeight(board, 5) 
		+ getWeight(board, 6) + getWeight(board, 7);
	return value;
}

float Tuple_6tile::getWeight(int board[4][4], int no)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	int position = board[index[no][0] / 4][index[no][0] % 4]
	+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
	+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][4] / 4][index[no][4] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][5] / 4][index[no][5] % 4];
	return  Data[position];
}

void Tuple_6tile::setWeight(int board[4][4], int no, float weight)
{
#ifdef _DEBUG
	assert(no >= 0 && no < 8);
#endif
	
	int position = board[index[no][0] / 4][index[no][0] % 4]
	+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
	+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][4] / 4][index[no][4] % 4]
	+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][5] / 4][index[no][5] % 4];
	Data[position] = weight;
}

void Tuple_6tile::Update(int board[4][4], const float error)
{
	for (int no = 0 ; no < 8 ; no++){
		int position = board[index[no][0] / 4][index[no][0] % 4]
		+ iUpperbound * board[index[no][1] / 4][index[no][1] % 4]
		+ iUpperbound * iUpperbound * board[index[no][2] / 4][index[no][2] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * board[index[no][3] / 4][index[no][3] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][4] / 4][index[no][4] % 4]
		+ iUpperbound * iUpperbound * iUpperbound * iUpperbound * iUpperbound * board[index[no][5] / 4][index[no][5] % 4];
#ifdef __TCLMODE__
		denumorator[position] += abs(error);
		numerator[position] += error;
		Data[position] += LEARNING_RATE * error * abs(numerator[position]) / denumorator[position] / normalization_factor;
#else
		Data[position] += LEARNING_RATE * error / normalization_factor;
#endif
	}
}
void Tuple_6tile::ReadFromWeightTable(const char *filename){

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


void Tuple_6tile::WriteToWeightTable(const char *filename)
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



int Tuple_6tile::UpsideDown(const int index){
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}


int Tuple_6tile::Rotate(const int index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}
