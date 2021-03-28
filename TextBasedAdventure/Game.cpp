#include "Game.h"

int Game::GetInput()
{
	char* sInput;
	cout << "> ";
	cin >> sInput;
	cin.ignore(INT_MAX, '\n');

	if (isnumber(sInput))
		return stoi(sInput);

	return -1; // if input is not a number
}

string Game::SkipToNextStar()
{
	string currentLine;
	getline(currentFile, currentLine);
	for (; lineNumber < MAX_LINES_OF_DESCRIPTION && currentLine[0] != '*'; ++lineNumber)
		getline(currentFile, currentLine);
	return currentLine;
}

int Game::ExecuteFirstChar(string line)
{
	char firstChar = line[0];
	if (firstChar == '[') { // reached linker line
		return 0;
		// the game will go on to find a list of exits now
	}

	else if (firstChar == '*') { // starting a conditional
		bool validline = line.find('=') && isalpha(line[1]);
		string var = line.substr(1, line.find('=') - 1);
		if (validline && GetVariable(variables, var) <= 0) // if var is false
		{
			line = SkipToNextStar();
		}
		return 1;
	}

	else if (firstChar == '{') // setting a variable
	{
		string variable = line.substr(1, line.find('=') - 1);
		string value = line.substr(line.find('=') + 1, line.find('}') - line.find('=') - 1);
		SetVariable(variables, variable, value);
		if (!isnumber(value))
			cout << "(variable " + variable + " is not being assigned an integer value. check line" << lineNumber + 1 << ")";

		return 1;
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

void Game::PrintCurrentFile()
{
	//if the file is the end file, end the game
	if (currentFilename == END_FILE_STRING) {
		isRunning = false;
		return;
	}

	cout << '\n';

	string currentLine;

	// until max number of lines, print out each line
	for (; lineNumber < MAX_LINES_OF_DESCRIPTION; ++lineNumber)
	{
		getline(currentFile, currentLine);

		ExecuteFirstChar(currentLine);

		for (int i = 0; i < currentLine.length(); ++i) 
		{
			if (currentLine[i] == '\\') ExecuteCommand(currentLine[++i]);

			cout << currentLine[i];

			if (typingIsOn) LocalSleep(SLEEP_DURATION);
		}

		cout << '\n';
	}

	lineNumber = 0;
}

bool Game::getIsRunning()
{
	return isRunning;
}

bool Game::ChangeFile(string next_file)
{
	currentFile.close();
	currentFile = ifstream(next_file);

	// check if the file exists
	if (!currentFile)
		return false;

	// check if the file has a linker line

}

void Game::ExecuteNode()
{
	//Print File
	PrintCurrentFile();
	
	//Get exits into list of next possible rooms
	
	//Take input

	//switch file to input and repeat
}

Game::Game(string startfile)
{
	FileToStrArray(VARIABLES_PATH, variables);
	currentFilename = startfile;
	currentFile = ifstream(startfile);
	lineNumber = 0;
}