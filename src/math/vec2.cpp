#include <ativ1.h>

#include <math.h>

vec2::vec2(): vec2(0.0f, 0.0f) {
}

vec2::vec2(float s): vec2(s, s) {
}

vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

float vec2::len() {
	return (float)sqrt(dot(*this));
}

float vec2::dist(const vec2 & v) {
	return (*this - v).len();
}

float vec2::dot(const vec2 & v) {
	return x * v.x + y * v.y;
}

float vec2::cross(const vec2 & v) {
	return x * v.y - y * v.x;
}

vec2 vec2::normal() {
	return *this / len();
}

float vec2::operator[](int i) const {
	return *((float *)this + i);
}

float & vec2::operator[](int i) {
	return *((float *)this + i);
}

vec2 vec2::operator+(float s) {
    return *this + vec2(s);
}

vec2 vec2::operator-(float s) {
    return *this - vec2(s);
}

vec2 vec2::operator*(float s) {
    return *this * vec2(s);
}

vec2 vec2::operator/(float s) {
    return *this / vec2(s);
}

vec2 vec2::operator+=(float s) {
    return *this += vec2(s);
}

vec2 vec2::operator-=(float s) {
    return *this -= vec2(s);
}

vec2 vec2::operator*=(float s) {
    return *this *= vec2(s);
}

vec2 vec2::operator/=(float s) {
    return *this /= vec2(s);
}

vec2 vec2::operator+(const vec2 & v) {
	return vec2(x + v.x, y + v.y);
}

vec2 vec2::operator-(const vec2 & v) {
	return vec2(x - v.x, y - v.y);
}

vec2 vec2::operator*(const vec2 & v) {
	return vec2(x * v.x, y * v.y);
}

vec2 vec2::operator/(const vec2 & v) {
	return vec2(x / v.x, y / v.y);
}

vec2 vec2::operator+=(const vec2 & v) {
	return *this = *this + v;
}

vec2 vec2::operator-=(const vec2 & v) {
	return *this = *this - v;
}

vec2 vec2::operator*=(const vec2 & v) {
	return *this = *this * v;
}

vec2 vec2::operator/=(const vec2 & v) {
	return *this = *this / v;
}
