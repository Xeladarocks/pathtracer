#include "inc/Object.h"

Object::Object() {}

float Object::calculateIntersection(Ray *ray) {
    throw "Object::calculateIntersection() called";
}

glm::vec3 Object::calculateNormal(glm::vec3 collisionPoint) {
    throw "Object::calculateNormal() called";
}

Material Object::getMaterial() {
    throw "Object::getMaterial() called";
}

glm::vec3 Object::calculateUVCoordinates(glm::vec3 collisionPoint, glm::vec3 normal) {
    throw "Object::calculateUVCoordinates() called";
}