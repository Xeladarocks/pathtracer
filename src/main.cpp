// g++ -o bin/main src/*.cpp -lpng -lpthread -O3 -g -std=c++17

using namespace std;

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <future>

// broad purpose
#include "inc/Color.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <png++/png.hpp>

// project specific
#include "inc/Sphere.h"
#include "inc/Triangle.h"
#include "inc/Plane.h"
#include "inc/Ray.h"
#include "inc/Util.h"
#include "inc/Material.h"
#include "inc/Camera.h"
#include "inc/Skybox.h"
#include "inc/Scene.h"
#include "inc/Renderer.h"
#include "inc/Rotation.h"

void renderChunk(int x0, int y0, int x1, int y1, Scene *scene, Renderer *renderer, png::image<png::rgba_pixel> *image);

void setupScene(Scene *scene);

int main() {
    int sampling;
    cout << "Samples: ";
    cin >> sampling;

    Scene scene; // scene
    Renderer renderer(&scene, 1920, 1080, sampling, 64, 16, 0.15);

    Camera camera(glm::vec3(0, 1.5, 10.5), (float) renderer.height / (float) renderer.width, 180,
                  Rotation((180 - 0) * M_PI / 180, 0, 0)); // camera
    scene.setCamera(&camera);
    Skybox skybox(Color(63, 178, 232), Color(225, 244, 252), Color(225, 244, 252), true, Color(0, 0, 0)); // skybox
    scene.setSkybox(&skybox);

    setupScene(&scene);

    png::image<png::rgba_pixel> image(renderer.width, renderer.height);

    cout << "dimensions: " << to_string(renderer.width) << "x" << to_string(renderer.height) << "\n";

    /*try { // Debugging purposes
        renderChunk(0, 0, (int) renderer.width, (int) renderer.height, &scene, &renderer, &image);
    } catch(const char* err) {
        cout << string(err);
    }*/

    vector<thread> threads;
    int threadCount = renderer.thread_count;
    for (int i = 0; i < threadCount; i++) {
        int width = renderer.width / threadCount;

        threads.emplace_back(renderChunk, i * width, 0, i * width + width, renderer.height, &scene, &renderer, &image);
    }
    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
    }

    image.write("output.png");
}

void renderChunk(int x0, int y0, int x1, int y1, Scene *scene, Renderer *renderer, png::image<png::rgba_pixel> *image) {
    for (int x = x0; x < x1; x++) {
        for (int y = y0; y < y1; y++) {
            Color col;
            for (int s = 0; s < renderer->samples; s++) {
                float u, v;
                u = (x + randomDouble()) / renderer->width;
                v = (y + randomDouble()) / renderer->height;
                Ray ray = scene->camera->getRay(u, v);

                Color traced_color = renderer->renderPixel(ray);
                col = col.add(traced_color);
            }
            col = col.divide((float) renderer->samples).clamp();
            col.r = 255 * pow(col.r / 255, 1 / 2.2);
            col.g = 255 * pow(col.g / 255, 1 / 2.2);
            col.b = 255 * pow(col.b / 255, 1 / 2.2); // gamma correction
            image->set_pixel(x, y, png::rgba_pixel(col.r, col.g, col.b, 255));
        }
    }
}

void setupScene(Scene *scene) {
    Sphere sphere1 = Sphere(glm::vec3(-2.5, 1.25, 0.0), 1.25, Material(1.0, 0.0, 0.0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(sphere1));

    Sphere sphere2 = Sphere(glm::vec3(0.0, 1.25, 0.0), 1.25, Material(0.0, 1.0, 0.0, Color(255.0, 50.0, 50.0)));
    scene->addObject(std::make_unique<Sphere>(sphere2));

    Sphere sphere3 = Sphere(glm::vec3(2.5, 1.25, 0.0), 1.25, Material(1, 0.5, 0.0, Color(50.0, 255.0, 50.0)));
    scene->addObject(std::make_unique<Sphere>(sphere3));

    Sphere light = Sphere(glm::vec3(-35.0, 35.0, 0.0), 30, Material(0.0, 0.0, 1.0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(light));

    Plane floor = Plane(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0),
                        Material(0.0, 1.0, 0.0, Color(0.0, 0.0, 0.0)));
    scene->addObject(std::make_unique<Plane>(floor));
}