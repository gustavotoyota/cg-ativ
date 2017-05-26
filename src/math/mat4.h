#ifndef MAT4_HEADER
#define MAT4_HEADER

struct vec4;

struct mat4 {
	vec4 cols[4];

    static const mat4 translate(const vec3 &v);
    static const mat4 rotate(const vec3 &v, float angle);
    static const mat4 scale(const vec3 &v);

    static const mat4 lookAt(const vec3 &eye, const vec3 &at, vec3 up = vec3(0.0f, 0.0f, 1.0f));

    static const mat4 perspective(float fovY, float aspect, float near, float far);
    static const mat4 ortho(float left, float right, float bottom, float top, float near, float far);
    
    mat4();
    mat4(float s);

    const mat4 transpose() const;

	const vec4 &operator [](int i) const;
    vec4 &operator [](int i);

    const mat4 operator +(float s) const;
    const mat4 operator -(float s) const;
    const mat4 operator *(float s) const;
    const mat4 operator +(const mat4 &m) const;
    const mat4 operator -(const mat4 &m) const;
    const mat4 operator *(const mat4 &m) const;

    mat4 &operator +=(float s);
    mat4 &operator -=(float s);
    mat4 &operator *=(float s);
    mat4 &operator +=(const mat4 &m);
    mat4 &operator -=(const mat4 &m);
    mat4 &operator *=(const mat4 &m);
};

#endif