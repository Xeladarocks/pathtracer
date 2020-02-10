//
// Created by xelada on 2/9/20.
//

#include "inc/Plane.h"
#include <iostream>

Plane::Plane() {
    normal = glm::vec3();
    material = Material();
}

Plane::Plane(glm::vec3 position, glm::vec3 normal, Material material) {
    this->position = position;
    this->normal = normal;
    this->material = material;
}

float Plane::calculateIntersection(Ray ray) {
    return glm::dot(normal, (ray.origin - position)) / -glm::dot(ray.direction, normal);
}

glm::vec3 Plane::calculateNormal(glm::vec3 collisionPoint) {
    return normal;
}

Material Plane::getMaterial() {
    return material;
}
