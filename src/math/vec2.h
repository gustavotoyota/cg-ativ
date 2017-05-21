#ifndef VEC2_HEADER
#define VEC2_HEADER

struct vec2 {
	float x, y;

	vec2();
	vec2(float s);
	vec2(float x, float y);

	float len();
	float dist(const vec2 &v);
	float dot(const vec2 &v);
	float cross(const vec2 &v);
	vec2 normal();

	float operator [](int i) const;
	float &operator [](int i);

    vec2 operator +(float s);
    vec2 operator -(float s);
    vec2 operator *(float s);
    vec2 operator /(float s);
    vec2 operator +=(float s);
    vec2 operator -=(float s);
    vec2 operator *=(float s);
    vec2 operator /=(float s);

	vec2 operator +(const vec2 &v);
	vec2 operator -(const vec2 &v);
	vec2 operator *(const vec2 &v);
	vec2 operator /(const vec2 &v);
	vec2 operator +=(const vec2 &v);
	vec2 operator -=(const vec2 &v);
	vec2 operator *=(const vec2 &v);
	vec2 operator /=(const vec2 &v);
};

#endif