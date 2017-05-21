#include <ativ1.h>

#include <math.h>

ivec2::ivec2(): ivec2(0, 0) {
}

ivec2::ivec2(int s): ivec2(s, s) {
}

ivec2::ivec2(int x, int y) {
	this->x = x;
	this->y = y;
}

int ivec2::operator[](int i) const {
	return *((int *)this + i);
}

int & ivec2::operator[](int i) {
	return *((int *)this + i);
}

ivec2 ivec2::operator+(int s) {
    return *this + ivec2(s);
}

ivec2 ivec2::operator-(int s) {
    return *this - ivec2(s);
}

ivec2 ivec2::operator*(int s) {
    return *this * ivec2(s);
}

ivec2 ivec2::operator/(int s) {
    return *this / ivec2(s);
}

ivec2 ivec2::operator+=(int s) {
    return *this = *this + s;
}

ivec2 ivec2::operator-=(int s) {
    return *this = *this - s;
}

ivec2 ivec2::operator*=(int s) {
    return *this = *this * s;
}

ivec2 ivec2::operator/=(int s) {
    return *this = *this / s;
}

ivec2 ivec2::operator+(const ivec2 & v) {
	return ivec2(x + v.x, y + v.y);
}

ivec2 ivec2::operator-(const ivec2 & v) {
	return ivec2(x - v.x, y - v.y);
}

ivec2 ivec2::operator*(const ivec2 & v) {
	return ivec2(x * v.x, y * v.y);
}

ivec2 ivec2::operator/(const ivec2 & v) {
	return ivec2(x / v.x, y / v.y);
}

ivec2 ivec2::operator+=(const ivec2 & v) {
	return *this = *this + v;
}

ivec2 ivec2::operator-=(const ivec2 & v) {
	return *this = *this - v;
}

ivec2 ivec2::operator*=(const ivec2 & v) {
	return *this = *this * v;
}

ivec2 ivec2::operator/=(const ivec2 & v) {
	return *this = *this / v;
}
