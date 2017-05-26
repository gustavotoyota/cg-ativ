#ifndef VEC4_HEADER
#define VEC4_HEADER

struct vec2;
struct vec3;

struct vec4 {
	float x, y, z, w;

	vec4();
	vec4(float s);
	vec4(float x, float y, float z = 0.0f, float w = 0.0f);
	vec4(float x, float y, const vec2 &v);
	vec4(const vec2 &v, float z = 0.0f, float w = 0.0f);
	vec4(const vec2 &v1, const vec2 &v2);
	vec4(float x, const vec3 &v);
	vec4(const vec3 &v, float w);

	float len() const;
	float dist(const vec4 &v) const;
	float dot(const vec4 &v) const;
    const vec4 normal() const;

	float operator [](int i) const;
	float &operator [](int i);

    const vec4 operator +(float s) const;
    const vec4 operator -(float s) const;
    const vec4 operator *(float s) const;
    const vec4 operator /(float s) const;
    const vec4 operator +(const vec4 &v) const;
    const vec4 operator -(const vec4 &v) const;
    const vec4 operator *(const vec4 &v) const;
    const vec4 operator /(const vec4 &v) const;

    vec4 &operator +=(float s);
    vec4 &operator -=(float s);
    vec4 &operator *=(float s);
    vec4 &operator /=(float s);
	vec4 &operator +=(const vec4 &v);
	vec4 &operator -=(const vec4 &v);
	vec4 &operator *=(const vec4 &v);
	vec4 &operator /=(const vec4 &v);
};

#endif