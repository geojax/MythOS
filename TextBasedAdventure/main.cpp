#include <iostream>
#include <fstream>
#include <climits>

#include "Header.h"

using namespace std;

int main() {

	cout << "Made with MythOS\n Copyright 2021 Micha Rand and Alex Su\n\n";

	string exits = readFile(START_FILE_STRING); // exits as one long string, commas in between
	string selectedExit;
	string currentFolder = "";
	string sInput = "";
	int iInput;
	bool gameIsRunning = true;

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
			selectedExit = getExit(exits, iInput) + ".txt"; // uses the last string of exits to find the right exit
		}
		catch (int input) {
			cout << "(your input was not an option)\n\n";
			goto GetInput;
		}

		if (currentFolder == getFolder(selectedExit, currentFolder)) //if the current folder isn't changed
		{
			selectedExit = currentFolder + selectedExit;
		}
		currentFolder = getFolder(selectedExit, currentFolder);

		if (selectedExit.substr(0,12) == "PARENTFOLDER")
		{
			selectedExit = selectedExit.substr(13, selectedExit.length());
		}

		try 
		{ 
			exits = readFile(selectedExit); 
		}
		catch (string filename) {
			cout << "(can't find a line in " + filename + " that starts with a '[' opening bracket. Make sure the file exists and links to other files correctly.\
 for now try a different input.)";
			goto GetInput;
		}

		if (selectedExit == "End.txt")
		{
			gameIsRunning = false;
		}
	}
	return 0;
}