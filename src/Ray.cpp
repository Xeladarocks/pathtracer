using namespace std;

#include <glm/glm.hpp>

#include "headers/Ray.h"

Ray::Ray(glm::vec3 nposition, glm::vec3 ndirection) {
    this->position = nposition;
    this->direction = ndirection;
}