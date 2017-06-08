#include "curves.h"

#include <math.h>

#include "vec3.h"

vec3 cubicBezier(std::vector<vec3> p, float t) {
	return
		p[0] * pow(t, 0) * pow(1 - t, 3) * 1 +
		p[1] * pow(t, 1) * pow(1 - t, 2) * 3 +
		p[2] * pow(t, 2) * pow(1 - t, 1) * 3 +
		p[3] * pow(t, 3) * pow(1 - t, 0) * 1;
}