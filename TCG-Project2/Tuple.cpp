#include "Tuple.h"
Tuple::Tuple()
{
}

Tuple::~Tuple()
{
}


int Tuple::GetStage(int board[4][4])
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

int Tuple::GetMaxTile(int board[4][4])
{
	int maxtile = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (board[i][j] > maxtile) maxtile = board[i][j];
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
void Tuple::UpdateTable(int position, const float error, int board[4][4], int stage)
{
#ifdef __TCLMODE__
	if (UseData[stage][position] == -1) {
//#ifdef __TRAININGMODE__
//#ifdef __PARALLELMODE__
//		std::lock_guard<std::mutex> guard(lock_tex);
//#endif
//#endif

		if ( Data[stage].size() + 10 >  Data[stage].capacity() ) {
			Data[stage].reserve(Data[stage].capacity() * 1.5);
#ifdef __TCLMODE__
			numerator[stage].reserve(numerator[stage].capacity() * 1.5);
			denumorator[stage].reserve(denumorator[stage].capacity() * 1.5);
#endif
		}

		denumorator[stage].push_back(0.00000001 + abs(error));
		numerator[stage].push_back(0.00000001 + error);
		Data[stage].push_back(LEARNING_RATE * error * abs(0.00000001 + error) / (0.00000001 + abs(error)) / normalization_factor);
		UseData[stage][position] = denumorator[stage].size() - 1;
	}
	else {
		denumorator[stage][UseData[stage][position]] += abs(error);
		numerator[stage][UseData[stage][position]] += error;
		Data[stage][UseData[stage][position]] += LEARNING_RATE * error * abs(numerator[stage].at(UseData[stage][position])) / denumorator[stage].at(UseData[stage][position]) / normalization_factor;
	}
#else
	if (UseData[stage][position] == -1)
		Data[stage].push_back(LEARNING_RATE * error / normalization_factor);
	else
		Data[stage].at(UseData[stage][position]) += LEARNING_RATE * error / normalization_factor;

#endif
}

float Tuple::getWeightFromTable(int position, int board[4][4], int stage)
{
#ifdef __TRAININGMODE__
	/*lock_tex.lock();
	lock_tex.unlock();*/
#endif
	if (UseData[stage][position] == -1)
		return 0;
	return Data[stage][UseData[stage][position]];
}

void Tuple::setWeightToTable(int position, float value, int board[4][4], int stage)
{
}

void Tuple::Constructor()
{
	UseData = new int *[STAGENUM];
	for (int i = 0; i < STAGENUM; i++) {
		// Data, numerator and denumorator can change their size
		// dynamicaly
		UseData[i] = new int[iTableSize[i]];
		// initialize the table
		for (int j = 0; j < iTableSize[i]; j++) {
			UseData[i][j] = -1;
		}
	}
}
void Tuple::Desturctor()
{
}

void Tuple::ConverTable_VectorToArray(const char * filename)
{
	cout << "convert Weight Table from vector form to array form: " << endl;
	for (int i = 0; i < STAGENUM; i++) {

		/* read data from vector table*/
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
		fin.read(reinterpret_cast<char*>(UseData[i]), (iTableSize[i])* sizeof(int));
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

		float a;
		while (fin1.read((char*)&a, sizeof(float))) {
			Data[i].push_back(a);
#ifdef __TCLMODE__
			float b;
			float c;
			fin2.read((char*)&b, sizeof(float));
			numerator[i].push_back(b);
			fin3.read((char*)&c, sizeof(float));
			denumorator[i].push_back(c);
#endif
		}
		fin1.close();
		fin2.close();
		fin3.close();

		/*write data into array table*/
		ofstream fout1;
		ofstream fout2;
		ofstream fout3;


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
			if (UseData[i][j] == -1) {
				fout1.write("0", sizeof(float));
#ifdef __TCLMODE__
				fout2.write("0", sizeof(float));
				fout3.write("0", sizeof(float));
#endif
			}
			else {
				fout1.write((const char *)&(Data[i][UseData[i][j]]), sizeof(float));
#ifdef __TCLMODE__
				fout2.write((const char *)&(numerator[i][UseData[i][j]]), sizeof(float));
				fout3.write((const char *)&(denumorator[i][UseData[i][j]]), sizeof(float));
#endif
			}
		}
	}
}

void Tuple::ReadFromWeightTable(const char * filename)
{
	cout << "Read Weight Table: " << filename << endl;
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
		fin.read(reinterpret_cast<char*>(UseData[i]), (iTableSize[i])* sizeof(int));
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

		//****************************** test other method to read table **********************
		Data[i].reserve(iTableSize[i] * 0.1);
		float *tmp_Data = new float[iTableSize[i]];
#ifdef __TCLMODE__
		numerator[i].reserve(iTableSize[i] * 0.1);
		denumorator[i].reserve(iTableSize[i] * 0.1);
		float *tmp_num = new float[iTableSize[i]];
		float *tmp_den = new float[iTableSize[i]];
#endif
		for (int j = 0; j < iTableSize[i]; j++) {
			tmp_Data[j] = -FLT_MAX;
#ifdef __TCLMODE__
			tmp_num[j] = -FLT_MAX;
			tmp_den[j] = -FLT_MAX;
#endif
		}
		fin1.read(reinterpret_cast<char*>(tmp_Data), (iTableSize[i])* sizeof(float));
#ifdef __TCLMODE__
		fin2.read(reinterpret_cast<char*>(tmp_num), (iTableSize[i])* sizeof(float));
		fin3.read(reinterpret_cast<char*>(tmp_den), (iTableSize[i])* sizeof(float));
#endif
		for (int j = 0; j < iTableSize[i]; j++) {
			if (tmp_Data[j] == -FLT_MAX)
				break;
			if ( Data[i].size() + 10 > Data[i].capacity() ) {
				Data[i].reserve(Data[i].capacity() * 1.5);
#ifdef __TCLMODE__
				numerator[i].reserve(numerator[i].capacity() * 1.5);
				denumorator[i].reserve(denumorator[i].capacity() * 1.5);
#endif
			}
			Data[i].push_back(tmp_Data[j]);
#ifdef __TCLMODE__
			numerator[i].push_back(tmp_num[j]);
			denumorator[i].push_back(tmp_den[j]);
#endif
		}
		delete tmp_Data;
#ifdef __TCLMODE__
		delete tmp_num;
		delete tmp_den;
#endif
/*
float a;
while (fin1.read((char*)&a, sizeof(float))) {
Data[i].push_back(a);
#ifdef __TCLMODE__
float b;
float c;
fin2.read((char*)&b, sizeof(float));
numerator[i].push_back(b);
fin3.read((char*)&c, sizeof(float));
denumorator[i].push_back(c);
#endif
}
*/

		fin1.close();
		fin2.close();
		fin3.close();
	}
}
void Tuple::WriteToWeightTable(const char * filename)
{
	cout << "Write Weight Table: " << filename << endl;
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

		fout.write(reinterpret_cast<char*>(UseData[i]), (iTableSize[i])* sizeof(int));
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

		for (int j = 0; j < Data[i].size(); j++) {
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

#endif






#ifdef __ARRAYTABLEMODE__

void Tuple::UpdateTable(int position, const float error, int board[4][4], int stage)
{
#ifdef __TCLMODE__
	denumorator[stage][position] += (error < 0) ? -error : error; 
	numerator[stage][position] += error;
	Data[stage][position] += LEARNING_RATE * error * abs(numerator[stage][position]) / denumorator[stage][position] / normalization_factor;
#else
	Data[stage][position] += LEARNING_RATE * error / normalization_factor;
#endif
}

float Tuple::getWeightFromTable(int position, int board[4][4], int stage)
{
	return Data[stage][position];
}

void Tuple::setWeightToTable(int position, float value, int board[4][4], int stage)
{
	Data[stage][position] = value;
}

void Tuple::Constructor()
{
	Data = new float*[STAGENUM];

#ifdef __TCLMODE__
	numerator = new float*[STAGENUM];
	denumorator = new float*[STAGENUM];
#endif

	for (int i = 0; i < STAGENUM; i++) {
		Data[i] = new float[iTableSize[i]];
#ifdef __TCLMODE__
		numerator[i] = new float[iTableSize[i]];
		denumorator[i] = new float[iTableSize[i]];
#endif

		// initialize the table
		for (int j = 0; j < iTableSize[i]; j++) {
			Data[i][j] = 0;
#ifdef __TCLMODE__
			numerator[i][j] = 0.00000001;
			denumorator[i][j] = 0.00000001;
#endif
		}
	}
}

void Tuple::Desturctor()
{
	for (int i = 0; i < STAGENUM; i++) {
		delete[] Data[i];
#ifdef __TCLMODE__
		delete[] numerator[i];
		delete[] denumorator[i];
#endif
	}
	delete Data;
#ifdef __TCLMODE__
	delete numerator;
	delete denumorator;
#endif
}

void Tuple::ReadFromWeightTable(const char * filename) {
	for (int i = 0; i < STAGENUM; i++) {
		ifstream fin;
		char name[100] = { 0 };
		sprintf(name, "%s%d", filename, i);
		fin.open(name, ios::in | ios::binary);
		if (!fin.is_open()) {
			printf("The file '%s' was not open\n", name);
		}
		fin.read(reinterpret_cast<char*>(Data[i]), (iTableSize[i])* sizeof(float));
		fin.close();
#ifdef __TCLMODE__
		sprintf(name, "%s%d_coherence_numerator", filename, i);
		fin.open(name, ios::in | ios::binary);
		if (!fin.is_open()) {
			printf("The file '%s' was not open\n", name);
		}
		fin.read(reinterpret_cast<char*>(numerator[i]), (iTableSize[i])* sizeof(float));
		fin.close();
		sprintf(name, "%s%d_coherence_denumorator", filename, i);
		fin.open(name, ios::in | ios::binary);
		if (!fin.is_open()) {
			printf("The file '%s' was not open\n", name);
		}
		fin.read(reinterpret_cast<char*>(denumorator[i]), (iTableSize[i])* sizeof(float));
		fin.close();
#endif
	}
}


void Tuple::WriteToWeightTable(const char * filename)
{
	for (int i = 0; i < STAGENUM; i++) {

		ofstream fout;
		char name[100] = { 0 };
#ifdef __TCLMODE__

		sprintf(name, "%s%d_coherence_numerator", filename, i);
		fout.open(name, ios::out | ios::binary);
		if (!fout.is_open()) {
			printf("The file '%s' was not open\n", name);
		}
#ifdef __TRAININGMODE__
		fout.write(reinterpret_cast<char*>(numerator[i]), (iTableSize[i])* sizeof(float));
#endif
		fout.close();

		sprintf(name, "%s%d_coherence_denumorator", filename, i);
		fout.open(name, ios::out | ios::binary);
		if (!fout.is_open()) {
			printf("The file '%s' was not open\n", name);
		}
#ifdef __TRAININGMODE__
		fout.write(reinterpret_cast<char*>(denumorator[i]), (iTableSize[i])* sizeof(float));
#endif
		fout.close();
#endif
		sprintf(name, "%s%d", filename, i);
		fout.open(name, ios::out | ios::binary);
		if (!fout.is_open()) {
			printf("The file '%s' was not open\n", name);
		}

		fout.write(reinterpret_cast<char*>(Data[i]), (iTableSize[i])* sizeof(float));
		fout.close();

	}
}
#endif
