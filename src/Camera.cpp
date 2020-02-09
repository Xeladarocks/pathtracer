using namespace std;

#include "Camera.h"

Camera::Camera(glm::vec3 nposition, Rotation nrotation) {
	this->position = nposition;
	this->rotation = nrotation;
}