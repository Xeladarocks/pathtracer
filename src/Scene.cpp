using namespace std;

#include <vector>
#include <iostream>
#include "inc/Scene.h"
#include <SDL2/SDL.h>

Scene::Scene() {}

void Scene::setSkybox(Skybox *skybox) {
    this->skybox = skybox;
}

void Scene::setCamera(Camera *camera) {
    this->camera = camera;
}

void Scene::addObject(std::unique_ptr<Object> object) {
    this->objects.emplace_back(move(object));
}

void Scene::addObjects(vector<std::unique_ptr<Object>> &vector) {
    for (int i = 0; i < vector.size(); i++)
        this->objects.emplace_back(move(vector[i]));
}

Intersection Scene::castRay(Ray *ray, Renderer *renderer) {
    Object *object = nullptr;
    float closestDistance = -1;

    for (int i = 0; i < this->objects.size(); i++) {
        float dist = this->objects[i].get()->calculateIntersection(ray);

        if (dist >= renderer->min_dist && dist < renderer->max_dist &&
            (dist < closestDistance || closestDistance < 0)) {
            closestDistance = dist;
            object = this->objects[i].get();
        }
    }

    return Intersection({closestDistance > -1, closestDistance, ray->across(closestDistance), object});
}
