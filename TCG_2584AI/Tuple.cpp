#include "Tuple.h"
Tuple::Tuple()
{
}

Tuple::~Tuple()
{
}


int Tuple::GetStage(int board[16])
{
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
	for (int i = 0; i < 16; i++) {
		if (board[i] == 0)
			emptytile_count++;
	}
	for (int i = 0; i < STAGENUM; i++) {
		if (16 - emptytile_count > stage_threshold[i])
			stage++;
	}
#endif
	return stage;
}

int Tuple::GetMaxTile(int board[16])
{
	int maxtile = 0;
	for (int i = 0; i < 16; i++)
			if (board[i] > maxtile) maxtile = board[i];
	return maxtile;
}

int Tuple::UpsideDown(const int index) {
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return upsidedown_table[index];
}

int Tuple::Rotate(const int index) {
#ifdef _DEBUG
	assert(index >= 0 && index < 16);
#endif
	return rotate_table[index];
}

#ifdef __VECTORTABLEMODE__
void Tuple::UpdateTable(int position, const float error, int board[16], int stage)
{
	int tmp_position = 0;
	if (UseData[stage][position] == -1){
		if (iCurentTableSize[stage] == iTableCapacity[stage]) {
			TableReserve(stage);
		}
		UseData[stage][position] = iCurentTableSize[stage];
		iCurentTableSize[stage]++;
	}
#ifdef __TCLMODE__
	numerator[stage][UseData[stage][position]] += error;
	denumorator[stage][UseData[stage][position]] += abs(error);
	Data[stage][UseData[stage][position]] += LEARNING_RATE * error * abs(numerator[stage][UseData[stage][position]]) / denumorator[stage][UseData[stage][position]] / normalization_factor;
#else
	Data[stage][UseData[stage][position]] += LEARNING_RATE * error / normalization_factor;
#endif
}

float Tuple::getWeightFromTable(int position, int board[16], int stage)
{
	if (UseData[stage][position] == -1)
		return 0;
	if (UseData[stage][position] > iTableSize[stage]) {
		UseData[stage][position] = -1;
		return 0;
	}
	return Data[stage][UseData[stage][position]];
}

void Tuple::Constructor()
{
	for (int i = 0; i < STAGENUM; i++) {
		// Data, numerator and denumorator can change their size
		// dynamicaly
		UseData[i] = new int[iTableSize[i]];
		if (iTableSize[i] > 1000000)
			iTableCapacity[i] = iTableSize[i] >> 4;
		else
			iTableCapacity[i] = iTableSize[i];
		iCurentTableSize[i] = 0;
		Data[i] = new float[iTableCapacity[i]];
#ifdef __TCLMODE__
		numerator[i] = new float[iTableCapacity[i]];
		denumorator[i] = new float[iTableCapacity[i]];
#endif
		// initialize the table
		for (int j = 0; j < iTableSize[i]; j++) 
			UseData[i][j] = -1;
		for (int j = 0; j < iTableCapacity[i]; j++) {
			Data[i][j] = 0;
#ifdef __TCLMODE__
			numerator[i][j] = FLT_MIN;
			denumorator[i][j] = FLT_MIN;
#endif
		}
	}
}

void Tuple::Desturctor()
{
	for (int i = 0; i < STAGENUM; i++) {
		delete [] UseData[i];
		delete [] Data[i];
#ifdef __TCLMODE__
		delete [] denumorator[i];
		delete [] numerator[i];
#endif
	}
}

void Tuple::ReadFromWeightTable(const char * filename)
{
	cout << "Read Weight Table: " << filename << endl;
	ifstream fin;
	ifstream fin1;
	ifstream fin2;
	ifstream fin3;
	ifstream fin_par;
	char name[100] = { 0 };

	sprintf(name, "%s_UseData", filename);
	fin.open(name, ios::in | ios::binary);
	if (!fin.is_open()) {
		printf("The file '%s' was not open\n", name);
		return;
	}
	sprintf(name, "%s", filename);
	fin1.open(name, ios::in | ios::binary);
	if (!fin1.is_open()) {
		printf("The file '%s' was not open\n", name);
		return;
	}

	sprintf(name, "%s_coherence_numerator", filename);
	fin2.open(name, ios::in | ios::binary);
	if (!fin2.is_open()) {
		printf("The file '%s' was not open\n", name);
	}

	sprintf(name, "%s_coherence_denumorator", filename);
	fin3.open(name, ios::in | ios::binary);
	if (!fin3.is_open()) {
		printf("The file '%s' was not open\n", name);
	}

	sprintf(name, "%s_parameter", filename);
	fin_par.open(name, ios::in | ios::binary);
	if (!fin_par.is_open()) {
		printf("The file '%s' was not open\n", name);
		return;
	}

	fin_par.read(reinterpret_cast<char*>(iTableCapacity), STAGENUM * sizeof(int));
	fin_par.read(reinterpret_cast<char*>(iCurentTableSize), STAGENUM * sizeof(int));

	for (int i = 0; i < STAGENUM; i++) {
		fin.read(reinterpret_cast<char*>(UseData[i]), (iTableSize[i])* sizeof(int));
		delete Data[i];
		Data[i] = new float[iTableCapacity[i]];
		fin1.read(reinterpret_cast<char*>(Data[i]), iTableCapacity[i] * sizeof(float));
#ifdef __TCLMODE__
		delete numerator[i];
		numerator[i] = new float[iTableCapacity[i]];
		fin2.read(reinterpret_cast<char*>(numerator[i]), iTableCapacity[i] * sizeof(float));
		delete denumorator[i];
		denumorator[i] = new float[iTableCapacity[i]];
		fin3.read(reinterpret_cast<char*>(denumorator[i]), iTableCapacity[i] * sizeof(float));
#endif
		for (int j = iCurentTableSize[i]; j < iTableCapacity[i]; j++) {
			Data[i][j] = 0;
#ifdef __TCLMODE__
			numerator[i][j] = FLT_MIN;
			denumorator[i][j] = FLT_MIN;
#endif
		}
	}
	fin.close();
	fin1.close();
	fin2.close();
	fin3.close();
	fin_par.close();
}

void Tuple::WriteToWeightTable(const char * filename)
{
	cout << "Write Weight Table: " << filename << endl;
	ofstream fout;
	ofstream fout1;
	ofstream fout2;
	ofstream fout3;
	ofstream fout_par;

	char name[100] = { 0 };

	sprintf(name, "%s_UseData", filename);
	fout.open(name, ios::out | ios::binary);
	if (!fout.is_open()) {
		printf("The file '%s' was not open\n", name);
	}

	

	sprintf(name, "%s", filename);
	fout1.open(name, ios::out | ios::binary);
	if (!fout1.is_open()) {
		printf("The file '%s' was not open\n", name);
	}

	sprintf(name, "%s_coherence_numerator", filename);
	fout2.open(name, ios::out | ios::binary);
	if (!fout2.is_open()) {
		printf("The file '%s' was not open\n", name);
	}

	sprintf(name, "%s_coherence_denumorator", filename);
	fout3.open(name, ios::out | ios::binary);
	if (!fout3.is_open()) {
		printf("The file '%s' was not open\n", name);
	}

	sprintf(name, "%s_parameter", filename);
	fout_par.open(name, ios::out | ios::binary);
	if (!fout_par.is_open()) {
		printf("The file '%s' was not open\n", name);
	}

	fout_par.write(reinterpret_cast<char*>(iTableCapacity), STAGENUM * sizeof(int));
	fout_par.write(reinterpret_cast<char*>(iCurentTableSize), STAGENUM * sizeof(int));

	for (int i = 0; i < STAGENUM; i++) {
		fout.write(reinterpret_cast<char*>(UseData[i]), (iTableSize[i])* sizeof(int));
		fout1.write(reinterpret_cast<char*>(Data[i]), (iTableCapacity[i])* sizeof(float));
#ifdef __TCLMODE__
		fout2.write(reinterpret_cast<char*>(numerator[i]), (iTableCapacity[i])* sizeof(float));
		fout3.write(reinterpret_cast<char*>(denumorator[i]), (iTableCapacity[i])* sizeof(float));
#endif
	}

	fout.close();
	fout1.close();
	fout2.close();
	fout3.close();
	fout_par.close();
}

#endif

void Tuple::TableReserve(int stage)
{
	iTableCapacity[stage] *= 1.1;
	float *tmpData = new float[iTableCapacity[stage]];
#ifdef __TCLMODE__
	float *tmpNum = new float[iTableCapacity[stage]];
	float *tmpDen = new float[iTableCapacity[stage]];
#endif
	memset(tmpData, 0, iTableCapacity[stage]);
	for (int i = 0; i < iTableCapacity[stage]; i++) {
#ifdef __TCLMODE__
		tmpNum[i] = FLT_MIN;
		tmpDen[i] = FLT_MIN;
#endif
	}
	for (int i = 0; i < iCurentTableSize[stage]; i++) {
		tmpData[i] = Data[stage][i];
#ifdef __TCLMODE__
		tmpNum[i] = numerator[stage][i];
		tmpDen[i] = denumorator[stage][i];
#endif
	}
	delete Data[stage];
	Data[stage] = tmpData;
#ifdef __TCLMODE__
	delete numerator[stage];
	delete denumorator[stage];

	numerator[stage] = tmpNum;
	denumorator[stage] = tmpDen;
#endif
	
}

void Tuple::WriteArrayTable(const char * filename)
{
	for (int i = 0; i < STAGENUM; i++) {
		float *tmpData = new float[iTableSize[i]];
		for (int j = 0; j < iTableSize[i]; j++) {
			if (UseData[i][j] == -1)
				tmpData[j] = 0;
			else
				tmpData[j] = Data[i][UseData[i][j]];
		}

		ofstream fout;
		char name[100] = { 0 };
		sprintf(name, "%s%d", filename, i);
		fout.open(name, ios::out | ios::binary);
		if (!fout.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		fout.write(reinterpret_cast<char*>(tmpData), (iTableSize[i])* sizeof(float));
		fout.close();
		delete tmpData;
	}
}