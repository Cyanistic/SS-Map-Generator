#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

char keyConvert(int storeNote);
void dataConvert(int storeNote, int exportchoice);
int randomNoteSpiral(int seed, int eval1, int eval2);
int randomNoteJump(int seed, int eval1, int eval2);
void randomSpiral(int& wLoop, int& noteNum, int& seed2, int& eval1, int& eval2, int eval1s[], int& timeAt, int& timeBetween, int& storeNote, char& storeKey, int& format, int& exportchoice, int startTime);
void randomJump(int& wLoop, int& noteNum, int& seed, int& eval1, int& eval2, int eval1s[], int& timeAt, int& timeBetween, int& storeNote, char& storeKey, int& format, int& exportchoice, int startTime);
void randomExport(int& wLoop, int& noteNum, int eval1s[], int& timeAt, int& timeBetween, int& storeNote, char& storeKey, int& format, int& exportchoice,  int startTime, ofstream& outfile);
void dataConvertOut(int storeNote, int exportchoice, ofstream& outfile);
int main()
{
	long long audioID = 0;
	int seed = time(0), eval1, eval2, initial, wLoop = 0, storeNote, noteNum = 0, divis, time, format = 0, choiceSave, timeBetween = 0, timeAt = 0, exportchoice = 0, eval1s[10000], nChoice, seedSave = 0, startTime = 0;
	double bpm;
	char storeKey = 0;
	srand(seed);

	cout << "0. Jump or 1. Spiral? ";
	cin >> nChoice;

	initial = rand() % 9;
	while (initial == 4)
	{
		seed++;
		initial = rand() % 9;
	}
	eval1 = initial;

	if (nChoice == 0)
	{
		eval2 = rand() % 15;
	}
	else
	{
		eval2 = rand() % 12;
	}
	cout << "How many notes? (Enter -1 for BPM & time calc) ";
	cin >> noteNum;

	if (noteNum == -1)
	{
		choiceSave = 1;
		cout << "BPM? ";
		cin >> bpm;
		cout << "Divisor? ";
		cin >> divis;
		cout << "Time? (In seconds) ";
		cin >> time;
		cout << "At what time should the first note be placed? (In miliseconds) ";
		cin >> startTime;

		noteNum = (bpm * divis * time) / 60;

		cout << noteNum << " notes\n";
		timeBetween = (time * 1000) / noteNum;

		cout << "Key or data format? (Key = 0, Data = 1) ";
		cin >> format;
	}

	seedSave = seed;
	if (nChoice == 1)
	{
		randomSpiral(wLoop, noteNum, seed, eval1, eval2, eval1s, timeAt, timeBetween, storeNote, storeKey, format, exportchoice, startTime);
	}
	else
	{
		if (nChoice == 0)
		{
			randomJump(wLoop, noteNum, seed, eval1, eval2, eval1s, timeAt, timeBetween, storeNote, storeKey, format, exportchoice, startTime);
		}
		else
		{
			cout << "doo doo head";
		}
	}

	cout << "\nSave to file? (0 = No, 1 = Yes)";
	cin >> exportchoice;
	ofstream outfile;

	if (exportchoice == 1)
	{
		string locate;
		cout << "Enter file directory: ";
		cin.ignore();
		getline(cin, locate);

		outfile.open(locate);

		cout << "Audio ID? ";
		cin >> audioID;

		seed = seedSave, wLoop = 0;

		outfile << audioID;

		randomExport(wLoop, noteNum, eval1s, timeAt, timeBetween, storeNote, storeKey, format, exportchoice, startTime, outfile);
	}
}

void randomSpiral(int& wLoop, int& noteNum, int& seed, int& eval1, int& eval2, int eval1s[], int& timeAt, int& timeBetween, int& storeNote, char& storeKey, int& format, int& exportchoice, int startTime)
{
	int centerCheck[9] = { 0,7,0,5,0,3,0,1,0 };
	while (wLoop < noteNum)
	{
		storeNote = randomNoteSpiral(seed, eval1, eval2);
		if (eval1s[wLoop - 1] == 4 && wLoop > 0)
		{
			storeNote = centerCheck[eval1s[wLoop - 2]];
		}
		while (storeNote == eval1s[wLoop - 2] && wLoop > 1)
		{
			seed++;
			eval2 = rand() % 12;
			storeNote = randomNoteSpiral(seed, eval1, eval2);
		}
		if (format == 0)
		{
			storeKey = keyConvert(storeNote);
		}
		else
		{
			cout << ",";
			dataConvert(storeNote, exportchoice);
			timeAt =startTime + timeBetween * (wLoop);
			cout << timeAt;
		}
		cout << storeKey;
		eval1s[wLoop] = storeNote;
		eval1 = storeNote;

		eval2 = rand() % 12;
		wLoop++;
		if (wLoop % 3 == 0 && format == 0)
		{
			cout << endl;
		}
		seed++;
	}
}

void randomJump(int& wLoop, int& noteNum, int& seed, int& eval1, int& eval2, int eval1s[], int& timeAt, int& timeBetween, int& storeNote, char& storeKey, int& format, int& exportchoice, int startTime)
{
	while (wLoop < noteNum)
	{
		storeNote = randomNoteJump(seed, eval1, eval2);
		while (storeNote == eval1s[wLoop - 2] && wLoop > 1)
		{
			seed++;
			eval2 = rand() % 15;
			storeNote = randomNoteJump(seed, eval1, eval2);
		}
		if (format == 0)
		{
			storeKey = keyConvert(storeNote);
		}
		else
		{
			cout << ",";
			dataConvert(storeNote, exportchoice);
			timeAt = startTime + timeBetween * (wLoop);
			cout << timeAt;
		}
		cout << storeKey;
		eval1s[wLoop] = storeNote;
		eval1 = storeNote;
		eval2 = rand() % 15;
		wLoop++;
		if (wLoop % 3 == 0 && format == 0)
		{
			cout << endl;
		}
		seed++;
	}
}

void randomExport(int& wLoop, int& noteNum, int eval1s[], int& timeAt, int& timeBetween, int& storeNote, char& storeKey, int& format, int& exportchoice, int startTime, ofstream& outfile)
{
	while (wLoop < noteNum)
	{
		storeNote = eval1s[wLoop];

		if (format == 0)
		{
			storeKey = keyConvert(storeNote);
		}
		else
		{
			outfile << ",";
			dataConvertOut(storeNote, exportchoice, outfile);
			timeAt = startTime + timeBetween * (wLoop);
			outfile << timeAt;
		}
		cout << storeKey;
		wLoop++;
		if (wLoop % 3 == 0 && format == 0)
		{
			cout << endl;
		}
	}
}


int randomNoteJump(int seed, int eval1, int eval2)
{
	int note[9][15] = { {2,5,6,7,8,2,5,6,7,8,2,5,6,7,8},{6,7,8,6,7,8,6,7,8,6,7,8,6,7,8},{0,3,6,7,8,0,3,6,7,8,0,3,6,7,8},{2,5,8,2,5,8,2,5,8,2,5,8,2,5,8},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{0,3,6,0,3,6,0,3,6,0,3,6,0,3,6},{0,1,2,5,8,0,1,2,5,8,0,1,2,5,8},{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2},{0,1,2,3,6,0,1,2,3,6,0,1,2,3,6} };

	return note[eval1][eval2];
}

int randomNoteSpiral(int seed, int eval1, int eval2)
{
	int note[9][12] = { {1,3,1,3,1,3,1,3,1,3,1,3}, {0,2,4,0,2,4,0,2,4,0,2,4}, {1,5,1,5,1,5,1,5,1,5,1,5}, {0,4,6,0,4,6,0,4,6,0,4,6}, {1,3,5,7,1,3,5,7,1,3,5,7}, {2,4,8,2,4,8,2,4,8,2,4,8}, {3,7,3,7,3,7,3,7,3,7,3,7}, {4,6,8,4,6,8,4,6,8,4,6,8}, {5,7,5,7,5,7,5,7,5,7,5,7} };

	return note[eval1][eval2];
}

char keyConvert(int storeNote)
{
	int key[9] = { 81,87,69,65,83,68,90,88,67 };

	return key[storeNote];
}

void dataConvert(int storeNote, int exportchoice)
{
	int data1[9] = { 0,0,0,1,1,1,2,2,2 };
	int data2[9] = { 0,1,2,0,1,2,0,1,2 };

	if (exportchoice == 0)
	{
		cout << data1[storeNote] << "|" << data2[storeNote] << "|";
	}
}

void dataConvertOut(int storeNote, int exportchoice, ofstream& outfile)
{
	int data1[9] = { 0,0,0,1,1,1,2,2,2 };
	int data2[9] = { 0,1,2,0,1,2,0,1,2 };

	outfile << data1[storeNote] << "|" << data2[storeNote] << "|";
}