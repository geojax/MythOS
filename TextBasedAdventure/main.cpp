#include <iostream>
#include <fstream>
#include "Header.h"

using namespace std;

int main() {

	cout << "Made with MythOS\n Copyright 2021 Micha Rand and Alex Su\n\n";

	bool gameIsRunning = true;

	string exits = FindLinkerLine(START_FILE_STRING); // exits as one long string, commas in between

	PrintFile(START_FILE_STRING);

	string currentFile; // the file MythOS will print to console
	string currentFolder = ""; // the folder path to be prepended to all files until PARENTFOLDER\ is added

	string sInput = ""; // input variables
	int iInput;

	while (currentFile != END_FILE_STRING)
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
			string exit = getExit(exits, iInput); // contains entire path if it's there
			currentFile = exit.substr(exit.find_last_of('\\') + 1) + ".txt"; // uses the last string of exits to find the right exit
			string getFolderResult = getFolder(exit);
			if (getFolderResult.substr(0, 12) == "PARENTFOLDER")
			{
				currentFolder = getFolderResult.substr(13);

			}
			else {
				currentFolder += getFolderResult;
			}
		}
		catch (int input) {
			cout << "(your input was not an option)\n\n";
			goto GetInput;
		}
		try
		{
			exits = FindLinkerLine(currentFolder + currentFile);
		}
		catch (string filename) {
			cout << "(can't find a line in " + filename + " that starts with a '[' opening bracket. Make sure the file exists and links to other files correctly.\
 for now try a different input.)";
			goto GetInput;
		}
		PrintFile(currentFolder + currentFile);
	}
	return 0;
}