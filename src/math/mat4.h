#ifndef MAT4_HEADER
#define MAT4_HEADER

struct vec4;

struct mat4 {
	vec4 rows[4];

    static mat4 translate(const vec3 &v);
    static mat4 rotate(const vec3 &v, float angle);
    static mat4 scale(const vec3 &v);

    static mat4 perspective(float fovY, float aspect, float near, float far);
    static mat4 ortho(float left, float right, float bottom, float top, float near, float far);
    
    mat4();
    mat4(float s);

	const vec4 &operator [](int i) const;
    vec4 &operator [](int i);
    mat4 operator +(const mat4 &m);
    mat4 operator -(const mat4 &m);
    mat4 operator *(const mat4 &m);
};

#endif