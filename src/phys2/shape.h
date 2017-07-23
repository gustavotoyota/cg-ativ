#ifndef PHYS2_SHAPE_HEADER
#define PHYS2_SHAPE_HEADER

#include <math/vec2.h>

class Shape {
public:
    struct Type {
        enum Enum {
            RECT, 
            CIRCLE
        };
    };

    Type::Enum type;
    union {
        vec2 half;
        float radius;
    };

    Shape();
    Shape(vec2 half);
    Shape(float radius);

    float getArea();
};


#endif
