#ifndef VEC2_HEADER
#define VEC2_HEADER

struct vec2 {
	float x, y;

	vec2();
	vec2(float s);
	vec2(float x, float y);

    float angle() const;
	float len() const;
    float lenSqr() const;
	float dist(const vec2 &v) const;
    float distSqr(const vec2 &v) const;
	float dot(const vec2 &v) const;
	float cross(const vec2 &v) const;
    const vec2 abs() const;
    const vec2 sign() const;
    const vec2 sqrt() const;
    const vec2 normal() const;
    const vec2 pow(float exp) const;
    const vec2 clamp(vec2 min, vec2 max) const;

	float operator [](int i) const;
	float &operator [](int i);
};

const vec2 operator +(float s, const vec2 &v);
const vec2 operator -(float s, const vec2 &v);
const vec2 operator *(float s, const vec2 &v);
const vec2 operator /(float s, const vec2 &v);

const vec2 operator +(const vec2 &v, float s);
const vec2 operator -(const vec2 &v, float s);
const vec2 operator *(const vec2 &v, float s);
const vec2 operator /(const vec2 &v, float s);

const vec2 operator +(const vec2 &v1, const vec2 &v2);
const vec2 operator -(const vec2 &v1, const vec2 &v2);
const vec2 operator *(const vec2 &v1, const vec2 &v2);
const vec2 operator /(const vec2 &v1, const vec2 &v2);

vec2 &operator +=(vec2 &v, float s);
vec2 &operator -=(vec2 &v, float s);
vec2 &operator *=(vec2 &v, float s);
vec2 &operator /=(vec2 &v, float s);

vec2 &operator +=(vec2 &v1, const vec2 &v2);
vec2 &operator -=(vec2 &v1, const vec2 &v2);
vec2 &operator *=(vec2 &v1, const vec2 &v2);
vec2 &operator /=(vec2 &v1, const vec2 &v2);

bool operator ==(const vec2 &v1, const vec2 &v2);
bool operator !=(const vec2 &v1, const vec2 &v2);

#endif