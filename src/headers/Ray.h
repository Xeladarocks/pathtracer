#ifndef RAY_H
#define RAY_H

using namespace std;

#include "../glm/glm.hpp"

class Ray {
    public:
        glm::vec3 position;
        glm::vec3 direction;

        Ray(glm::vec3 nposition, glm::vec3 ndirection);
        static Ray GenerateRandomRay(glm::vec3 origin, glm::vec3 normal, glm::vec3 reflectDirection, float diffuse);
};

#endif