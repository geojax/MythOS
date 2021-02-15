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
	// look for a bracket in the first 200 lines
	for (int i = 0; i <= MAX_LINES_OF_DESCRIPTION; ++i)
	{
		getline(RoomFile, myText);
		if (myText[0] == '[') {
			myText = "";
			RoomFile.clear();
			RoomFile.seekg(0);
			break;
		}
		if (i == MAX_LINES_OF_DESCRIPTION)
			throw(filename);
	}

	int i = 0;
	while (myText[0] != '[') {
		if (myText[0] == '%')
		{
			cin.get(); // wait for input if line starts with '%'
			myText = myText.substr(1, myText.length());
		}
		cout << myText << '\n';
		getline(RoomFile, myText);
		/*if (++i > MAX_LINES_OF_DESCRIPTION) {
			cout << "(" + filename + " is missing a '[' closing bracket in the first 200 lines. does the file exist?\n\n";
			return "";
		}*/
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