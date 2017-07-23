#include "contact.h"

Contact::Contact() {
}

Contact::Contact(Body * bodyA, Body * bodyB, vec2 normal, vec2 penet) {
    this->bodyA = bodyA;
    this->bodyB = bodyB;
    this->normal = normal;
    this->penet = penet;
}
