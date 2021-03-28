#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Variable.h"
#include <climits>

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

/* Cycle through exits string, look for one less comma than user's input*/

string getExit(string exits, int input, string* variables) { /* get exit from string of exits */
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
					string variable = selectedExit.substr(i + 1, selectedExit.find('}') - (i + 1));

					selectedExit = selectedExit.substr(0, i);

					SetVariable(variables, variable, "1");
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

string getFolder(string& selectedExit)
{
	string foldername;// = currentfolder;
	foldername = selectedExit.substr(0, selectedExit.find_last_of('\\') + 1);
	return foldername;
}