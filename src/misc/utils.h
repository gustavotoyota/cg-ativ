#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <string>

float sqr(float s);
float randBetween(float a, float b);
float clamp(float min, float max, float value);
std::string readFile(std::string fileName);

#endif