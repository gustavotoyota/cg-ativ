#include "world.h"

#include <algorithm>

#include <misc/utils.h>

using namespace std;

World::World() {
    iterations = 6;
    timeStep = 1 / 60.0f;
    correctFactor = 0.5f;

    contactCallback = [] (Contact *contact) -> bool {
        return true;
    };

    contactFunc[Shape::Type::RECT][Shape::Type::RECT] = &World::contactRectRect;
    contactFunc[Shape::Type::RECT][Shape::Type::CIRCLE] = &World::contactRectCircle;
    contactFunc[Shape::Type::CIRCLE][Shape::Type::CIRCLE] = &World::contactCircleCircle;
}

void World::step() {
    for (int i = 1; i <= iterations; ++i) {
        integration();
        detection();
        resolution();
        correction();
    }
}
void World::addBody(Body body) {
    bodies.push_back(body);
    bodies.back().iter = prev(bodies.end());
}
void World::applyForce(vec2 force) {
    for (auto iter = bodies.begin(); iter != bodies.end(); ++iter)
        iter->applyForce(force);
}

std::list<Body>& World::getBodies() {
    return bodies;
}
float World::getTimeStep() {
    return timeStep;
}
void World::setTimeStep(float timeStep) {
    this->timeStep = timeStep;
    deltaTime = timeStep / iterations;
}
int World::getIterations() {
    return iterations;
}
void World::setIterations(int iterations) {
    this->iterations = iterations;
    deltaTime = timeStep / iterations;
}
float World::getCorrectFactor() {
    return correctFactor;
}
void World::setCorrectFactor(float correctFactor) {
    this->correctFactor = correctFactor;
}
void World::setContactCallback(bool (*contactCallback)(Contact *contact)) {
    this->contactCallback = contactCallback;
}

void World::integration() {
    float deltaTime = timeStep / iterations;
    for (auto iter = bodies.begin(); iter != bodies.end(); ++iter) {
        Body &body = *iter;
        body.vel += body.force * timeStep * body.invMass;
        body.vel *= pow(body.damp, deltaTime);
        body.pos += body.vel * deltaTime;
        body.force = vec2();
    }
}
void World::detection() {
    contacts.clear();
    for (auto iterA = bodies.begin(); iterA != bodies.end(); ++iterA) {
        for (auto iterB = next(iterA); iterB != bodies.end(); ++iterB) {
            Body *bodyA = &*iterA, *bodyB = &*iterB;
            Shape::Type::Enum shapeA = bodyA->shape.type, shapeB = bodyB->shape.type;
            if (shapeA > shapeB) {
                swap(bodyA, bodyB);
                swap(shapeA, shapeB);
            }

            Contact contact;
            if ((this->*(this->contactFunc[shapeA][shapeB]))(bodyA, bodyB, &contact))
                if (contactCallback(&contact))
                    contacts.push_back(contact);
        }
    }
}
void World::resolution() {
    for (auto iter = contacts.begin(); iter != contacts.end(); ++iter) {
        Contact contact = *iter;
        Body *bodyA = contact.bodyA, *bodyB = contact.bodyB;
        float invMassSum = bodyA->invMass + bodyB->invMass;
        if (invMassSum == 0)
            continue;

        vec2 relVel = bodyB->vel - bodyA->vel;
        float normalVel = relVel.dot(contact.normal);
        if (normalVel > 0)
            continue;

        float restit = min(bodyA->restit, bodyB->restit);
        float impulseLen = -(1 + restit) * normalVel / invMassSum;
        vec2 impulse = contact.normal * impulseLen;
        bodyA->vel -= impulse * bodyA->invMass;
        bodyB->vel += impulse * bodyB->invMass;
    }
}
void World::correction() {
    for (auto iter = contacts.begin(); iter != contacts.end(); ++iter) {
        Contact contact = *iter;
        Body *bodyA = contact.bodyA, *bodyB = contact.bodyB;
        float invMassSum = bodyA->invMass + bodyB->invMass;
        if (invMassSum == 0)
            continue;

        vec2 factor = contact.penet * (correctFactor / invMassSum);
        contact.bodyA->pos -= factor * bodyA->invMass;
        contact.bodyB->pos += factor * bodyB->invMass;
    }
}

bool World::contactRectRect(Body * bodyA, Body * bodyB, Contact *contact) {
    vec2 diff = bodyB->pos - bodyA->pos;
    vec2 diffAbs = diff.abs();
    vec2 penetAbs = bodyA->shape.half + bodyB->shape.half - diffAbs;
    if (penetAbs.x < 0 || penetAbs.y < 0)
        return false;

    vec2 sign = diff.sign();
    vec2 penet = penetAbs * sign;
    vec2 normal = sign;
    if (penetAbs.x > penetAbs.y)
        penet.x = normal.x = 0;
    else
        penet.y = normal.y = 0;

    *contact = Contact(bodyA, bodyB, normal, penet);

    return true;
}
bool World::contactRectCircle(Body * bodyA, Body * bodyB, Contact *contact) {
    vec2 minA = bodyA->pos - bodyA->shape.half;
    vec2 maxA = bodyA->pos + bodyA->shape.half;
    vec2 closest = bodyB->pos.clamp(minA, maxA);
    if (closest.distSqr(bodyB->pos) > sqr(bodyB->shape.radius))
        return false;

    vec2 normal;
    if (closest == bodyB->pos) {
        vec2 sign = (bodyB->pos - bodyA->pos).sign();
        vec2 corner = bodyA->pos + sign * bodyA->shape.half;
        vec2 cornerDiff = corner - closest;
        vec2 cornerDiffAbs = cornerDiff.abs();
        if (cornerDiffAbs.x < cornerDiffAbs.y) {
            closest.x = corner.x;
            normal = vec2(sign.x, 0);
        } else {
            closest.y = corner.y;
            normal = vec2(0, sign.y);
        }
    } else
        normal = (bodyB->pos - closest).normal();

    vec2 radius = normal * bodyB->shape.radius;
    vec2 diff = bodyB->pos - closest;
    vec2 penet = radius - diff;

    *contact = Contact(bodyA, bodyB, normal, penet);

    return true;
}
bool World::contactCircleCircle(Body * bodyA, Body * bodyB, Contact *contact) {
    float depth = bodyA->shape.radius + bodyB->shape.radius - bodyB->pos.dist(bodyA->pos);
    if (depth < 0)
        return false;

    vec2 normal = bodyA->pos != bodyB->pos ? (bodyB->pos - bodyA->pos).normal() : vec2(0, 1);
    vec2 penet = normal * depth;

    *contact = Contact(bodyA, bodyB, normal, penet);

    return true;
}
