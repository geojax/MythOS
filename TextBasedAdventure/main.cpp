#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>

#ifdef _DEBUG
#define DEBUG_LOG(x) std::cout << x << '\n'
#endif
#ifdef NDEBUG
#define DEBUG_LOG(x)
#endif

static std::ifstream file;
static std::unordered_map<std::string, int> userVars;

enum errors {
	MISSING_FILE = 1,
	MISSING_CONTENTS,
	MISSING_LINKER,
	NONEXISTENT_USER_VAR,
	NONNUMERIC_VAR
};

int Init(std::unordered_map<std::string, int>& varMap);
int ParseFile(std::string& description, std::vector<std::string>& exits);
void PrintDescription(const std::string& description);
void FindReplace(std::string& str, char from, char to);
bool HasOnlyDigits(const std::string& s);

int main() {

	std::string filename = "START.txt", path;
	std::string description, exit;
	std::string sInput;
	int input;
	std::vector<std::string> exits;

	Init(userVars);

	while (true) {
		file.open(filename);
		//TODO: File name errors are reported incorrectly.
		if (!file) {
			std::cerr << path + filename << " not found\n";
			DEBUG_LOG("Path: " + path + "\nfilename: " + filename + '\n');
			return MISSING_FILE;
		}

		// exit strings may contain variables to be set

		switch (ParseFile(description, exits)) {
		case errors::MISSING_CONTENTS:
			std::cerr << path + filename + " is missing contents\n";
			return errors::MISSING_CONTENTS;
		case errors::MISSING_LINKER:
			std::cerr << path + filename + " is missing a linker line\n";
			return errors::MISSING_LINKER;
		default:
			break;
		}

		PrintDescription(description);

	GetInput:
		std::cout << "> ";
		std::cin >> sInput;
		for (char c : sInput) {
			if (!isdigit(c)) {
				sInput = "";
				std::cerr << "(input must be a number, try again)\n";
				goto GetInput;
			}
		}

		if (stoi(sInput) > exits.size()) {
			sInput = "";
			std::cerr << "(that input is not implemented, try again)\n";
			goto GetInput;
		}

		input = stoi(sInput);
		exit = exits[input - 1];

		// Parse Exit for variable assignment
		if (exit.find('{') - exit.find('}') != 0) {
			std::string varInfo = exit.substr(exit.find('{') + 1, exit.find('}') - exit.find('{') - 1);
			std::string userVar;
			exit = exit.substr(0, exit.find('{'));
			if (varInfo.find('=') != -1) {
				userVar = varInfo.substr(0, varInfo.find('='));
				std::string userVarVal = varInfo.substr(varInfo.find('=') + 1);
				if (!userVars.count(userVar)) {
					std::cerr << "(variable " << userVar << " doesn't exist. is it in variables.txt?)";
					return errors::NONEXISTENT_USER_VAR;
				}
				if (!HasOnlyDigits(userVarVal)) {
					std::cerr << "Assigning non-numeric value to variable " << userVar;
					return errors::NONNUMERIC_VAR;
				}

				userVars[userVar] = stoi(userVarVal);
			}
			else {
				userVar = varInfo;
				if (!userVars.count(userVar)) {
					std::cerr << "(variable " << userVar << " doesn't exist. is it in variables.txt?)";
					return errors::NONEXISTENT_USER_VAR;
				}
				userVars[userVar] = 1;
			}

		}
		// HOUSEKEEPING
		sInput.clear();
		input = 0;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		exits.clear();
		description = "";
		file.close();

		if (exit == "End") return 0;


		// note to self, in case folder system starts to break at some point: the following should work
		/*if (exit.find('\\') != -1) {
			FindReplace(exit, '\\', '/');
		}*/

		FindReplace(exit, '\\', '/');

		filename = path + exit + ".txt";
		if (exit.find('/') != -1) {
			path += exit.substr(0, exit.find_last_of('/') + 1);
			exit = exit.substr(exit.find_last_of('/') + 1);
		}

		while (path.find("..") != -1) {
			path = path.substr(path.find("..") + 3);
			DEBUG_LOG("Up to parent folder, new path = " + path);
		}
		DEBUG_LOG("Filepath: " + path);
	}
}

int Init(std::unordered_map<std::string, int>& varMap) {
	std::ifstream varFile("variables.txt");
	std::string curLine;
	while (getline(varFile, curLine)) {
		// all variables will start initialized to zero
		std::string userVar = curLine.substr(0, curLine.find('='));
		varMap[userVar] = 0;
	}
	return 0;
}

// description will hold text to be printed out to console for the player
// exits will hold a list of the files that the current file leads to
inline int ParseFile(std::string& description, std::vector<std::string>& exits) {
	std::string contents;
	bool isInConditional = false;

	for (int c = 0; (c = file.get()) != EOF; ++c) {
		contents += c;
	}

	contents = '\n' + contents; // helps to mark the beginning of contents
	if (contents.length() < 2)
		return errors::MISSING_CONTENTS;

	// iterate from end since linker line is closer to end of file
	for (int i = contents.length() - 1; i >= 1; --i) {
		if (contents[i] == '[' && contents[i - 1] == '\n')
			break;
		else if (i == 1)
			return errors::MISSING_LINKER;
	}

	int index; // added '\n' to beginning, helps to have known starting character
	for (index = 1; index < contents.length(); ++index) {
		char curr = contents[index], last = contents[index - 1];
		if (curr == '[' && last == '\n') {
			++index;
			break;
		}

		// conditional, format: *variable OR *variable=value
		if (curr == '*' && last == '\n') {
			if (isalpha(contents[index + 1])) {
				std::string condLine, userVar;
				int condVal = 1; // conditional will be true if the user's variable is equal to this
				char c;

				while ((c = contents[++index]) != '\n') {
					condLine += c;
				}

				// condline without equals sign defaults to check if the variable equals 1
				// with an equals sign it will check against the value on the left of the equals sign
				if (condLine.find('=') != -1) {
					userVar = condLine.substr(0, condLine.find('='));
					std::string sCondVal = condLine.substr(condLine.find('=') + 1); // everything right of equals sign is presumed to be cond value
					if (!HasOnlyDigits(sCondVal)) {
						std::cerr << "Variable " << userVar << " being set to non-numeric value";
						return errors::NONNUMERIC_VAR;
					}
					condVal = stoi(sCondVal);
				}
				else {
					// default conditional, checks if variable is 1 (TODO: non-zero instead of 1)
					userVar = condLine; // because there was no equals sign, the whole line is the user variable
				}

				// check that the variable exists in the userVars map
				if (!userVars.count(userVar)) {
					std::cerr << "Missing variable " << userVar << '\n';
					return errors::NONEXISTENT_USER_VAR;
				}

				DEBUG_LOG("variable " + userVar + " = " << userVars[userVar]);
				if (userVars[userVar] != condVal) {
					// skip until end of conditional block bc conditional was false

					//TODO: ability to test multiple variables at once
					/*for (index; !(contents[index] == '*' && contents[index - 1] == '\n') && !isspace(contents[index + 1]); ++index) {
					}*/
					isInConditional = true;
				}
			}
			else { // character after asterisk was not alpha
				isInConditional = false;
			}
			curr = contents[++index]; last = contents[index - 1];
		}

		if (!isInConditional)
			description += curr;
	}

	std::string currentExit;
	for (; index < contents.length(); ++index) {
		if (contents[index] == ',' || contents[index] == ']') {
			exits.push_back(currentExit);
			currentExit = "";
		}
		else {
			currentExit += contents[index];
		}
	}
	return 0;
}

inline void PrintDescription(const std::string& description) {
	bool isTyping = false;
	char last = '\n';
	for (char curr : description) {
		if (last == '\\') {
			switch (curr)
			{
			case '%':
				std::cin.get();
				break;
			case 'T':
				isTyping = true;
				break;
			case 't':
				isTyping = false;
				break;
			}
		}
		else if (curr != '\\') {
			if (isTyping) {
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			std::cout << curr;
		}
		last = curr;
	}
}

void FindReplace(std::string& str, char from, char to) {
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == from) {
			str[i] = to;
		}
	}
}

//https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
bool HasOnlyDigits(const std::string& s) {
	return s.find_first_not_of("0123456789") == std::string::npos;
}