using namespace std;

#include <vector>

#include "headers/Skybox.h"
#include "headers/Camera.h"
#include "headers/Object.h"
#include "headers/Light.h"
#include "headers/Util.h"

class Scene {
    public:
        Camera camera;
        Skybox skybox;
        vector<Object> objects;
        vector<Light> lights;

        Scene(vector<Object> objects=vector<Object>(), vector<Light> lights=vector<Light>(), Camera camera=Camera(), Skybox skybox=defaultSkybox);
        void AddObject(Object object);
        void AddObjects(vector<Object> objects);
        void AddLight(Light light);
        void AddLights(vector<Light> lights);
        void SetSkybox(Skybox sb);
        void SetCamera(Camera cam);
};