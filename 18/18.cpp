// 18.cpp: ���������� ����� ����� ��� ����������� ����������.
//
/*
18
�  �����  �������  �����  �������������.  �������������
����� ���,  ����� ������ ������ �� 4 ����� �������� � �����  �
���  ��  �������,  ���������  �  ��������� ����� � ��� �������
������������ ����������� ������� �� 5 ������� ������ ��� �����
���������� (7).

�����: ������� ������ ��-21 ������� ������.
*/

#include "stdafx.h"

using namespace std;

bool IsValidAmountArguments(const int &argc);
bool IsFileExists(const ifstream &file);
bool IsFileEmpty(ifstream &file);
bool IsValidInputOutputFiles(char* argv[], ifstream &inputFile, ofstream &outputFile);

void ClearLine(char * line);
void GetLine(ifstream & inputFile, char * line);
void PrintLine(ofstream & output, char * line);
bool IsEvenVerseLine(unsigned int& number);
char ToUpper(char& letter);

void ShiftOddVerses(ifstream &inputFile, ofstream &outputFile);



int main(int argc, char* argv[])
{
	if (!IsValidAmountArguments(argc))
	{
		cout << ERROR_ARGUMENT_COUNT_TEXT << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	if (!IsValidInputOutputFiles(argv, inputFile, outputFile))
	{
		return 1;
	}

	ShiftOddVerses(inputFile, outputFile);

	inputFile.close();
	outputFile.close();

	return 0;
}



bool IsValidAmountArguments(const int &argc)
{
	return argc == COUNT_VALID_ARGUMENTS;
}

bool IsFileExists(const ifstream &file)
{
	return file.good();
}

bool IsFileEmpty(ifstream &file)
{
	return file.peek() == ifstream::traits_type::eof();
}

bool IsValidInputOutputFiles(char* argv[], ifstream &inputFile, ofstream &outputFile)
{
	if (!IsFileExists(inputFile))
	{
		cout << "Input file " << argv[1] << " not exists" << "\n";
		return false;
	}

	if (IsFileEmpty(inputFile))
	{
		cout << "Input file " << argv[1] << " is empty" << "\n";
		return false;
	}

	return true;
}

bool IsEvenVerseLine(unsigned int & number)
{
	return number / NUMBER_LINE_IN_VERSE % STEP != ODD_VERSE;
}

void ClearLine(char * line)
{
	for (size_t i = 0; i < LINE_LENGTH; i++)
	{
		line[i] = ' ';
	}
}

void GetLine(ifstream & inputFile, char * line)
{
	char ch = ' ';

	for (size_t i = 0; inputFile.get(ch) && (ch != '\n') && (ch != EOF); i++)
	{
		line[i] = ch;
	}
}

void PrintLine(ofstream & output, char * line)
{
	output << line << "\n";
}

char ToUpper(char &letter)
{
	int asciiCode = static_cast<char>(letter);

	/*
	�������� ����� ���������� �������� (����� '�', ��� ��������: -72, ��� ��������� -88) � ����������� ��������
	��������� � ������ ascii � ��������� ���������� [-32; -1] � [97; 122] ��������������.
	���������: [-64; -33] � [65;97]
	*/

	if ((asciiCode >= -32 && asciiCode <= -1) || (asciiCode >= 97 && asciiCode <= 122))
	{
		letter = static_cast<int>(asciiCode - 32);
	}
	else if (asciiCode == -72)
	{
		letter = static_cast<int>(-88);
	}

	return letter;
}

void ShiftOddVerses(ifstream &inputFile, ofstream &outputFile)
{
	char line[LINE_LENGTH],
		ch = ' ';

	ClearLine(line);

	for (size_t lineNumber = FIRST_LINE; !inputFile.eof(); lineNumber++)
	{
		GetLine(inputFile, line);

		if (IsEvenVerseLine(lineNumber)) {
			outputFile << INDENT_VERSE;
		}

		line[0] = ToUpper(line[0]);

		PrintLine(outputFile, line);

		ClearLine(line);
	}
}