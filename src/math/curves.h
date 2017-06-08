#ifndef CURVES_HEADER
#define CURVES_HEADER

#include <vector>

struct vec3;

vec3 cubicBezier(std::vector<vec3> p, float t);

#endif