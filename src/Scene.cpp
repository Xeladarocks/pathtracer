using namespace std;

#include <vector>
#include <iostream>
#include "inc/Scene.h"

Scene::Scene() {}

void Scene::setSkybox(Skybox *skybox) {
    this->skybox = skybox;
}

void Scene::setCamera(Camera *camera) {
    this->camera = camera;
}

void Scene::addObject(std::unique_ptr<Object> object) {
    objects.emplace_back(std::move(object));
}

Intersection Scene::castRay(Ray ray) {
    Object *object = nullptr;
    float closestDistance = -1;

    for (int i = 0; i < this->objects.size(); i++) {
        float dist = this->objects[i].get()->calculateIntersection(ray);
        if (dist >= 0 && (dist < closestDistance || closestDistance < 0)) {
            closestDistance = dist;
            object = this->objects[i].get();
        }
    }

    return Intersection({closestDistance > -1, closestDistance, ray.across(closestDistance), object});
}