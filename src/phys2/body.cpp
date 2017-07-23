#include "body.h"

Body::Body() {
    shape = Shape();

    pos = vec2();
    vel = vec2();
    force = vec2();

    mass = 1;
    invMass = 1;

    damp = 1;
    restit = 1;
}

const Shape &Body::getShape() const {
    return shape;
}
void Body::setShape(const Shape & shape) {
    this->shape = shape;
}

const vec2 & Body::getPos() const {
    return pos;
}
void Body::setPos(const vec2 & pos) {
    this->pos = pos;
}
const vec2 & Body::getVel() const {
    return vel;
}
void Body::setVel(const vec2 & vel) {
    this->vel = vel;
}

float Body::getMass() const {
    return mass;
}
void Body::setMass(float mass) {
    this->mass = mass;
    invMass = mass == 0 ? 0 : 1 / mass;
}
float Body::getInvMass() const {
    return invMass;
}

float Body::getDamp() const {
    return damp;
}
void Body::setDamp(float damp) {
    this->damp = damp;
}
float Body::getRestit() const {
    return restit;
}
void Body::setRestit(float restit) {
    this->restit = restit;
}

void * Body::getData() {
    return data;
}

void Body::setData(void * data) {
    this->data = data;
}

std::list<Body>::iterator Body::getIter() {
    return iter;
}

void Body::applyForce(vec2 force) {
    this->force += force;
}