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
			for (int n = 0; n < i + 1; ++n)
			{
				foldername += selectedExit[n];
				if (foldername == "PARENTFOLDER")
				{
					foldername = "";
					++n; //to remove slash????????????
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
		int Input;

	GetInput:
		cin >> sInput;
		try
		{
			//getInput(sInput, Input);
			Input = stoi(sInput);
		}
		catch (exception e) {
			cout << "(enter a number)\n\n";
			goto GetInput;
		}
		catch (int i) {
			cout << "(" << i << " is out of range)\n\n";
		}

		try 
		{
			selectedExit = getExit(exits, Input) + ".txt"; // uses the last string of exits to find the right exit
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

		exits = readFile(selectedExit);

		if (selectedExit == "End.txt")
		{
			gameIsRunning = false;
		}
	}
	return 0;
}