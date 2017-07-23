#include "shape.h"

#define _USE_MATH_DEFINES
#include <math.h>

Shape::Shape() {
    type = Type::RECT;
    half = vec2(1);
}

Shape::Shape(vec2 half) {
    type = Type::RECT;
    this->half = half;
}

Shape::Shape(float radius) {
    type = Type::CIRCLE;
    this->radius = radius;
}

float Shape::getArea() {
    switch (type) {
    case Type::RECT:
        return half.x * half.y * 4;
    case Type::CIRCLE:
        return (float)M_PI * radius * radius;
    }
    return 0;
}
