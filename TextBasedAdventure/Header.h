#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Variable.h"
#ifdef _WIN32
	#include "windows.h"
#endif
#ifdef TARGET_OS_MAC
	#include <unistd.h>
#endif
#define START_FILE_STRING "START.txt"
#define END_FILE_STRING "End.txt"
#define SLEEP_DURATION 20 // typewriter effect duration

using namespace std;

#define MAX_LINES_OF_DESCRIPTION 1000 // 1000 lines is the max

void LocalSleep(int duration)
{
#ifdef _WIN32
	Sleep(duration);
#endif

#ifdef TARGET_OS_MAC
	usleep(duration);
#endif
}

string FindLinkerLine(string filename) // make sure the file has a linker and return linker line
{
	if (filename == END_FILE_STRING) {
		return "";
	}
	ifstream file(filename);
	string currentLine;
	for (int i = 0; i <= MAX_LINES_OF_DESCRIPTION; ++i)
	{
		getline(file, currentLine);
		if (currentLine[0] == '[') {
			file.clear();
			file.seekg(0);
			return currentLine;
		}
		if (i == MAX_LINES_OF_DESCRIPTION)
			throw(filename);
	}
}

string SkipToNextStar(ifstream& file, int& lineNumber)
{
	string currentLine;
	getline(file, currentLine);
	for (; lineNumber < MAX_LINES_OF_DESCRIPTION && currentLine[0] != '*'; ++lineNumber)
		getline(file, currentLine);
	return currentLine;
}

void PrintFile(string filename, string* variables) { // prints out description and returns exit options 
	cout << '\n';
	
	ifstream file(filename);
	string currentLine;
	bool sleepIsOn = false;

	if (filename == END_FILE_STRING) {
		return;
	}
	int lineNumber = 0;
	for (;lineNumber < MAX_LINES_OF_DESCRIPTION; ++lineNumber) {
		getline(file, currentLine);
		if (currentLine[0] == '[') {
			return;
		}
		else if (currentLine[0] == '*') {
			if (isalpha(currentLine[1]) && GetVariable(variables, currentLine.substr(currentLine.find('=') + 1)) == 0) // if var is false
			{
				currentLine = SkipToNextStar(file, lineNumber);
			}
			continue;
		}
		else if (currentLine[0] == '{')
		{
			string variable = currentLine.substr(1, currentLine.find('=') - 1);
			int lineNo = FindLineNumStartsWith(variable); // find the variable's line in variables.txt
			writeToFile(lineNo, currentLine.substr(1, currentLine.find('}') - 1));
			continue;
		}
		for (int i = 0; i < currentLine.length(); ++i) {
			if (currentLine[i] == '\\')
			{
				switch (currentLine[++i])
				{
				case '%':
					cin.get();
					continue;
				case 't':
					sleepIsOn = !sleepIsOn; // toggle typing
					continue;
				default:
					break;
				}
			}
			cout << currentLine[i];
			if (sleepIsOn) LocalSleep(SLEEP_DURATION);
		}
		cout << '\n';
	}
	file.close();
}

/* Cycle through exits string, look for one less comma than user's input*/

string getExit(string exits, int input) { /* get exit from string of exits */
	if (input <= 0)
		throw (input);
	string selectedExit = "";
	for (int i = 1; exits[i] != EOF; ++i) {
		if (exits[i] == ',' || exits[i] == ']')
		{
			--input;
			++i;
			if (input > 0)
				selectedExit = "";
		}

		if (input == 0) // this is all in a single selected exit
		{
			for (int i = 1; selectedExit[i] != '}'; ++i)
			{
				if (selectedExit[i] == '{')
				{
					string variable = selectedExit.substr(i + 1, selectedExit.find('}') - (i + 1)); // takeoff{GotChili}

					selectedExit = selectedExit.substr(0, i);

					int lineNo = FindLineNumStartsWith(variable); // find the variable's line in variables.txt
					writeToFile(lineNo, variable + "=1"); // Set the variable to true
					break;
				}
				if (i == selectedExit.length())
				{
					return selectedExit;
				}
			}
			return selectedExit;
		}
		
		selectedExit += exits[i];
	}

	if (input != 1)
		throw(input); // otherwise throw error that input was out of range
	return selectedExit;
}

string getFolder(string& selectedExit, string currentfolder)
{
	string foldername = currentfolder;
	for (int i = selectedExit.length() - 1; i >= 0; --i)
	{
		if (selectedExit[i] == '\\')
		{
			foldername = "";
			for (int n = 0; n < i + 1; ++n)
			{
				foldername += selectedExit[n];
				if (foldername == "PARENTFOLDER")
				{
					foldername = "";
					++n;
				}
			}
		}
	}
	return foldername;
}