#include <ativ1.h>

#include <math.h>

vec4::vec4(): vec4(0.0f, 0.0f, 0.0f, 0.0f) {
}

vec4::vec4(float s) : vec4(s, s, s, s) {
}

vec4::vec4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4::vec4(float x, float y, const vec2 & v): vec4(x, y, v.x, v.y) {
}

vec4::vec4(const vec2 &v, float z, float w): vec4(v.x, v.y, z, w) {
}

vec4::vec4(const vec2 & v1, const vec2 & v2): vec4(v1.x, v1.y, v2.x, v2.y) {
}

vec4::vec4(float x, const vec3 & v): vec4(x, v.x, v.y, v.z) {
}

vec4::vec4(const vec3 & v, float w): vec4(v.x, v.y, v.z, w) {
}

float vec4::len() {
	return (float)sqrt(dot(*this));
}

float vec4::dist(const vec4 &v) {
	return (*this - v).len();
}

float vec4::dot(const vec4 &v) {
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

vec4 vec4::normal() {
	return *this / len();
}

float vec4::operator[](int i) const {
	return *((float *)this + i);
}

float & vec4::operator[](int i) {
	return *((float *)this + i);
}

vec4 vec4::operator+(float s) {
    return *this + vec4(s);
}

vec4 vec4::operator-(float s) {
    return *this - vec4(s);
}

vec4 vec4::operator*(float s) {
    return *this * vec4(s);
}

vec4 vec4::operator/(float s) {
    return *this / vec4(s);
}

vec4 vec4::operator+=(float s) {
    return *this += vec4(s);
}

vec4 vec4::operator-=(float s) {
    return *this -= vec4(s);
}

vec4 vec4::operator*=(float s) {
    return *this *= vec4(s);
}

vec4 vec4::operator/=(float s) {
    return *this /= vec4(s);
}

vec4 vec4::operator +(const vec4 &v) {
	return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
}

vec4 vec4::operator -(const vec4 &v) {
	return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
}

vec4 vec4::operator *(const vec4 &v) {
	return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
}

vec4 vec4::operator /(const vec4 &v) {
	return vec4(x / v.x, y / v.y, z / v.z, w / v.w);
}

vec4 vec4::operator +=(const vec4 &v) {
	return *this = *this + v;
}

vec4 vec4::operator -=(const vec4 &v) {
	return *this = *this - v;
}

vec4 vec4::operator*=(const vec4 & v) {
	return *this = *this * v;
}

vec4 vec4::operator /=(const vec4 &v) {
	return *this = *this / v;
}
