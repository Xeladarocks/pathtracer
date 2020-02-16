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

Ray Ray::GenerateRandomRay(glm::vec3 origin, glm::vec3 normal, glm::vec3 reflectDirection, float diffuse) {
    // Create a random direction
    glm::vec3 randomDirection = glm::normalize(glm::vec3({
                                                                 randomDouble() * 2 - 1,
                                                                 randomDouble() * 2 - 1,
                                                                 randomDouble() * 2 - 1,
                                                         }));

    // If the random direction we generated is pointing into the surface, we negate it so it points within 90 degrees of the surface normal
    if (glm::dot(normal, randomDirection) <= 0) {
        randomDirection = randomDirection * -1.0f;
    }

    // Create a new direction, based on the random direction and the reflect direction, based on how diffuse the material is, by interpolating the directions.
    glm::vec3 rayDirection = glm::mix(reflectDirection, randomDirection, diffuse);

    return Ray(
            origin + (rayDirection * 0.01f),
            rayDirection
    );
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