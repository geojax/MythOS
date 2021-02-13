#include <iostream>
#include <fstream>
#include "PlotNode.h"
#include "Rooms.h"

using namespace std;
#define MAX_LINES_OF_DESCRIPTION 200
string readFile(string filename){ // prints out description and returns exit choices 

	string myText = "";
	ifstream RoomFile(filename);
	int i = 0;
	while (myText[0] != '[') {
		cout << myText;
		getline(RoomFile, myText);
		if (++i > 200) {
			cout << "ERROR: Description for " + filename + ".txt is too long or missing end statement!";
			return "";
		}
	}

	return myText; // myText holds the exits as a string
	RoomFile.close();
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
			selectedExit = "";
		}
		if (input == 0)
		{
			return selectedExit;
		}
		selectedExit += exits[i];
	}
}

int main() {

	string exits = readFile("Map.txt"); // exits as one long string, commas in between
	// we need a throw/catch statement here
	int input = 0;
	cin >> input;

	readFile(getExit(exits, input) + ".txt");

	return 0;
}