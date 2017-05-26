#include <cg-ativ.h>

#include <math.h>

vec3::vec3(): vec3(0.0f, 0.0f, 0.0f) {
}

vec3::vec3(float s): vec3(s, s, s) {
}

vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3::vec3(float x, const vec2 & v): vec3(x, v.x, v.y) {
}

vec3::vec3(const vec2 & v, float z): vec3(v.x, v.y, z) {
}

float vec3::len() const {
    return (float)sqrt(dot(*this));
}

float vec3::dist(const vec3 &v) const {
    return (*this - v).len();
}

float vec3::dot(const vec3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

const vec3 vec3::cross(const vec3 &v) const {
    return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

const vec3 vec3::normal() const {
    return *this / len();
}

float vec3::operator[](int i) const {
	return *((float *)this + i);
}

float & vec3::operator[](int i) {
	return *((float *)this + i);
}

const vec3 vec3::operator+(float s) const {
    return *this + vec3(s);
}

const vec3 vec3::operator-(float s) const {
    return *this - vec3(s);
}

const vec3 vec3::operator*(float s) const {
    return *this * vec3(s);
}

const vec3 vec3::operator/(float s) const {
    return *this / vec3(s);
}

const vec3 vec3::operator +(const vec3 &v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
}

const vec3 vec3::operator -(const vec3 &v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
}

const vec3 vec3::operator *(const vec3 &v) const {
    return vec3(x * v.x, y * v.y, z * v.z);
}

const vec3 vec3::operator /(const vec3 &v) const {
    return vec3(x / v.x, y / v.y, z / v.z);
}

vec3 &vec3::operator+=(float s) {
    return *this += vec3(s);
}

vec3 &vec3::operator-=(float s) {
    return *this -= vec3(s);
}

vec3 &vec3::operator*=(float s) {
    return *this *= vec3(s);
}

vec3 &vec3::operator/=(float s) {
    return *this /= vec3(s);
}

vec3 &vec3::operator +=(const vec3 &v) {
	return *this = *this + v;
}

vec3 &vec3::operator -=(const vec3 &v) {
	return *this = *this - v;
}

vec3 &vec3::operator*=(const vec3 & v) {
	return *this = *this * v;
}

vec3 &vec3::operator /=(const vec3 &v) {
	return *this = *this / v;
}
