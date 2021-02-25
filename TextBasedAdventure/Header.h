#pragma once

#include <fstream>
#include <iostream>
#include <string>
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

	ifstream RoomFile(filename);
	char myChars[2]; // stores current char and last char to check for commands like \t and \%
	bool sleepIsOn = false;

	if (filename == END_FILE_STRING) {
		return;
	}

	while ((myChars[0] = RoomFile.get()) != EOF) { // loop thru roomfile 
		if (myChars[1] == '\n' && myChars[0] == '[') {
			return;
		}
		if (myChars[0] == '\\')
		{
			myChars[0] = RoomFile.get();
			switch (myChars[0])
			{
			case '%':
				cin.get();
				continue;
			case 't':
				sleepIsOn = !sleepIsOn; // change status of typewriter effect being on or off
				continue;
			default:
				break;
			}
		}
		myChars[1] = myChars[0];
		cout << myChars[0];
		if (sleepIsOn) LocalSleep(SLEEP_DURATION);
	}
	RoomFile.close();
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