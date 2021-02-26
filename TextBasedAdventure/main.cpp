#include <iostream>
#include <fstream>
#include "Header.h"
#include "Variable.h"
using namespace std;

int main() {

	cout << "Made with MythOS\n Copyright 2021 Micha Rand and Alex Su\n\n";
	cout << GetVariable("joma");
	bool gameIsRunning = true;

	string exits = FindLinkerLine(START_FILE_STRING); // exits as one long string, commas in between

	PrintFile(START_FILE_STRING);

	string currentFile; // the file MythOS will print to console
	string currentFolder = ""; // the folder path to be prepended to all files until PARENTFOLDER\ is added

	string sInput = ""; // input variables
	int iInput;

	while (gameIsRunning)
	{

	GetInput:
		cout << ">";
		cin >> sInput;
		cin.ignore(INT_MAX, '\n');

		try
		{
			iInput = stoi(sInput);
		}
		catch (exception e) {
			cout << "(enter a number)\n\n";
			goto GetInput;
		}

		try
		{
			currentFile = getExit(exits, iInput) + ".txt"; // uses the last string of exits to find the right exit
		}
		catch (int input) {
			cout << "(your input was not an option)\n\n";
			goto GetInput;
		}

		if (currentFolder == getFolder(currentFile, currentFolder)) //if the current folder isn't changed
		{
			currentFile = currentFolder + currentFile;
		}
		currentFolder = getFolder(currentFile, currentFolder);

		if (currentFile.substr(0, 12) == "PARENTFOLDER")
		{
			currentFile = currentFile.substr(13, currentFile.length());
		}

		try
		{
			exits = FindLinkerLine(currentFile);
		}
		catch (string filename) {
			cout << "(can't find a line in " + filename + " that starts with a '[' opening bracket. Make sure the file exists and links to other files correctly.\
 for now try a different input.)";
			goto GetInput;
		}
		PrintFile(currentFile);
		if (currentFile == "End.txt")
		{
			gameIsRunning = false;
		}
	}
	return 0;
}