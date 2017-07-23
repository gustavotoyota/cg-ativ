#include "vec2.h"

#include <math.h>

#include <misc/utils.h>

vec2::vec2(): vec2(0, 0) {
}

vec2::vec2(float s) : vec2(s, s) {
}

vec2::vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

float vec2::angle() const {
    return atan2(x, y);
}

float vec2::len() const {
    return (float)::sqrt(lenSqr());
}

float vec2::lenSqr() const {
    return x * x + y * y;
}

float vec2::dist(const vec2 & v) const {
    return (*this - v).len();
}

float vec2::distSqr(const vec2 & v) const {
    return (*this - v).lenSqr();
}

float vec2::dot(const vec2 & v) const {
    return x * v.x + y * v.y;
}

float vec2::cross(const vec2 & v) const {
    return x * v.y - y * v.x;
}

const vec2 vec2::abs() const {
    return vec2(::abs(x), ::abs(y));
}

const vec2 vec2::sign() const {
    return vec2(x < 0 ? -1.0f : 1.0f, y < 0 ? -1.0f : 1.0f);
}

const vec2 vec2::sqrt() const {
    return vec2(::sqrt(x), ::sqrt(y));
}

const vec2 vec2::normal() const {
    return *this / len();
}

const vec2 vec2::pow(float exp) const {
    return vec2(::pow(x, exp), ::pow(y, exp));
}

const vec2 vec2::clamp(vec2 min, vec2 max) const {
    return vec2(::clamp(min.x, max.x, x), ::clamp(min.y, max.y, y));
}

float & vec2::operator[](int i) {
    return *((float *)this + i);
}

float vec2::operator[](int i) const {
    return *((float *)this + i);
}

const vec2 operator +(float s, const vec2 &v) {
    return vec2(s) + v;
}

const vec2 operator -(float s, const vec2 &v) {
    return vec2(s) - v;
}

const vec2 operator *(float s, const vec2 &v) {
    return vec2(s) * v;
}

const vec2 operator /(float s, const vec2 &v) {
    return vec2(s) / v;
}

const vec2 operator +(const vec2 &v, float s) {
    return v + vec2(s);
}

const vec2 operator -(const vec2 &v, float s) {
    return v - vec2(s);
}

const vec2 operator *(const vec2 &v, float s) {
    return v * vec2(s);
}

const vec2 operator /(const vec2 &v, float s) {
    return v / vec2(s);
}

const vec2 operator +(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.x + v2.x, v1.y + v2.y);
}

const vec2 operator -(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.x - v2.x, v1.y - v2.y);
}

const vec2 operator *(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.x * v2.x, v1.y * v2.y);
}

const vec2 operator /(const vec2 &v1, const vec2 &v2) {
    return vec2(v1.x / v2.x, v1.y / v2.y);
}

vec2 &operator +=(vec2 &v, float s) {
    return v = v + s;
}

vec2 &operator -=(vec2 &v, float s) {
    return v = v - s;
}

vec2 &operator *=(vec2 &v, float s) {
    return v = v * s;
}

vec2 &operator /=(vec2 &v, float s) {
    return v = v / s;
}

vec2 &operator +=(vec2 &v1, const vec2 &v2) {
    return v1 = v1 + v2;
}

vec2 &operator -=(vec2 &v1, const vec2 &v2) {
    return v1 = v1 - v2;
}

vec2 &operator *=(vec2 &v1, const vec2 &v2) {
    return v1 = v1 * v2;
}

vec2 &operator /=(vec2 &v1, const vec2 &v2) {
    return v1 = v1 / v2;
}

bool operator ==(const vec2 &v1, const vec2 &v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator !=(const vec2 &v1, const vec2 &v2) {
    return v1.x != v2.x || v1.y != v2.y;
}