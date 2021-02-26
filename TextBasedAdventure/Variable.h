#pragma once
#define VARIABLES_PATH "data/variables.txt"
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;

int GetVariable(string variable)
{
	ifstream variablesFile(VARIABLES_PATH);
	string currentLine;
	for (int i = 1; i < 100; ++i)
	{
		getline(variablesFile, currentLine);
		if (currentLine.substr(0, variable.length()) == variable)
		{
			string returnString = currentLine.substr(currentLine.find('=') + 1, currentLine.length());
			if (isnumber(returnString)) 
			{
				variablesFile.close();
				return stoi(currentLine.substr(currentLine.find('=') + 1, currentLine.length()));
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