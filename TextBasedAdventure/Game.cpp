#pragma once
#include "Game.h"

int Game::GetInput()
{
	cout << "> ";

	string sInput = "";
	
	cin >> sInput;
	cin.ignore(INT_MAX, '\n');
	
	while (!isnumber(sInput))
	{
		cout << "(enter a number)\n";
		cin >> sInput;
	}

	return stoi(sInput);
}

string Game::GetExit(string exits, int exitNum)
{
	string exit;

	for (int i = 1; exitNum > 0 && exits[i] != EOF; ++i)
	{
		if (exits[i] == ',')
		{
			--exitNum;
			exit = "";
		}
		else if (exits[i] == ']')
		{
			--exitNum;
		}
		else
		{
			exit += exits[i];
		}
	}

	if (exitNum > 0)
	{
		cout << "(your input was not an option. try again.)\n";
		return "";
	}
	return exit;
}

string Game::SkipToNextStar()
{
	string currentLine;
	getline(currentFile, currentLine);
	for (; lineNumber < MAX_LINES_OF_DESCRIPTION && currentLine[0] != '*'; ++lineNumber)
		getline(currentFile, currentLine);
	return currentLine;
}

void Game::ExecuteConditional()
{
	/*bool validline = line.find('=') && isalpha(line[1]);
	string var = line.substr(1, line.find('=') - 1);
	if (validline && GetVariable(variables, var) <= 0) // if var is false
	{
		line = SkipToNextStar();
	}*/
}

bool Game::ExecuteSetVariable()
{
	/*string variable = line.substr(1, line.find('=') - 1);
	string value = line.substr(line.find('=') + 1, line.find('}') - line.find('=') - 1);
	SetVariable(variables, variable, value);
	if (!isnumber(value))
		cout << "(variable " + variable + " is not being assigned an integer value. check line" << lineNumber + 1 << ")";
		*/
	return true;
}

int Game::ExecuteFirstChar(string line)
{
	char firstChar = line[0];
	if (firstChar == '[') 
	{ // reached linker line
		return 0;
	}

	else if (firstChar == '*') 
	{ // starting a conditional
		ExecuteConditional();
	}

	else if (firstChar == '{') // setting a variable
	{
		ExecuteSetVariable();
	}
}

void Game::ExecuteCommand(char c)
{
	switch (c)
	{
	case '%':
		cin.get();
		return;
	case 't':
		typingIsOn = !typingIsOn; // toggle typing
		return;
	default:
		return;
	}
}

string Game::FindLinkerLine()
{
	string currentLine;
	for (int i = 0; i < MAX_LINES_OF_DESCRIPTION; ++i)
	{
		getline(currentFile, currentLine);
		
		//if line starts with asterisk, skipToNextStar 

		if (currentLine[0] == '[' && currentLine[currentLine.length() - 1] == ']')
		{
			return currentLine;
		}
	}
	
}

string Game::ExecuteCurrentFileAndGetExits()
{
	//if the file is the end file, end the game
	if (currentFilename == END_FILE_STRING) {
		isRunning = false;
		return "";
	}

	cout << '\n';

	string currentLine;

	// until max number of lines, print out each line
	for (; lineNumber < MAX_LINES_OF_DESCRIPTION; ++lineNumber)
	{
		getline(currentFile, currentLine);

		if (ExecuteFirstChar(currentLine) == 0) break; // for conditionals, variables, and linker lines

		for (int i = 0; i < currentLine.length(); ++i) 
		{
			if (currentLine[i] == '\\') ExecuteCommand(currentLine[++i]);

			cout << currentLine[i];

			if (typingIsOn) LocalSleep(SLEEP_DURATION);
		}

		cout << '\n';
	}

	return currentLine; //should contain linker line
	//lineNumber = 0;
}

int Game::ChangeFile(string next_file)
{
	if (next_file == "End")
		return -1;
	currentFile.close();
	currentFile = ifstream(next_file);

	// check if the file exists
	return (bool)currentFile;
	// check if the file has a linker line
	//FindLinkerLine();
}

void Game::Run()
{
	string strExits;
	string exit = "";
	int input;

	while (isRunning)
	{
		exit = "";

		//Print File
		strExits = ExecuteCurrentFileAndGetExits();

		while (exit == "") // exit equals "" if an error occurs
		{
			input = GetInput();
			exit = GetExit(strExits, input);
		}

		//switch file to input and repeat
		if (ChangeFile(exit) == -1) return;
	}
}

Game::Game(string startfile)
{
	//FileToStrArray(VARIABLES_PATH, variables);
	currentFilename = startfile;
	currentFile = ifstream(startfile);
	lineNumber = 0;
}