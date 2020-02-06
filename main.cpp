#include "pch.h"
using namespace std;

// disable deprecation warnings
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <ctime>
#include <cmath> 
#include <random>
#include <thread>
#include <future>

// broad purpose
#include "Color.h"
#include "../glm/glm.hpp"
#include "../glm/gtx/string_cast.hpp"

// project specific
#include "Sphere.h"
#include "Triangle.h"
#include "Ray.h"
#include "Util.h"
#include "Material.h"
#include "Object.h"
#include "Camera.h"
#include "Skybox.h"
#include "Light.h"
#include "Scene.h"
#include "Renderer.h"

vector<Color> renderChunk(int thread_count, int x1, int x2, int y1, int y2, Scene scene, Renderer renderer);

int main() {
	int sampling;
	cout << "Samples: ";
	cin >> sampling;

	Scene scene; // scene
	Renderer renderer(scene, 600, 600, sampling, 16, 8, 0);

	Camera camera(glm::vec3(0, 1.5, -2)); // camera
	scene.SetCamera(camera);
	Skybox skybox(Color(63, 178, 232), Color(225, 244, 252), Color(225, 244, 252), true, Color(0, 0, 0)); // skybox
	scene.SetSkybox(skybox);

	/** OBJECTS **/
	Sphere sphere = Sphere(glm::vec3(0, 1, 5), 1, Color(255, 255, 255), Material(1, 1, 0, 0));
	scene.AddObject(&sphere);

	/*vector<Triangle> quad;
	quad = newQuad(glm::vec3(-100,0,-100),glm::vec3(-100,0,100),glm::vec3(100,0,100),glm::vec3(10Color(255, 255, 255)0,0,-100), Material(0, 1, 1, 0), Color(255, 255, 255));*/
	vector<Triangle> tris;
	tris.push_back(Triangle(glm::vec3(-100, 0, -100), glm::vec3(-100, 0, 100), glm::vec3(100, 0, 100), Color(255, 255, 255), Material(0, 1, 1, 0)));
	tris.push_back(Triangle(glm::vec3(100, 0, 100), glm::vec3(100, 0, -100), glm::vec3(-100, 0, -100), Color(255, 255, 255), Material(0, 1, 1, 0)));
	for (int i = 0; i < tris.size(); i++) {
		scene.AddObject(&tris[i]);
	}

	vector<Triangle> light;
	float lh = 4.0f; // light height
	float ls = 3.0f; // light size
	light.push_back(Triangle(glm::vec3(ls/2.0, lh, 5.0+ls/2.0), glm::vec3(ls/2.0, lh, 5.0-ls/2.0), glm::vec3(-ls/2, lh, 5-ls/2), Color(255, 255, 255), Material(0, 0, 0, 1)));
	light.push_back(Triangle(glm::vec3(-ls/2.0, lh, 5.0-ls/2.0), glm::vec3(-ls/2.0, lh, 5.0+ls/2.0), glm::vec3(ls/2, lh, 5+ls/2), Color(255, 255, 255), Material(0, 0, 0, 1)));
	for (int i = 0; i < light.size(); i++) {
		scene.AddObject(&light[i]);
	}
	/** ------- **/

	for (int o = 0; o < renderer.scene->objects.size(); o++) {
		cout << scene.objects[o]->GetName() << " " << glm::to_string(scene.objects[o]->position) << "\n";
	}

	FILE *fp;
	string file_loc = "../output/main" + to_string(std::time(nullptr)) + ".ppm";
	cout << "output: " << file_loc << "\n";
	fp = fopen(file_loc.c_str(), "w");
	fprintf(fp, "P3\n%d %d\n255\n", renderer.width, renderer.height);

	cout << "dimensions: " << renderer.width << "x" << renderer.height << "\n";

	std::vector<std::future<vector<Color>>> threads;
	for (int t = 0; t < renderer.thread_count; t++) {
		int x = int((float)t * (renderer.width / (float)renderer.thread_count));
		int width = int(ceil(renderer.width / (float)renderer.thread_count));

		threads.push_back(async(std::launch::async, renderChunk, t, x, 0, x + width, renderer.height, scene, renderer));
	}
	int total = 0;
	for (auto&& fut : threads) {
		total++;
		vector<Color> cols = fut.get();
		for (int c = 0; c < cols.size(); c++) {
			fprintf(fp, "%d %d %d\n", (int)cols[c].r, (int)cols[c].g, (int)cols[c].b);
		}
	}

	cout << "A total of " << total << "threads have completed\n";

	fclose(fp);
	cout << '\r' << "100% complete";
	return 0;
}

vector<Color> renderChunk(int thread_id, int x1, int y1, int x2, int y2, Scene scene, Renderer renderer) {
	vector<Color> total_colors;
	for (int x = x1; x < x2; x++) {
		//if (x % (renderer.height / 20) == 0)cout << '\r' << (renderer.height - (float) x) / renderer.height * 100 << "% complete" << std::flush;
		for (int y = y2; y > y1; y--) {
			/*for (int y = renderer.height; y > 0; y--) {
				for (int x = 0; x < renderer.width; x++) {*/
			Color col;
			for (int s = 0; s < renderer.samples; s++) {
				float u, v;
				u = x + rand_float(0.0f, 1.0f);
				v = y + rand_float(0.0f, 1.0f);
				glm::vec3 direction = renderer.CanvasToViewport(glm::vec2(v, renderer.height-u));
				/*direction = scene.camera.rotation.roll * direction;
				direction = scene.camera.rotation.pitch * direction;
				direction = scene.camera.rotation.yaw * direction;*/
				Color traced_color = renderer.renderPixel(Ray(scene.camera.position, direction));
				col = col.add(traced_color);
			}
			col = col.divide((float)renderer.samples);
			total_colors.push_back(col);
		}
	}
	cout << '\r' << thread_id / renderer.thread_count * 100 << "% complete" << flush;
	return total_colors;
}