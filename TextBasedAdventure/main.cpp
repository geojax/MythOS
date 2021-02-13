#include <iostream>
#include <fstream>

#include "Header.h"

using namespace std;


int main() {

	string exits = readFile("Map.txt"); // exits as one long string, commas in between
	// we need a throw/catch statement here

	bool gameRunning;

	if (exits == "Map.txt");
	{
		gameRunning = true;
	}

	while (gameRunning == true)
	{
		string sInput = "";
		cin >> sInput;

		int Input;
		getInput(sInput, Input);

		exits = readFile(getExit(exits, Input) + ".txt");

		if (exits == "End")
		{
			gameRunning == false;
		}

	}

	return 0;
}