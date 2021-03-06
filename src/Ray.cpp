using namespace std;

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/norm.hpp>
#include <random>

#include "inc/Ray.h"
#include "inc/Util.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
    this->origin = origin;
    this->direction = direction;
}

glm::vec3 Ray::across(float distance) {
    return origin + (direction * distance);
}

glm::vec3 Ray::random_in_unit_sphere() {
    glm::vec3 randomDirection = glm::normalize(glm::vec3({
                                                                 randomDouble() * 2 - 1,
                                                                 randomDouble() * 2 - 1,
                                                                 randomDouble() * 2 - 1,
                                                         }));
    return randomDirection;
}

glm::vec3 Ray::diffuse(glm::vec3 normal) {
    glm::vec3 dir = Ray::random_in_unit_sphere();
    if (glm::dot(normal, dir) <= 0) {
        return dir * -1.0f;
    }
    return dir;
}

glm::vec3 Ray::reflect(Ray ray, glm::vec3 normal) {
    return ray.direction - (2 * glm::dot(ray.direction, glm::normalize(normal)) * glm::normalize(normal));
}