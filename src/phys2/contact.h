#ifndef PHYS2_CONTACT_HEADER
#define PHYS2_CONTACT_HEADER

#include <math/vec2.h>

class Body;

struct Contact {
    Body *bodyA;
    Body *bodyB;
    vec2 normal;
    vec2 penet;

    Contact();
    Contact(Body *bodyA, Body *bodyB, vec2 normal, vec2 penet);
};

#endif