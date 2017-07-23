#ifndef PHYS2_BODY_HEADER
#define PHYS2_BODY_HEADER

#include <list>

#include <math/vec2.h>

#include "shape.h"

class Body {
    friend class World;
public:
    Body();

    const Shape &getShape() const;
    void setShape(const Shape &shape);

    const vec2 &getPos() const;
    void setPos(const vec2 &pos);
    const vec2 &getVel() const;
    void setVel(const vec2 &vel);

    float getMass() const;
    void setMass(float mass);
    float getInvMass() const;

    float getDamp() const;
    void setDamp(float damp);
    float getRestit() const;
    void setRestit(float restit);

    void *getData();
    void setData(void *data);
    std::list<Body>::iterator getIter();

    void applyForce(vec2 force);
private:
    Shape shape;

    vec2 pos;
    vec2 vel;

    float mass;
    float invMass;

    float damp;
    float restit;

    vec2 force;

    void *data;
    std::list<Body>::iterator iter;
};

#endif