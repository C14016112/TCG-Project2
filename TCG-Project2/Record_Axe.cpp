#include "Record_Axe.h"

Record_Axe::Record_Axe()
{
	for (int i = 0 ;i < 6 ; i++){
		if(i < 4){
			index[0][0][i] = 12 - 4 * i;
			index[0][1][i] = i;
			index[0][2][i] = 3 + 4 * i;
			index[0][3][i] = 15 - i;
			index[0][4][i] = 15 - 4 * i;
			index[0][5][i] = 12 + i;
			index[0][6][i] = 4 * i;
			index[0][7][i] = 3 - i;

			/*index[1][0][i] = 13 - 4 * i;
			index[1][1][i] = 4 + i;
			index[1][2][i] = 2 + 4 * i;
			index[1][3][i] = 11 - i;
			index[1][4][i] = 14 - 4 * i;
			index[1][5][i] = 8 + i;
			index[1][6][i] = 1 + 4 * i;
			index[1][7][i] = 7 - i;

			index[2][0][i] = 14 - 4 * i;
			index[2][1][i] = 8 + i;
			index[2][2][i] = 1 + 4 * i;
			index[2][3][i] = 7 - i;
			index[2][4][i] = 13 - 4 * i;
			index[2][5][i] = 4 + i; 
			index[2][6][i] = 2 + 4 * i;
			index[2][7][i] = 11 - i;*/
		}
		else{
			index[0][0][i] = 1 + 4 * ( i - 4);
			index[0][1][i] = 11 - i;
			index[0][2][i] = 14 - 4 * (i - 4);
			index[0][3][i] = 4 + i;
			index[0][4][i] = 2 + 4 * (i - 4);
			index[0][5][i] = 15 - i;
			index[0][6][i] = 13 - 4 * ( i - 4);
			index[0][7][i] = i;

			/*index[1][0][i] = 2 + 4 * ( i - 4);
			index[1][1][i] = 15 - i;
			index[1][2][i] = 13 - 4 * ( i - 4);
			index[1][3][i] = i;
			index[1][4][i] = 1 + 4 * (i - 4);
			index[1][5][i] = 11 - i;
			index[1][6][i] = 14 - 4 * ( i - 4);
			index[1][7][i] = i + 4;

			index[2][0][i] = 3 + 4 * (i - 4);
			index[2][1][i] = 19 - i;
			index[2][2][i] = 12 - 4 * (i - 4);
			index[2][3][i] = i - 4;
			index[2][4][i] = 4 * (i - 4);
			index[2][5][i] = i - 2;
			index[2][6][i] = 15 - 4 * (i - 4);
			index[2][7][i] = 8 + i;*/
		}

	}
	iUpperBound = 20;
	iTableSize = iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	Data1 = new float[iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound];
	//Data2 = new float[iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound];
	//Data3 = new float[iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound];
	for (int i = 0 ; i< iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound; i++){
		Data1[i] = 0;
		//Data2[i] = 0;
		//Data3[i] = 0;
	}
}

Record_Axe::~Record_Axe()
{
	delete Data1;
	//delete Data2;
	//delete Data3;
}

void Record_Axe::setScore(int tablenumber, int inputindex[6], float score){
#ifdef _DEBUG
	assert(tablenumber == 1 ); //|| tablenumber == 2 || tablenumber == 3 );
#endif
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	position += inputindex[4] *iUpperBound*iUpperBound*iUpperBound*iUpperBound + inputindex[5] * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	//if(tablenumber == 1)
	Data1[position] = score;
	/*else if (tablenumber == 2)
		Data2[position] = score;
	else
		Data3[position] = score;*/
}

float Record_Axe::getScore(int tablenumber, int inputindex[6]){
#ifdef _DEBUG
	assert(tablenumber == 1 ); //|| tablenumber == 2 || tablenumber == 3 );
#endif
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	position += inputindex[4] *iUpperBound*iUpperBound*iUpperBound*iUpperBound + inputindex[5] * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	//if(tablenumber == 1)
	return Data1[position];
	/*else if (tablenumber == 2)
		return Data2[position];
	else
		return Data3[position];*/
}

float Record_Axe::getScore(int board[4][4]){

	float value = 0;
	for (int i = 0 ; i< 8 ; i++){
		value = value + get_OneFeature_Score(1, board, i) ;//+ get_OneFeature_Score(2, board, i) + get_OneFeature_Score(3, board, i);
	}
	return value;
}


float Record_Axe::get_OneFeature_Score(int tablenumber, int board[4][4], int no)
{
#ifdef DEBUG
	assert(tablenumber == 1 ); //|| tablenumber == 2 || tablenumber == 3 );
	assert(no >= 0 && no < 8);
#endif
	int index1 = board[index[tablenumber - 1][no][0] / 4][index[tablenumber - 1][no][0] % 4];
	int index2 = board[index[tablenumber - 1][no][1] / 4][index[tablenumber - 1][no][1] % 4];
	int index3 = board[index[tablenumber - 1][no][2] / 4][index[tablenumber - 1][no][2] % 4];
	int index4 = board[index[tablenumber - 1][no][3] / 4][index[tablenumber - 1][no][3] % 4];
	int index5 = board[index[tablenumber - 1][no][4] / 4][index[tablenumber - 1][no][4] % 4];
	int index6 = board[index[tablenumber - 1][no][5] / 4][index[tablenumber - 1][no][5] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	position += index5*iUpperBound*iUpperBound*iUpperBound*iUpperBound + index6 * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	//if(tablenumber == 1)
	return Data1[position];
	/*else if (tablenumber == 2)
		return Data2[position];
	else
		return Data3[position];*/
}

void Record_Axe::set_OneFeature_Score(int tablenumber, int board[4][4], int no, float score)
{
#ifdef DEBUG
	assert(tablenumber == 1);// || tablenumber == 2 || tablenumber == 3 );
	assert(no >= 0 && no < 8);
#endif

	int index1 = board[index[tablenumber - 1][no][0] / 4][index[tablenumber - 1][no][0] % 4];
	int index2 = board[index[tablenumber - 1][no][1] / 4][index[tablenumber - 1][no][1] % 4];
	int index3 = board[index[tablenumber - 1][no][2] / 4][index[tablenumber - 1][no][2] % 4];
	int index4 = board[index[tablenumber - 1][no][3] / 4][index[tablenumber - 1][no][3] % 4];
	int index5 = board[index[tablenumber - 1][no][4] / 4][index[tablenumber - 1][no][4] % 4];
	int index6 = board[index[tablenumber - 1][no][5] / 4][index[tablenumber - 1][no][5] % 4];
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	position += index5*iUpperBound*iUpperBound*iUpperBound*iUpperBound + index6 * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	//if(tablenumber == 1)
	Data1[position] = score;
	/*else if (tablenumber == 2)
		Data2[position] = score;
	else
		Data3[position] = score;*/
}

void Record_Axe::ReadWeightTable(){
	char filename[30] = "WeightTable_Axe_1.bin";
	/*char filename2[30] = "WeightTable_Axe_2.bin";
	char filename3[30] = "WeightTable_Axe_3.bin";*/

	ifstream fin1;
	fin1.open(filename, ios::in | ios::binary );
	//ifstream fin2;
	/*fin2.open(filename2, ios::in | ios::binary );
	ifstream fin3;
	fin3.open(filename3, ios::in | ios::binary );*/

	if( !fin1.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	/*if( !fin2.is_open()){
		printf("The file '%s' was not open\n", filename2);
		return ;
	}

	if( !fin3.is_open()){
		printf("The file '%s' was not open\n", filename3);
		return ;
	}*/

	fin1.read(reinterpret_cast<char*>(Data1), (iTableSize) * sizeof(float));
	/*fin2.read(reinterpret_cast<char*>(Data2), (iTableSize) * sizeof(float));
	fin3.read(reinterpret_cast<char*>(Data3), (iTableSize) * sizeof(float));*/
	fin1.close();
	/*fin2.close();
	fin3.close();*/
}


void Record_Axe::WriteWeightTable()
{
	char filename[30] = "WeightTable_Axe_1.bin";
	/*char filename2[30] = "WeightTable_Axe_2.bin";
	char filename3[30] = "WeightTable_Axe_3.bin";*/

	ofstream fout1;
	fout1.open(filename, ios::out | ios::binary );
	/*ofstream fout2;
	fout2.open(filename2, ios::out | ios::binary );
	ofstream fout3;
	fout3.open(filename3, ios::out | ios::binary );*/

	if( !fout1.is_open()){
		printf("The file '%s' was not open\n", filename);
		return ;
	}

	//if( !fout2.is_open()){
	//	printf("The file '%s' was not open\n", filename2);
	//	return ;
	//}

	//if( !fout3.is_open()){
	//	printf("The file '%s' was not open\n", filename3);
	//	return ;
	//}
	fout1.write(reinterpret_cast<char*>(Data1), (iTableSize) * sizeof(float));
	/*fout2.write(reinterpret_cast<char*>(Data2), (iTableSize) * sizeof(float));
	fout3.write(reinterpret_cast<char*>(Data3), (iTableSize) * sizeof(float));*/
	fout1.close();
	/*fout2.close();
	fout3.close();*/
}
