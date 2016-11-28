#include "Tuple.h"

Tuple::Tuple()
{
}

Tuple::~Tuple()
{
}

void Tuple::UpdateTable(int position, const float error, int board[4][4], int stage)
{
	if (UseData[stage][position] == FALSE) {
#ifdef __TCLMODE__
		denumorator[stage][position] = 0.00000001 + abs(error);
		numerator[stage][position] = 0.00000001 + error;
		Data[stage][position] = LEARNING_RATE * error * abs(numerator[stage][position]) / denumorator[stage][position] / normalization_factor;
#else
		Data[stage][position] = Data[stage][position] * UseData[stage][position] + LEARNING_RATE * error / normalization_factor;
#endif
		UseData[stage][position] = TRUE;
	}
	else {
#ifdef __TCLMODE__
		denumorator[stage][position] += abs(error);
		numerator[stage][position] += error;
		Data[stage][position] += LEARNING_RATE * error * abs(numerator[stage][position]) / denumorator[stage][position] / normalization_factor;
#else
		Data[stage][position] += LEARNING_RATE * error / normalization_factor;
#endif
	}
}

int Tuple::UpsideDown(const int index) {
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}

int Tuple::Rotate(const int index)
{
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}

float Tuple::getWeightFromTable(int position, int board[4][4], int stage)
{
	return  Data[stage][position] * UseData[stage][position];
}

void Tuple::setWeightToTable(int position, float value, int board[4][4], int stage)
{
	Data[stage][position] = value;
	UseData[stage][position] = TRUE;
}

void Tuple::Constructor()
{
	Data = new float*[STAGENUM];
	UseData = new bool*[STAGENUM];
#ifdef __TCLMODE__
	numerator = new float*[STAGENUM];
	denumorator = new float*[STAGENUM];
#endif

	for (int i = 0; i < STAGENUM; i++) {
		Data[i] = new float[iTableSize[i]];
		UseData[i] = new bool[iTableSize[i]];
#ifdef __TCLMODE__
		numerator[i] = new float[iTableSize[i]];
		denumorator[i] = new float[iTableSize[i]];
#endif

		// initialize the table
		for (int j = 0; j < iTableSize[i]; j++) {
			/*Data[i][j] = 0;*/
			UseData[i][j] = FALSE;
#ifdef __TCLMODE__
			/*numerator[i][j] = 0.00000001;
			denumorator[i][j] = 0.00000001;*/
#endif
		}
	}
}

void Tuple::Desturctor()
{
	for (int i = 0; i < STAGENUM; i++) {
		delete[] Data[i];
		delete[] UseData[i];
#ifdef __TCLMODE__
		delete[] numerator[i];
		delete[] denumorator[i];
#endif
	}
	delete Data;
	delete UseData;
#ifdef __TCLMODE__
	delete numerator;
	delete denumorator;
#endif
}

int Tuple::GetMaxTile(int board[4][4])
{
	int maxtile = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (board[i][j] > maxtile) maxtile = board[i][j];
	return maxtile;
}

int Tuple::GetStage(int board[4][4])
{
	if (!board)
		getchar();
	int stage = 0;
#ifdef __MULTISTAGE_MAXTILEMODE__
	int maxtile = GetMaxTile(board);
	for (int i = 0; i < STAGENUM; i++) {
		if (maxtile >= stage_threshold[i])
			stage++;
	}
#endif
#ifdef __MULTISTAGE_TILENUMMODE__
	int emptytile_count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0)
				emptytile_count++;
		}
	}
	for (int i = 0; i < STAGENUM; i++) {
		if (16 - emptytile_count > stage_threshold[i])
			stage++;
	}
#endif
	return stage;
}

void Tuple::ReadFromWeightTable(const char * filename) {
	for (int i = 0; i < STAGENUM; i++) {
		ifstream fin;
		ifstream fin1;
		ifstream fin2;
		ifstream fin3;
		char name[100] = { 0 };

		sprintf(name, "%s%d_UseData", filename, i);
		fin.open(name, ios::in | ios::binary);
		if (!fin.is_open()) {
			printf("The file '%s' was not open\n", name);
		}
		fin.read(reinterpret_cast<char*>(UseData[i]), (iTableSize[i])* sizeof(bool));
		fin.close();

		sprintf(name, "%s%d", filename, i);
		fin1.open(name, ios::in | ios::binary);
		if (!fin1.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		sprintf(name, "%s%d_coherence_numerator", filename, i);
		fin2.open(name, ios::in | ios::binary);
		if (!fin2.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		sprintf(name, "%s%d_coherence_denumorator", filename, i);
		fin3.open(name, ios::in | ios::binary);
		if (!fin3.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		for (int j = 0; j < iTableSize[i]; j++) {
			if (UseData[i][j] == FALSE)
				continue;
			fin1.read((char *)&(Data[i][j]), sizeof(float));
#ifdef __TCLMODE__
			fin2.read((char *)&(numerator[i][j]), sizeof(float));
			fin3.read((char *)&(denumorator[i][j]), sizeof(float));
#endif
		}
		fin1.close();
		fin2.close();
		fin3.close();
	}
}
//
//void Tuple::ReadFromWeightTable(const char * filename) {
//	for (int i = 0; i < STAGENUM; i++) {
//		ifstream fin;
//		char name[100] = { 0 };
//		sprintf(name, "%s%d", filename, i);
//		fin.open(name, ios::in | ios::binary);
//		if (!fin.is_open()) {
//			printf("The file '%s' was not open\n", name);
//		}
//		fin.read(reinterpret_cast<char*>(Data[i]), (iTableSize[i])* sizeof(float));
//		fin.close();
//#ifdef __TCLMODE__
//		sprintf(name, "%s%d_coherence_numerator", filename, i);
//		fin.open(name, ios::in | ios::binary);
//		if (!fin.is_open()) {
//			printf("The file '%s' was not open\n", name);
//		}
//		fin.read(reinterpret_cast<char*>(numerator[i]), (iTableSize[i])* sizeof(float));
//		fin.close();
//		sprintf(name, "%s%d_coherence_denumorator", filename, i);
//		fin.open(name, ios::in | ios::binary);
//		if (!fin.is_open()) {
//			printf("The file '%s' was not open\n", name);
//		}
//		fin.read(reinterpret_cast<char*>(denumorator[i]), (iTableSize[i])* sizeof(float));
//		fin.close();
//#endif
//		for (int j = 0; j < iTableSize[i]; j++) {
//			if (Data[i][j] != 0) {
//				UseData[i][j] = TRUE;
//			}
//		}
//	}
//}

void Tuple::WriteToWeightTable(const char * filename)
{
	for (int i = 0; i < STAGENUM; i++) {

		ofstream fout;
		ofstream fout1;
		ofstream fout2;
		ofstream fout3;

		char name[100] = { 0 };

		sprintf(name, "%s%d_UseData", filename, i);
		fout.open(name, ios::out | ios::binary);
		if (!fout.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		fout.write(reinterpret_cast<char*>(UseData[i]), (iTableSize[i])* sizeof(bool));
		fout.close();

		sprintf(name, "%s%d", filename, i);
		fout1.open(name, ios::out | ios::binary);
		if (!fout1.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		sprintf(name, "%s%d_coherence_numerator", filename, i);
		fout2.open(name, ios::out | ios::binary);
		if (!fout2.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		sprintf(name, "%s%d_coherence_denumorator", filename, i);
		fout3.open(name, ios::out | ios::binary);
		if (!fout3.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		for (int j = 0; j < iTableSize[i]; j++) {
			if (UseData[i][j] == FALSE)
				continue;
			fout1.write((const char *)&(Data[i][j]), sizeof(float));
#ifdef __TCLMODE__
			fout2.write((const char *)&(numerator[i][j]), sizeof(float));
			fout3.write((const char *)&(denumorator[i][j]), sizeof(float));
#endif
		}
		fout1.close();
		fout2.close();
		fout3.close();
	}
}