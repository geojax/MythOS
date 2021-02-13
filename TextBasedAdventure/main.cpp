#include <iostream>
#include <fstream>

#include "Header.h"

using namespace std;


int main() {

	string exits = readFile("Map.txt"); // exits as one long string, commas in between
	// we need a throw/catch statement here
	int input = 0;
	cin >> input;

	readFile(getExit(exits, input) + ".txt");

	return 0;
}