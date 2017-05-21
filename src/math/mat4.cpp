#include <ativ1.h>

#include <math.h>

mat4 mat4::translate(const vec3 & v) {
    mat4 res;

    res[3][0] = v.x;
    res[3][1] = v.y;
    res[3][2] = v.z;

    return res;
}

mat4 mat4::rotate(const vec3 & v, float angle) {
    mat4 res;

    float c = cos(angle);
    float s = sin(angle);
    float n = 1.0f - c;

    res[0][0] = c + n * v.x * v.x;
    res[0][1] = n * v.x * v.y + s * v.z;
    res[0][2] = n * v.x * v.z - s * v.y;

    res[1][0] = n * v.y * v.x - s * v.z;
    res[1][1] = c + n * v.y * v.y;
    res[1][2] = n * v.y * v.z + s * v.x;

    res[2][0] = n * v.z * v.x + s * v.y;
    res[2][1] = n * v.z * v.y - s * v.x;
    res[2][2] = c + n * v.z * v.z;

    return res;
}

mat4 mat4::scale(const vec3 & v) {
    mat4 res;

    res[0][0] = v.x;
    res[1][1] = v.y;
    res[2][2] = v.z;

    return res;
}

mat4 mat4::perspective(float fovY, float aspect, float near, float far) {
    mat4 res;

    float temp = (float)tan(fovY / 2.0f);

    res[0][0] = 1.0f / (aspect * temp);
    res[1][1] = 1.0f / temp;
    res[2][2] = -(far + near) / (far - near);

    res[2][3] = -1.0f;

    res[3][2] = -(2.0f * far * near) / (far - near);

    res[3][3] = 0.0f;

    return res;
}

mat4 mat4::ortho(float left, float right, float bottom, float top, float near, float far) {
    mat4 res;

    res[0][0] = 2.0f / (right - left);
    res[1][1] = 2.0f / (top - bottom);
    res[2][2] = -2.0f / (far - near);

    res[3][0] = -(right + left) / (right - left);
    res[3][1] = -(top + bottom) / (top - bottom);
    res[3][2] = -(far + near) / (far - near);

    res[3][3] = 1.0f;

    return res;
}

mat4::mat4(): mat4(1) {
}

mat4::mat4(float s) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            rows[i][j] = i == j ? s : 0;
}

const vec4 & mat4::operator[](int i) const {
	return rows[i];
}

vec4 &mat4::operator [](int i) {
    return rows[i];
}

mat4 mat4::operator +(const mat4 &m) {
    mat4 res;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = rows[i][j] + m[i][j];
    return res;
}

mat4 mat4::operator -(const mat4 &m) {
    mat4 res;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = rows[i][j] - m[i][j];
    return res;
}

mat4 mat4::operator *(const mat4 &m) {
    mat4 res(0);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				res[j][i] += rows[k][i] * m[j][k];
	return res;
}