#pragma once
#define VARIABLES_PATH "data/variables.txt"
#define MAX_VARIABLES 100
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;

bool isnumber(string str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

int GetValueFromFile(string key, string filename, char divider = '=') // default filename to VARIABLES_PATH!!!
{
	ifstream file(filename);
	string currentLine;
	for (int i = 0; i < MAX_VARIABLES; ++i)
	{
		getline(file, currentLine); // File does not seem to be resetting
		if (currentLine == "")return -1; // never have a gap in a file if using this method
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
	return -1; // if can't find a value
}

int FindLineNumStartsWith(string str, int max_lines = MAX_VARIABLES, string filename = VARIABLES_PATH)
{
	ifstream file(filename);
	string currentLine;
	for (int lineNo = 0; lineNo < max_lines; ++lineNo)
	{
		getline(file, currentLine);
		if (currentLine.length() >= str.length() && currentLine.substr(0, str.length()) == str)
		{
			return lineNo;
		}
	}
	return -1;
}

bool FileToStrArray(string filename, string* writeTo)
{
	int c; // current character of file
	int i = 0; // index of variables array
	ifstream file(filename);

	if (!file)
		return false;

	while ((c = file.get()) != EOF && i < MAX_VARIABLES) // end when end of file is reached or we've gone to max variables
	{
		if (c == '\n') 
		{
			++i; // go to the next index of the array on newlines
			continue; // don't include \n in the array
		}

		writeTo[i] += c;
	}
	for (int i = 0; i < 4; ++i)
		cout << writeTo[i];
	return true;
}

bool startswith(string str, string str2)
{
	if (str.length() < str2.length()) // check length first to avoid substr out of range
		return false;

	return str.substr(0, str2.length()) == str2.substr(0, str2.length());
}

void SetVariable(string* variables, string var, string val) 
{
	for (int i = 0; i < MAX_VARIABLES; ++i)
	{
		if (startswith(variables[i], var)) 
			variables[i] = variables[i].substr(0, var.length()) + "=" + val;
	}
}

int GetVariable(string* variables, string var)
{
	for (int i = 0; i < MAX_VARIABLES; ++i)
	{
		string currentLine = variables[i];
		if (startswith(currentLine, var))
		{
			if (isnumber(currentLine.substr(currentLine.find('=') + 1)))
				return stoi(currentLine.substr(currentLine.find('=') + 1));
			return -1;
		}
	}
	return -1;
}

// Thanks to cire on cplusplus.com in a 9-year-old post
bool writeToFile(unsigned lineNo, string toWrite, string filename = VARIABLES_PATH)
{
	std::fstream file(filename);
	if (!file)
		return false;

	unsigned currentLine = 0;
	while (currentLine < lineNo)
	{
		// We don't actually care about the lines we're reading,
		// so just discard them.
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		++currentLine;
	}

	// Position the put pointer -- switching from reading to writing.
	file.seekp(file.tellg());

	file << toWrite;
	return true;
}

//void resetVariables(string filename = VARIABLES_PATH)
//{
//	std::fstream file(filename);
//	string currentVariable, toWrite;
//
//	for (int currentLine = 0; currentLine < MAX_VARIABLES; currentLine++)
//	{
//		getline(file, currentVariable);
//		for (int n = 0; currentVariable[n] != '='; ++n)
//		{
//			toWrite += currentVariable[n];
//
//			file.seekp(file.tellg());
//			file << toWrite;
//	}
//}


