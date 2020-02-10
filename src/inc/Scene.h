#pragma once
#ifndef SCENE_H
#define SCENE_H

using namespace std;

#include <vector>

#include "Camera.h"
#include "Skybox.h"
#include "Object.h"
#include "Util.h"

class Scene {
public:
    Skybox *skybox;
    Camera *camera;
    std::vector<std::unique_ptr<Object>> objects;

    Scene();

    void setSkybox(Skybox *skybox);

    void setCamera(Camera *camera);

    void addObject(std::unique_ptr<Object> object);

    Intersection castRay(Ray ray);
};

#endif