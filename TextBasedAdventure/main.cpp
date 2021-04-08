#include <iostream>
#include <fstream>
#include "Header.h"
#include "Variable.h"
#include "Game.h"
using namespace std;

int main() {

	cout << "Made with MythOS\n Copyright 2021 Micha Rand and Alex Su\n\n";

	Game game(START_FILE_STRING);
	game.Run();
	return 0;
}