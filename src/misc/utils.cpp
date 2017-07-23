#include "utils.h"

#include <fstream>
#include <algorithm>

using namespace std;

float sqr(float s) {
    return s * s;
}

float randBetween(float a, float b) {
    return a + (b - a) * rand() / (float)RAND_MAX;
}

float clamp(float min, float max, float value) {
    return ::max(min, ::min(max, value));
}

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
