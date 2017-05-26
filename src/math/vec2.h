#ifndef VEC2_HEADER
#define VEC2_HEADER

struct vec2 {
	float x, y;

	vec2();
	vec2(float s);
	vec2(float x, float y);

	float len() const;
	float dist(const vec2 &v) const;
	float dot(const vec2 &v) const;
	float cross(const vec2 &v) const;
    const vec2 normal() const;

	float operator [](int i) const;
	float &operator [](int i);

    const vec2 operator +(float s) const;
    const vec2 operator -(float s) const;
    const vec2 operator *(float s) const;
    const vec2 operator /(float s) const;
    const vec2 operator +(const vec2 &v) const;
    const vec2 operator -(const vec2 &v) const;
    const vec2 operator *(const vec2 &v) const;
    const vec2 operator /(const vec2 &v) const;

    vec2 &operator +=(float s);
    vec2 &operator -=(float s);
    vec2 &operator *=(float s);
    vec2 &operator /=(float s);
	vec2 &operator +=(const vec2 &v);
	vec2 &operator -=(const vec2 &v);
	vec2 &operator *=(const vec2 &v);
	vec2 &operator /=(const vec2 &v);
};

#endif