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
	bool typingIsOn = false;
	string currentFilename; // current file
	string currentFolder;
	ifstream currentFile; // current file
	string variables[100];// array of variables
	int lineNumber;

	int ChangeFile(string next_file); // close current file, open a new one
	void ExecuteCommand(char c); // execute code for a user's command within a file, e.g. \t or \%
	void ExecuteConditional();
	int ExecuteFirstChar(string line);
	bool ExecuteSetVariable(); // sets a variable, returns whether successful
	string ExecuteCurrentFileAndGetExits(); // print file and return last line, i.e. linker line

	string FindLinkerLine();
	string GetExit(string exits, int input);
	int GetInput();
	string SkipToNextStar(); // return next line that starts with asterisk

public:
	Game(string startfile);
	void Run();
};

