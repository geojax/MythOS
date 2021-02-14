#pragma once

#include <fstream>
#include <iostream>
#include <string>
#define START_FILE_STRING "START.txt"
#define END_FILE_STRING "End.txt"

using namespace std;

#define MAX_LINES_OF_DESCRIPTION 200
string readFile(string filename) { // prints out description and returns exit choices 

	string myText = "";
	ifstream RoomFile(filename);
	if (filename == END_FILE_STRING) {
		return "";
	}

	int i = 0;
	while (myText[0] != '[') {
		cout << myText << '\n';
		getline(RoomFile, myText);
		if (++i > MAX_LINES_OF_DESCRIPTION) {
			cout << "ERROR: Description for " + filename + " is too long, missing an end, or the file doesn't exist!";
			return "";
		}
	}

	return myText; // myText holds the exits as a string
	RoomFile.close();
}

int getInput(string sInput, int &iInput) {
	//try {
		iInput = stoi(sInput);
		if (iInput > 3 || iInput < 1)
			throw(iInput);
	//}
	/*catch(exception e) {
		cout << "ERROR: " << e.what() << '\n';
	}
	catch (int iInput) {
		cout << iInput << " is out of input range!";
	}*/
	//return iInput;
}
/*Cycle through exits string, look for one less comma than user's input*/

string getExit(string exits, int input) { /* get exit from string of exits */
	if (input <= 0)
		throw (input);
	string selectedExit = "";
	for (int i = 1; exits[i] != ']'; ++i) {
		if (exits[i] == ',')
		{
			--input;
			++i;
			if (input > 0)
				selectedExit = "";
		}

		if (input == 0)
		{
			return selectedExit;
		}
		
		selectedExit += exits[i];
	}
	if (input != 1)
		throw(input); // otherwise throw error that input was out of range
	return selectedExit;
}