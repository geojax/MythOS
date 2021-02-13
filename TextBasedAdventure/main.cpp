#include <iostream>
#include <fstream>

#include "Header.h"

using namespace std;



int main() {

	string exits = readFile(START_FILE_STRING); // exits as one long string, commas in between
	string selectedExit;

	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		string sInput = "";
		cin >> sInput;

		int Input;
		getInput(sInput, Input);
		
		selectedExit = getExit(exits, Input) + ".txt";
		exits = readFile(getExit(exits, Input) + ".txt");
		

		if (selectedExit == "End.txt")
		{
			gameIsRunning = false;
		}

	}

	return 0;
}