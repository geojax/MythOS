#pragma once

#include <fstream>
#include <iostream>
#include <string>
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

#define MAX_LINES_OF_DESCRIPTION 200

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

void PrintFile(string filename) { // prints out description and returns exit options 
	cout << '\n';

	ifstream file(filename);
	string currentLine;
	bool sleepIsOn = false;

	if (filename == END_FILE_STRING) {
		return;
	}
	int lineNumber = 0;
	for (; lineNumber < MAX_LINES_OF_DESCRIPTION; ++lineNumber) {
		getline(file, currentLine);
		if (currentLine[0] == '[') {
			return;
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
	for (int i = 1; exits[i] != ']'; ++i) {
		if (exits[i] == ',')
		{
			--input;
			++i;
			if (input > 0)
				selectedExit = "";
		}

		if (input == 0)
		{
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