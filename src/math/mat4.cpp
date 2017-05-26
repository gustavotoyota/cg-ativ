#include <cg-ativ.h>

#include <math.h>

const mat4 mat4::translate(const vec3 & v) {
    mat4 res;

    res[3][0] = v.x;
    res[3][1] = v.y;
    res[3][2] = v.z;

    return res;
}

const mat4 mat4::rotate(const vec3 & v, float angle) {
    mat4 res;

    float c = cos(angle);
    float s = sin(angle);
    float n = 1.0f - c;

    res[0][0] = n * v.x * v.x + c;
    res[0][1] = n * v.x * v.y + s * v.z;
    res[0][2] = n * v.x * v.z - s * v.y;

    res[1][0] = n * v.y * v.x - s * v.z;
    res[1][1] = n * v.y * v.y + c;
    res[1][2] = n * v.y * v.z + s * v.x;

    res[2][0] = n * v.z * v.x + s * v.y;
    res[2][1] = n * v.z * v.y - s * v.x;
    res[2][2] = n * v.z * v.z + c;

    return res;
}

const mat4 mat4::scale(const vec3 & v) {
    mat4 res;

    res[0][0] = v.x;
    res[1][1] = v.y;
    res[2][2] = v.z;

    return res;
}

const mat4 mat4::lookAt(const vec3 & eye, const vec3 & at, vec3 up) {
    mat4 res;

    vec3 zaxis = (eye - at).normal();
    vec3 xaxis = up.cross(zaxis).normal();
    vec3 yaxis = zaxis.cross(xaxis);

    res[0] = vec4(xaxis, -xaxis.dot(eye));
    res[1] = vec4(yaxis, -yaxis.dot(eye));
    res[2] = vec4(zaxis, -zaxis.dot(eye));
    res[3] = vec4(0, 0, 0, 1);

    return res.transpose();
}

const mat4 mat4::perspective(float fovY, float aspect, float near, float far) {
    mat4 res;

    float aux = (float)tan(fovY / 2.0f);

    res[0][0] = 1.0f / (aspect * aux);
    res[1][1] = 1.0f / aux;
    res[2][2] = -(far + near) / (far - near);

    res[2][3] = -1.0f;

    res[3][2] = -(2.0f * far * near) / (far - near);

    res[3][3] = 0.0f;

    return res;
}

const mat4 mat4::ortho(float left, float right, float bottom, float top, float near, float far) {
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
            cols[i][j] = i == j ? s : 0;
}

const mat4 mat4::transpose() const {
    mat4 res;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = cols[j][i];

    return res;
}

const vec4 & mat4::operator[](int i) const {
	return cols[i];
}

vec4 &mat4::operator [](int i) {
    return cols[i];
}

const mat4 mat4::operator+(float s) const {
    mat4 res;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = cols[i][j] + s;

    return res;
}

const mat4 mat4::operator-(float s) const {
    mat4 res;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = cols[i][j] - s;

    return res;
}

const mat4 mat4::operator*(float s) const {
    mat4 res;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = cols[i][j] * s;

    return res;
}

const mat4 mat4::operator +(const mat4 &m) const {
    mat4 res;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = cols[i][j] + m[i][j];

    return res;
}

const mat4 mat4::operator -(const mat4 &m) const {
    mat4 res;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res[i][j] = cols[i][j] - m[i][j];

    return res;
}

const mat4 mat4::operator *(const mat4 &m) const {
    mat4 res(0);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				res[j][i] += cols[k][i] * m[j][k];

	return res;
}

mat4 & mat4::operator+=(float s) {
    return *this = *this + s;
}

mat4 & mat4::operator-=(float s) {
    return *this = *this - s;
}

mat4 & mat4::operator*=(float s) {
    return *this = *this * s;
}

mat4 & mat4::operator+=(const mat4 & m) {
    return *this = *this + m;
}

mat4 & mat4::operator-=(const mat4 & m) {
    return *this = *this - m;
}

mat4 & mat4::operator*=(const mat4 & m) {
    return *this = *this * m;
}
