#ifndef VEC3_HEADER
#define VEC3_HEADER

struct vec2;

struct vec3 {
	float x, y, z;
    
	vec3();
	vec3(float s);
	vec3(float x, float y, float z = 0.0f);
	vec3(float x, const vec2 &v);
	vec3(const vec2 &v, float z = 0.0f);
    
    float len();
    float dist(const vec3 &v);
    float dot(const vec3 &v);
    vec3 cross(const vec3 &v);
    vec3 normal();

	float operator [](int i) const;
	float &operator [](int i);

    vec3 operator +(float s);
    vec3 operator -(float s);
    vec3 operator *(float s);
    vec3 operator /(float s);
    vec3 operator +=(float s);
    vec3 operator -=(float s);
    vec3 operator *=(float s);
    vec3 operator /=(float s);

    vec3 operator +(const vec3 &v);
    vec3 operator -(const vec3 &v);
    vec3 operator *(const vec3 &v);
    vec3 operator /(const vec3 &v);
    vec3 operator +=(const vec3 &v);
    vec3 operator -=(const vec3 &v);
    vec3 operator *=(const vec3 &v);
    vec3 operator /=(const vec3 &v);
};

#endif