#include <iostream>
#include <fstream>
#include "Header.h"

using namespace std;

string getFolder(std::string& selectedExit, std::string currentfolder)
{
	string foldername = currentfolder;
	for (int i = selectedExit.length() - 1; i >= 0; --i)
	{
		if (selectedExit[i] == '\\')
		{
			foldername = "";
			for (int n = 0; n < selectedExit.length() - i + 1; ++n)
			{
				foldername += selectedExit[n];
				if (foldername == "PARENTFOLDER")
				{
					foldername = "";
				}
			}
		}
	}
	return foldername;
}

int main() {

	string exits = readFile(START_FILE_STRING); // exits as one long string, commas in between
	string selectedExit;
	string currentFolder = "";

	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		string sInput = "";
		cin >> sInput;
		int Input;
		getInput(sInput, Input);

		selectedExit = getExit(exits, Input) + ".txt"; // uses the last string of exits to find the right exit
		if (currentFolder == (currentFolder = getFolder(selectedExit, currentFolder)))
		{
			selectedExit = currentFolder + selectedExit;
		}
		exits = readFile(getExit(exits, Input) + ".txt"); // gets the new full string of exits

		if (selectedExit == "End.txt")
		{
			gameIsRunning = false;
		}
	}
	return 0;
}