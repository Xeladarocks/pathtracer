using namespace std;

#include "headers/Camera.h"

Camera::Camera(glm::vec3 nposition, Rotation nrotation) {
    this->position = nposition;
    this->rotation = nrotation;
}