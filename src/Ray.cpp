using namespace std;

#include <glm/glm.hpp>
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