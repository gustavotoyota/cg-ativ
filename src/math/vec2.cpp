#include <cg-ativ.h>

#include <math.h>

vec2::vec2(): vec2(0.0f, 0.0f) {
}

vec2::vec2(float s): vec2(s, s) {
}

vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

float vec2::len() const {
	return (float)sqrt(dot(*this));
}

float vec2::dist(const vec2 & v) const {
	return (*this - v).len();
}

float vec2::dot(const vec2 & v) const {
	return x * v.x + y * v.y;
}

float vec2::cross(const vec2 & v) const {
	return x * v.y - y * v.x;
}

const vec2 vec2::normal() const {
	return *this / len();
}

float vec2::operator[](int i) const {
	return *((float *)this + i);
}

float & vec2::operator[](int i) {
	return *((float *)this + i);
}

const vec2 vec2::operator+(float s) const {
    return *this + vec2(s);
}

const vec2 vec2::operator-(float s) const {
    return *this - vec2(s);
}

const vec2 vec2::operator*(float s) const {
    return *this * vec2(s);
}

const vec2 vec2::operator/(float s) const {
    return *this / vec2(s);
}

const vec2 vec2::operator+(const vec2 & v) const {
	return vec2(x + v.x, y + v.y);
}

const vec2 vec2::operator-(const vec2 & v) const {
	return vec2(x - v.x, y - v.y);
}

const vec2 vec2::operator*(const vec2 & v) const {
	return vec2(x * v.x, y * v.y);
}

const vec2 vec2::operator/(const vec2 & v) const {
	return vec2(x / v.x, y / v.y);
}

vec2 &vec2::operator+=(float s) {
    return *this += vec2(s);
}

vec2 &vec2::operator-=(float s) {
    return *this -= vec2(s);
}

vec2 &vec2::operator*=(float s) {
    return *this *= vec2(s);
}

vec2 &vec2::operator/=(float s) {
    return *this /= vec2(s);
}

vec2 &vec2::operator+=(const vec2 & v) {
	return *this = *this + v;
}

vec2 &vec2::operator-=(const vec2 & v) {
	return *this = *this - v;
}

vec2 &vec2::operator*=(const vec2 & v) {
	return *this = *this * v;
}

vec2 &vec2::operator/=(const vec2 & v) {
	return *this = *this / v;
}
