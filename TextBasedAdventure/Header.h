#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define MAX_LINES_OF_DESCRIPTION 200
string readFile(string filename) { // prints out description and returns exit choices 

	string myText = "";
	ifstream RoomFile(filename);
	int i = 0;
	while (myText[0] != '[') {
		cout << myText << '\n';
		getline(RoomFile, myText);
		if (++i > MAX_LINES_OF_DESCRIPTION) {
			cout << "ERROR: Description for " + filename + ".txt is too long or missing end statement!";
			return "";
		}
	}

	return myText; // myText holds the exits as a string
	RoomFile.close();
}

int getInput(string sInput, int &iInput) {
	try {
		iInput = stoi(sInput);
	}
	catch(exception e) {
		cout << "ERROR: " << e.what() << '\n';
	}
	return iInput;
}
/*Cycle through exits string, look for one less comma than user's input*/
			/* add each character to selectedExit
			if we reach a comma, selectedExit becomes an empty string
			Subtract 1 from input at each comma
			if input == 0, return "[selectedExit].txt"*/
string getExit(string exits, int input) { /* get exit from string of exits */
	string selectedExit = "";
	for (int i = 1; exits[i] != ']'; ++i) {
		if (exits[i] == ',')
		{
			--input;
			if (input > 0)
				selectedExit = "";
		}
		if (input == 0)
		{
			return selectedExit;
		}
		selectedExit += exits[i];
	}
}