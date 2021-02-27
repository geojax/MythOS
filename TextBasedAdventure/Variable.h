#pragma once
#define VARIABLES_PATH "data/variables.txt"
#define MAX_VARIABLES 100
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;

int GetValueFromFile(string key, ifstream& file, char divider = '=')
{
	file.seekg(0); // go to beginning of file
	string currentLine;
	for (int i = 1; i < MAX_VARIABLES; ++i)
	{
		getline(file, currentLine);
		if (currentLine.substr(0, key.length()) == key)
		{
			string returnString = currentLine.substr(currentLine.find(divider) + 1, currentLine.length());
			if (isnumber(returnString))
			{
				file.close();
				return stoi(currentLine.substr(currentLine.find(divider) + 1, currentLine.length()));
			}
		}
	}
	return 0; // if can't find a value
}

/*void SetVariable(string variable)
{
	ifstream variablesFile(VARIABLES_PATH);
	string currentLine;
	for (int i = 1; i < 100; ++i)
}*/