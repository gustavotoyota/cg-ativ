#ifndef PHYS2_WORLD_HEADER
#define PHYS2_WORLD_HEADER

#include <list>
#include <unordered_map>

#include <math/vec2.h>

#include "body.h"
#include "shape.h"
#include "contact.h"

class World {
public:
    World();

    void step();
    void addBody(Body body);
    void applyForce(vec2 force);

    std::list<Body> &getBodies();
    float getTimeStep();
    void setTimeStep(float timeStep);
    int getIterations();
    void setIterations(int iterations);
    float getCorrectFactor();
    void setCorrectFactor(float correctFactor);
    void setContactCallback(bool (*contactCallback)(Contact *contact));
private:
    int iterations;
    float timeStep;
    float deltaTime;
    float correctFactor;

    std::list<Body> bodies;

    void integration();
    void detection();
    void resolution();
    void correction();

    std::list<Contact> contacts;
    bool (*contactCallback)(Contact *contact);
    std::unordered_map<Shape::Type::Enum,
        std::unordered_map<Shape::Type::Enum,
        bool (World::*)(Body *, Body *, Contact *)>> contactFunc;

    bool contactRectRect(Body *bodyA, Body *bodyB, Contact *contact);
    bool contactRectCircle(Body *bodyA, Body *bodyB, Contact *contact);
    bool contactCircleCircle(Body *bodyA, Body *bodyB, Contact *contact);
};

#endif