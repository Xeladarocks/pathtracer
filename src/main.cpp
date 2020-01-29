using namespace std;

#include <iostream>
#include <string>
#include <ctime>
#include <random>

// broad purpose
#include "headers/Color.h"
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"

// project specific
#include "headers/Sphere.h"
#include "headers/Ray.h"
#include "headers/Util.h"
#include "headers/Material.h"
#include "headers/Object.h"
#include "headers/Camera.h"
#include "headers/Skybox.h"
#include "headers/Light.h"
#include "headers/Scene.h"
#include "headers/Renderer.h"

int main() {
    int sampling;
    cout << "Samples: ";
    cin >> sampling;

    Scene scene; // scene
    Renderer renderer(scene, 400, 400, sampling, 1, 8, 0);

    Camera camera(glm::vec3(0, 1.5, 0)); // camera
    scene.SetCamera(camera);
    Skybox skybox(Color(63, 178, 232), Color(225, 244, 252), Color(225, 244, 252), true, Color(0, 0, 0)); // skybox
    scene.SetSkybox(skybox);
    
    Sphere sphere = Sphere(glm::vec3(0, 1, 5), 1, Color(255, 255, 255), Material(0, 1, 0, 0));
    scene.AddObject(&sphere);
    Sphere floor = Sphere(glm::vec3(0, -1000, 5), 1000, Color(255, 255, 255), Material(0, 1, 0, 0));
    scene.AddObject(&floor);
    Sphere light = Sphere(glm::vec3(2, 6, 5), 1, Color(255, 255, 255), Material(0, 0, 0, 20));
    scene.AddObject(&light);

    FILE *fp;
    string file_loc = "../output/test"+to_string(std::time(nullptr))+".ppm";
    fp=fopen(file_loc.c_str(), "w");
    fprintf(fp, "P3\n%d %d\n255\n", renderer.width, renderer.height);

    cout << "dimensions: " << renderer.width<<"x"<<renderer.height<<"\n";
    
    for (int y = renderer.height; y > 0; y--) {
        if(y % (renderer.height/4)==0)cout << (renderer.height-(float) y)/renderer.height*100<<"% complete\n";
        for (int x = 0; x < renderer.width; x++) {
            Color col;
            for(int s = 0; s < renderer.samples; s++) {
                float u, v;
				if(renderer.samples > 1.0f) {
					u = x + rand_float(0.0f, 1.0f);
					v = y + rand_float(0.0f, 1.0f);
				} else {
					u = x;
					v = y;
				}
                glm::vec3 direction = renderer.CanvasToViewport(glm::vec2(u, v));
                /*direction = scene.camera.rotation.roll * direction;
                direction = scene.camera.rotation.pitch * direction;
                direction = scene.camera.rotation.yaw * direction;*/
                Color traced_color = renderer.renderPixel(Ray(scene.camera.position, direction));
                col = col.add(traced_color);
            }
            col = col.divide(renderer.samples);
            fprintf(fp, "%d %d %d\n", (int)col.r, (int)col.g, (int)col.b);
        }
    }
    fclose(fp);
    cout << "100% complete";
    return 0;
}