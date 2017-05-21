#ifndef IVEC2_HEADER
#define IVEC2_HEADER

struct ivec2 {
	int x, y;

    ivec2();
    ivec2(int s);
    ivec2(int x, int y);

    int operator [](int i) const;
    int &operator [](int i);

    ivec2 operator +(int s);
    ivec2 operator -(int s);
    ivec2 operator *(int s);
    ivec2 operator /(int s);
    ivec2 operator +=(int s);
    ivec2 operator -=(int s);
    ivec2 operator *=(int s);
    ivec2 operator /=(int s);

    ivec2 operator +(const ivec2 &v);
    ivec2 operator -(const ivec2 &v);
    ivec2 operator *(const ivec2 &v);
    ivec2 operator /(const ivec2 &v);
    ivec2 operator +=(const ivec2 &v);
    ivec2 operator -=(const ivec2 &v);
    ivec2 operator *=(const ivec2 &v);
    ivec2 operator /=(const ivec2 &v);
};

#endif