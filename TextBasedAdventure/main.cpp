#include <iostream>
#include <fstream>

using namespace std;
#include "PlotNode.h"
#include "Rooms.h"

string readFile(string fileName){ //prints out dscrp and gets exit choices 

	string myText = "";
	ifstream MyReadFile("Map.txt");


	while (myText[0] != '[') {
		cout << myText << "\n";
		getline(MyReadFile, myText);
	}

	return myText;
	MyReadFile.close();
}



int main() {

	string exits = readFile("Map.txt");
	int n = 0;

	for (int i = 1; exits[i] != ']'; ++i) {
		if (exits[i] == ',')
		{
			++n;
		}
		exits[n] += exits[i];
	} 

	int input = 0;

	cin >> input;

	ifstream MyReadFile2(exits[input - 1] + ".txt");
	getline(MyReadFile2, myText);
	cout << myText;

	return 0;
}