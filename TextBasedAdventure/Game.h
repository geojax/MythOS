#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Variable.h"
#include "Header.h"
using namespace std;

class Game
{
	bool isRunning = true;
	bool typingIsOn;
	string currentFilename; // current file
	string currentFolder;
	ifstream currentFile; // current file
	string variables[100];// array of variables
	int lineNumber;
	string FindLinkerLine();
	string SkipToNextStar(); // return next line that starts with asterisk
public:

	Game(string startfile);
	void ExecuteCommand(char c); // execute code for a user's command within a file, e.g. \t or \%
	void ExecuteNode(); // open file, print it, take input, and get information for the next file
	int ExecuteFirstChar(string line);
	void PrintCurrentFile(); // print file
	bool ChangeFile(string next_file); // close current file, open a new one
	int GetInput();
	bool getIsRunning();
};

