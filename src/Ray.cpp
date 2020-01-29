using namespace std;

#include "glm/glm.hpp"
#include <random>

#include "headers/Ray.h"
#include "headers/Util.h"

Ray::Ray(glm::vec3 nposition, glm::vec3 ndirection) {
    this->position = nposition;
    this->direction = ndirection;
}

Ray Ray::GenerateRandomRay(glm::vec3 origin, glm::vec3 normal, glm::vec3 reflectDirection, float diffuse) {
	// Create a random direction
	glm::vec3 randomDirection = glm::normalize(glm::vec3({
		rand_float(0.0f, 1.0f)*2-1,
		rand_float(0.0f, 1.0f)*2-1,
		rand_float(0.0f, 1.0f)*2-1,
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