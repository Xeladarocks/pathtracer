//
// Created by xelada on 2/9/20.
//

#ifndef PATHTRACER_PLANE_H
#define PATHTRACER_PLANE_H

#include "Object.h"
#include <glm/glm.hpp>

class Plane : public Object {
public:
    glm::vec3 position;
    glm::vec3 normal;
    Material material;

    Plane();

    Plane(glm::vec3 position, glm::vec3 normal, Material material);

    float calculateIntersection(Ray ray);

    glm::vec3 calculateNormal(glm::vec3 collisionPoint);

    Material getMaterial();
};

#endif //PATHTRACER_PLANE_H
