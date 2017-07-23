#include "mat3.h"

#include <math.h>

#include "mat4.h"

mat3::mat3() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cols[i][j] = i == j ? 1 : 0;
}

mat3::mat3(const mat4 &m) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cols[i][j] = m[i][j];
}

const vec3 & mat3::operator[](int i) const {
	return cols[i];
}

vec3 &mat3::operator [](int i) {
    return cols[i];
}
