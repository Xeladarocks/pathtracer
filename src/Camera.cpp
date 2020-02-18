using namespace std;

#include "inc/Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, float aspectRatio, float fov, Rotation rotation) {
    this->position = position;
    this->rotation = rotation;
    this->fov = fov;
    this->aspectRatio = aspectRatio;
}

Ray Camera::getRay(double x, double y) {
    glm::vec3 direction = glm::normalize(
            glm::vec3((x - 0.5) * (this->fov / 180), (y - 0.5) * (this->fov / 180) * this->aspectRatio, 1));

    direction = direction * rotation.rollMat;
    direction = direction * rotation.pitchMat;
    direction = direction * rotation.yawMat;
    direction = glm::normalize(direction);

    return Ray(position, direction);
}

void Camera::update(float deltaTime) {
    if (this->controls.w) {
        glm::vec3 direction = this->forward * this->rotation.yawMat;
        this->position = this->position + direction * (deltaTime / 50); // * speedModifier
    }
    if (this->controls.s) {
        glm::vec3 direction = this->forward * this->rotation.yawMat;
        this->position = this->position - direction * (deltaTime / 50); // * speedModifier
    }
    if (this->controls.a) {
        glm::vec3 direction = glm::vec3(-1, 0, 0) * this->rotation.yawMat;
        this->position = this->position + direction * (deltaTime / 50); // * speedModifier
    }
    if (this->controls.d) {
        glm::vec3 direction = glm::vec3(1, 0, 0) * this->rotation.yawMat;
        this->position = this->position + direction * (deltaTime / 50); // * speedModifier
    }
    if (this->controls.e) {
        this->position = this->position + glm::vec3(0, 1, 0) * (deltaTime / 50); // * speedModifier
    }
    if (this->controls.q) {
        this->position = this->position - glm::vec3(0, 1, 0) * (deltaTime / 50); // * speedModifier
    }
    if (this->controls.left) {
        this->rotation.yaw -= glm::radians(5.0f);
        this->rotation.updateYawMat();
    }
    if (this->controls.right) {
        this->rotation.yaw += glm::radians(5.0f);
        this->rotation.updateYawMat();
    }
    if (this->controls.down) {
        this->rotation.pitch -= glm::radians(5.0f);
        this->rotation.updatePitchMat();
    }
    if (this->controls.up) {
        this->rotation.pitch += glm::radians(5.0f);
        this->rotation.updatePitchMat();
    }
}