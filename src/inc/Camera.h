#pragma once

#ifndef CAMERA_H
#define CAMERA_H

using namespace std;

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include "Util.h"
#include "Rotation.h"

class Camera {
public:
    glm::vec3 position;
    Rotation rotation;
    float aspectRatio;
    float fov;

    Camera(glm::vec3 position, float aspectRatio, float fov, Rotation rotation);

    Ray getRay(double x, double y);
};

#endif