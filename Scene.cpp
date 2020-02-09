using namespace std;

#include <vector>
#include "Scene.h"

Scene::Scene(vector<Object*> objects, vector<Light> lights, Camera camera, Skybox skybox) {
	this->camera = camera;
	this->skybox = skybox;
	this->objects = objects;
	this->lights = lights;
}
void Scene::AddObject(Object* object) {
	this->objects.push_back(object);
}
void Scene::AddObjects(vector<Object*> objects) {
	for (int i = 0; i < objects.size(); i++) {
		this->objects.push_back(objects[i]);
	}
}
void Scene::AddTriangles(vector<Triangle> tris) {
	for (int i = 0; i < tris.size(); i++) {
		this->AddObject(&tris[i]);
	}
}
void Scene::AddLight(Light light) {
	this->lights.push_back(light);
}
void Scene::AddLights(vector<Light> lights) {
	for (int i = 0; i < lights.size(); i++) {
		this->AddLight(lights[i]);
	}
}
void Scene::SetSkybox(Skybox sb) {
	this->skybox = sb;
}
void Scene::SetCamera(Camera cam) {
	this->camera = cam;
}