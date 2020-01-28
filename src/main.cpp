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
    Scene scene; // scene
    Renderer renderer(scene, 400, 400, 1, 1, 5);

    Camera camera(glm::vec3(0, 1.5, -5)); // camera
    scene.SetCamera(camera);
    Skybox skybox(Color(63, 178, 232), Color(225, 244, 252), Color(225, 244, 252), true, Color(0, 0, 0)); // skybox
    scene.SetSkybox(skybox);
    
    Sphere sphere = Sphere(glm::vec3(0, 1, 5), 1, Color(255, 255, 0), Material(0, 1, 0, 0));
    scene.AddObject(&sphere);
    Sphere sphere2 = Sphere(glm::vec3(0, -1000, 5), 1000, Color(255, 255, 255), Material(0, 1, 0, 0));
    scene.AddObject(&sphere2);
    Sphere sphere3 = Sphere(glm::vec3(0, 4, 5), 0.4, Color(255, 255, 255), Material(0, 0, 0, 10));
    scene.AddObject(&sphere3);

    FILE *fp;
    string file_loc = "../output/test"+to_string(std::time(nullptr))+".ppm";
    fp=fopen(file_loc.c_str(), "w");
    fprintf(fp, "P3\n%d %d\n255\n", renderer.width, renderer.height);

    vector<Color> cols;
    for (int j = renderer.height; j > 0; j--) {
        for (int i = 0; i < renderer.width; i++) {
            glm::vec3 direction = renderer.CanvasToViewport(glm::vec2(i, j));
            /*direction = scene.camera.rotation.roll * direction;
            direction = scene.camera.rotation.pitch * direction;
            direction = scene.camera.rotation.yaw * direction;*/
            Color traced_color = renderer.renderPixel(Ray(scene.camera.position, direction));
            /*cols.push_back(traced_color);
            Color col = Color::average(cols);*/
            Color col = traced_color;
            col = col.clamp();
            fprintf(fp, "%d %d %d\n", (int)col.r, (int)col.g, (int)col.b);
        }
    }
    fclose(fp);
    return 0;
}