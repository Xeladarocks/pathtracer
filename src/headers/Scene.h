#ifndef SCENE_H
#define SCENE_H

using namespace std;

#include <vector>

#include "Camera.h"
#include "Skybox.h"
#include "Object.h"
#include "Light.h"

class Scene {
    public:
        Camera camera;
        Skybox skybox;
        vector<Object*> objects;
        vector<Light> lights;

        Scene(vector<Object*> objects=vector<Object*>(), vector<Light> lights=vector<Light>(), Camera camera=Camera(), Skybox skybox=Skybox());
        void AddObject(Object* object);
        void AddObjects(vector<Object*> objects);
        void AddLight(Light light);
        void AddLights(vector<Light> lights);
        void SetSkybox(Skybox sb);
        void SetCamera(Camera cam);
};

#endif