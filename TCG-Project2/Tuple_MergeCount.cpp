#include "Tuple_MergeCount.h"

Tuple_MergeCount::Tuple_MergeCount()
{

	for (int i = 0 ; i< 3; i++){
		Data[i] = 0;
#ifdef __TCLMODE__
		numerator[i] = 0.00000001;
		denumorator[i] = 0.00000001;
#endif
	}
	normalization_factor = std::sqrt(8.);
}

void Tuple_MergeCount::SetParameter(const int input_index[4])
{
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
}

Tuple_MergeCount::~Tuple_MergeCount()
{
}

float Tuple_MergeCount::getWeight(const int board[4][4])
{
	float value = 0;
	for(int i = 0 ;i<8 ;i++)
		value += Data[MergeableNumber(board, i)];
	return  value;
}

float Tuple_MergeCount::getWeight(const int board[4][4], const int no)
{
	return  Data[MergeableNumber(board, no)];
}

void Tuple_MergeCount::setWeight(const int board[4][4], const int no, const float weight)
{
	Data[MergeableNumber(board, no)] = weight;
}

void Tuple_MergeCount::Update(const int board[4][4], const float error)
{
	for (int i = 0 ; i < 8 ; i++){
		int position = MergeableNumber(board, i);
#ifdef __TCLMODE__
		numerator[position] += error;
		denumorator[position] += abs(error);
		Data[position] += LEARNING_RATE * error * abs(numerator[position]) / denumorator[position] / normalization_factor;
#else 
		Data[position] += LEARNING_RATE * error / normalization_factor;
#endif
	}
}

int Tuple_MergeCount::MergeableNumber(const int board[4][4], const int no)
{
	if(isMergeable(board[index[no][1] / 4][ index[no][1] % 4], board[index[no][2] / 4][index[no][2] % 4]) == false ){
		if(isMergeable(board[index[no][0] / 4][ index[no][0] % 4], board[index[no][1] / 4][index[no][1] % 4]) == true ){
			if(isMergeable(board[index[no][2] / 4][ index[no][2] % 4], board[index[no][3] / 4][index[no][3] % 4]) == true )
				return 2;
			else
				return 1;
		}
		else return 0;
	}
	return 1;
}
bool Tuple_MergeCount::isMergeable(const int x, const int y)
{
	if(x - y == 1 || y - x == 1)
		return true;
	if( x == y && x == 1)
		return true;
	return false;
}


void Tuple_MergeCount::ReadFromWeightTable(const char * filename){

	ifstream fin;
	fin.open(filename, ios::in | ios::binary );
	if( !fin.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}
	fin.read(reinterpret_cast<char*>(Data), (3) * sizeof(float));
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
	fin.read(reinterpret_cast<char*>(numerator), (3) * sizeof(float));
	fin.close();
	sprintf(name2, "%s_coherence_denumorator", filename);
	fin.open(name2, ios::in | ios::binary );
	if( !fin.is_open()){
		printf("The file '%s' was not open\n", name2);
		return ;
	}
	fin.read(reinterpret_cast<char*>(denumorator), (3) * sizeof(float));
	fin.close();
#endif
}


void Tuple_MergeCount::WriteToWeightTable(const char * filename)
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
	fout.write(reinterpret_cast<char*>(numerator), (3) * sizeof(float));
	fout.close();

	sprintf(name2, "%s_coherence_denumorator", filename);
	fout.open(name2, ios::out | ios::binary );
	if( !fout.is_open()){
		printf("The file '%s' was not open\n", name2);
		return ;
	}
	fout.write(reinterpret_cast<char*>(denumorator), (3) * sizeof(float));
	fout.close();
#endif

	fout.open(filename, ios::out | ios::binary );
	if( !fout.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	fout.write(reinterpret_cast<char*>(Data), (3) * sizeof(float));
	fout.close();
}


int Tuple_MergeCount::UpsideDown(const int index){
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}


int Tuple_MergeCount::Rotate(const int index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}
