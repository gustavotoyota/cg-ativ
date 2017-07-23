#ifndef MAT3_HEADER
#define MAT3_HEADER

#include "vec3.h"

struct mat4;

struct mat3 {
	vec3 cols[3];
    
    mat3();
    mat3(const mat4 &m);

	const vec3 &operator [](int i) const;
    vec3 &operator [](int i);
};

#endif
