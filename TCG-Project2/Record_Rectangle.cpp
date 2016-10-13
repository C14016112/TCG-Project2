#include "Record_Rectangle.h"

Record_Rectangle::Record_Rectangle()
{
	for (int i = 0 ;i < 6 ; i++){
		index[0][0][i] = 4*( i / 2 ) + ( i % 2 ) ;
		index[0][1][i] = 4 * (i % 2 ) + ( 6 - i + 1) / 2;
		index[0][2][i] = 15 - 4 * (i/2) - (i % 2);
		index[0][3][i] = 12 + ( i / 2) - 4 * ( i % 2);
		index[0][4][i] = 3 + 4 * ( i / 2 ) - ( i % 2);
		index[0][5][i] = 15 - 4 * ( i % 2 ) - i / 2;
		index[0][6][i] = 12 + ( i % 2) - 4 * ( i / 2);
		index[0][7][i] = 4 - 4 * ( i % 2) + (i / 2);

		index[1][0][i] = 4*( i / 2 ) + ( i % 2 ) + 1;
		index[1][1][i] = 4 * (i % 2 ) + ( 6 - i + 1) / 2 + 4;
		index[1][2][i] = 15 - 4 * (i/2) - (i % 2) - 1;
		index[1][3][i] = 12 + ( i / 2) - 4 * ( i % 2) - 4;
		index[1][4][i] = 3 + 4 * ( i / 2 ) - ( i % 2) - 1;
		index[1][5][i] = 15 - 4 * ( i % 2 ) - i / 2 - 4;
		index[1][6][i] = 12 + ( i % 2) - 4 * ( i / 2) + 1;
		index[1][7][i] = 4 - 4 * ( i % 2) + (i / 2) + 4;

		index[2][0][i] = 4*( i / 2 ) + ( i % 2 ) + 2;
		index[2][1][i] = 4 * (i % 2 ) + ( 6 - i + 1) / 2 + 8;
		index[2][2][i] = 15 - 4 * (i/2) - (i % 2) - 2;
		index[2][3][i] = 12 + ( i / 2) - 4 * ( i % 2) - 8;
		index[2][4][i] = 3 + 4 * ( i / 2 ) - ( i % 2) - 2;
		index[2][5][i] = 15 - 4 * ( i % 2 ) - i / 2 - 8;
		index[2][6][i] = 12 + ( i % 2) - 4 * ( i / 2) + 2;
		index[2][7][i] = 4 - 4 * ( i % 2) + (i / 2) + 8;
	}
	iUpperBound = iUpperBound_6tile;
	Data1 = new float[iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound];
	Data2 = new float[iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound];
	Data3 = new float[iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound];
	for (int i = 0 ; i< iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound; i++){
		Data1[i] = 0;
		Data2[i] = 0;
		Data3[i] = 0;
	}

}

Record_Rectangle::~Record_Rectangle()
{
	delete Data1;
	delete Data2;
	delete Data3;
}

void Record_Rectangle::setScore(int tablenumber, int inputindex[6], float score){
#ifdef _DEBUG
	assert(tablenumber == 1 || tablenumber == 2 || tablenumber == 3);
#endif
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	position += inputindex[4] *iUpperBound*iUpperBound*iUpperBound*iUpperBound + inputindex[5] * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	if(tablenumber == 1)
		Data1[position] = score;
	else if (tablenumber == 2)
		Data2[position] = score;
	else 
		Data3[position] = score;
}

float Record_Rectangle::getScore(int tablenumber, int inputindex[6]){
#ifdef _DEBUG
	assert(tablenumber == 1 || tablenumber == 2 || tablenumber == 3);
#endif
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	position += inputindex[4] *iUpperBound*iUpperBound*iUpperBound*iUpperBound + inputindex[5] * iUpperBound*iUpperBound*iUpperBound*iUpperBound*iUpperBound;
	if(tablenumber == 1)
		return Data1[position];
	else if(tablenumber ==2)
		return Data2[position];
	else
		return Data3[position];
}

float Record_Rectangle::getScore(int board[4][4]){

	float value = 0;
	for (int i = 0 ; i< 8 ; i++){
		value = value + get_OneFeature_Score(1, board, i) + get_OneFeature_Score(2, board, i) + get_OneFeature_Score(3, board, i);
	}
	return value;
}


float Record_Rectangle::get_OneFeature_Score(int tablenumber, int board[4][4], int no)
{
#ifdef DEBUG
	assert(tablenumber == 1 || tablenumber == 2 || tablenumber == 3)
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
	if(tablenumber == 1)
		return Data1[position];
	else if(tablenumber ==2)
		return Data2[position];
	else
		return Data3[position];

}

void Record_Rectangle::set_OneFeature_Score(int tablenumber, int board[4][4], int no, float value)
{
#ifdef DEBUG
	assert(tablenumber == 1 || tablenumber == 2 || tablenumber == 3);
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
	if(tablenumber == 1)
		Data1[position] = value;
	else if (tablenumber == 2)
		Data2[position] = value;
	else 
		Data3[position] = value;
}
