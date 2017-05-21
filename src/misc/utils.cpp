#include "utils.h"

#include <fstream>

using namespace std;

std::string readFile(std::string fileName) {
	ifstream input(fileName);
	if (!input.is_open())
		throw;

	string content = "";
	while (input.good()) {
		string line;
		getline(input, line);
		content += line + '\n';
	}
	return content;
}
