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
#include <png++/png.hpp>

#define ANIMATE // comment out to output as png

#include <SDL2/SDL.h>
#include <stdio.h>

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

#ifndef ANIMATE
void renderThreads(Renderer *renderer, png::image<png::rgba_pixel> *image);
void renderChunk(int x0, int y0, int x1, int y1, Renderer *renderer, png::image<png::rgba_pixel> *image);
#else

void renderThreads(Renderer *renderer, vector<Uint32> &pixels);

void renderChunk(int x0, int y0, int x1, int y1, Renderer *renderer, vector<Uint32> &pixels);

Uint32 ColorToUInt(Color color) {
    return (Uint32) (((int) color.r << 24) | ((int) color.r << 16) | ((int) color.g << 8) | ((int) color.b << 0));
}

#endif

void setupScene(Scene *scene);

int main() {
    int sampling;
    cout << "Samples: ";
    cin >> sampling;

    Scene scene; // scene
    Renderer renderer(&scene, 600, 600, sampling, 10, 8, 0.5);

    Camera camera(glm::vec3(0, 6, -16), (float) renderer.height / (float) renderer.width, 180,
                  Rotation((180 - 0) * M_PI / 180, (180 - 0) * M_PI / 180, 0)); // camera
    scene.setCamera(&camera);
    Skybox skybox(Color(63, 178, 232), Color(225, 244, 252), Color(225, 244, 252), false, Color(0, 0, 0)); // skybox
    scene.setSkybox(&skybox);

#ifdef ANIMATE
    renderer.samples = 1;
    renderer.recursion_depth = 3;
#endif

    try {
        setupScene(&scene);
    } catch (const char *err) {
        cout << string(err);
    }

#ifndef ANIMATE
    png::image<png::rgba_pixel> image(renderer.width, renderer.height);
    cout << "dimensions: " << to_string(renderer.width) << "x" << to_string(renderer.height) << "\n";
    renderThreads(&renderer, &image);
    image.write("../output.png");
    return 0;
#else
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, renderer.width,
                                  renderer.height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            SDL_Renderer *rd = SDL_CreateRenderer(window, -1, 0);
            SDL_Texture *texture = SDL_CreateTexture(rd, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
                                                     renderer.width, renderer.height);
            vector<Uint32> pixels(renderer.width * renderer.height);

            bool quit = false;
            SDL_Event event;
            const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&event) != 0) {
                    //User requests quit
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                    if (event.type == SDL_KEYDOWN) {
                        switch (event.key.keysym.scancode) {
                            case 26:
                                renderer.scene->camera->controls.w = true;
                                break;
                            case 4:
                                renderer.scene->camera->controls.a = true;
                                break;
                            case 22:
                                renderer.scene->camera->controls.s = true;
                                break;
                            case 7:
                                renderer.scene->camera->controls.d = true;
                                break;
                            case 0x02C:
                                renderer.scene->camera->controls.e = true;
                                break;
                            case 0x0E1:
                                renderer.scene->camera->controls.q = true;
                                break;
                            case 0x04F:
                                renderer.scene->camera->controls.left = true;
                                break;
                            case 0x050:
                                renderer.scene->camera->controls.right = true;
                                break;
                            case 0x051:
                                renderer.scene->camera->controls.down = true;
                                break;
                            case 0x052:
                                renderer.scene->camera->controls.up = true;
                                break;
                        }
                    }
                    if (event.type == SDL_KEYUP) {
                        switch (event.key.keysym.scancode) {
                            case 26:
                                renderer.scene->camera->controls.w = false;
                                break;
                            case 4:
                                renderer.scene->camera->controls.a = false;
                                break;
                            case 22:
                                renderer.scene->camera->controls.s = false;
                                break;
                            case 7:
                                renderer.scene->camera->controls.d = false;
                                break;
                            case 0x02C:
                                renderer.scene->camera->controls.e = false;
                                break;
                            case 0x0E1:
                                renderer.scene->camera->controls.q = false;
                                break;
                            case 0x04F:
                                renderer.scene->camera->controls.left = false;
                                break;
                            case 0x050:
                                renderer.scene->camera->controls.right = false;
                                break;
                            case 0x051:
                                renderer.scene->camera->controls.down = false;
                                break;
                            case 0x052:
                                renderer.scene->camera->controls.up = false;
                                break;
                        }
                    }
                }

                renderer.scene->camera->update();

                SDL_UpdateTexture(texture, NULL, pixels.data(), renderer.width * sizeof(Uint32));
                renderThreads(&renderer, pixels);

                SDL_RenderClear(rd);
                SDL_RenderCopy(rd, texture, NULL, NULL);
                SDL_RenderPresent(rd);
            }
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(rd);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
#endif
}

#ifndef ANIMATE
void renderThreads(Renderer *renderer, png::image<png::rgba_pixel> *image) {
#else

void renderThreads(Renderer *renderer, vector<Uint32> &pixels) {
#endif
    vector<thread> threads;
    int threadCount = renderer->thread_count;
    //renderChunk(0, 0, renderer->width, renderer->height, renderer, pixels);
    for (int i = 0; i < threadCount; i++) {
        int width = renderer->width / threadCount;
        try {
#ifndef ANIMATE
            threads.emplace_back(renderChunk, i * width, 0, i * width + width, renderer.height, &renderer->scene, &renderer, &image);
#else
            threads.emplace_back(renderChunk, i * width, 0, i * width + width, renderer->height, renderer, ref(pixels));
#endif
        } catch (const char *err) {
            cout << string(err);
        }
    }
    for (int i = 0; i < threadCount; i++) {
        try {
            threads[i].join();
        } catch (const char *err) {
            cout << string(err);
        }
    }
}

#ifndef ANIMATE
void renderChunk(int x0, int y0, int x1, int y1, Renderer *renderer, png::image<png::rgba_pixel> *image) {
#else

void renderChunk(int x0, int y0, int x1, int y1, Renderer *renderer, vector<Uint32> &pixels) {
#endif

    for (int x = x0; x < x1; x++) {
        for (int y = y0; y < y1; y++) {
            Color cols;
            for (int s = 0; s < renderer->samples; s++) {
                float u, v;
                u = (x + randomDouble()) / renderer->width;
                v = (y + randomDouble()) / renderer->height;
                Ray ray = renderer->scene->camera->getRay(u, v);

                Color traced_color = renderer->renderPixel(ray);
                cols = cols.add(traced_color);
            }
            Color col = cols.divide((float) renderer->samples).clamp();
            col.r = 255 * pow(col.r / 255, 1 / 2.2);
            col.g = 255 * pow(col.g / 255, 1 / 2.2);
            col.b = 255 * pow(col.b / 255, 1 / 2.2); // gamma correction
#ifndef ANIMATE
            image->set_pixel(x, y, png::rgba_pixel(col.r, col.g, col.b, 255));
#else
            pixels[y * renderer->width + x] = ColorToUInt(col);
#endif
        }
    }
}

void setupScene(Scene *scene) {
/** Main Objects **/
    Sphere sphere1 = Sphere(glm::vec3(-2, 3, -2.0), 3, Material(0.0, 1.0, 0.0, Color(204.0, 204.0, 204.0)));
    scene->addObject(std::make_unique<Sphere>(sphere1));

    Sphere sphere2 = Sphere(glm::vec3(0.0, 1.25, 3.0), 1.25, Material(1.0, 0.0, 0.0, Color(204.0, 204.0, 204.0)));
    scene->addObject(std::make_unique<Sphere>(sphere2));

    Sphere sphere3 = Sphere(glm::vec3(3.5, 1.75, 0.0), 1.75, Material(0.5, 0.5, 0.0, Color(204.0, 204.0, 204.0)));
    scene->addObject(std::make_unique<Sphere>(sphere3));


    /** Lights **/
    vector<unique_ptr<Object>> light = Rect(glm::vec3(-2, 11.99, -2), glm::vec3(-2, 11.99, 2), glm::vec3(2, 11.99, 2),
                                            glm::vec3(2, 11.99, -2), Material(0.0, 0.0, 25.0, Color(255, 255, 255)));
    scene->addObjects(light);


    /** Walls **/
    Plane floor = Plane(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0),
                        Material(0.0, 1.0, 0.0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Plane>(floor)); // floor

    //vector<unique_ptr<Object>> floor = Rect(glm::vec3(6, 0, -6), glm::vec3(-6, 0, -6), glm::vec3(-6, 0, 6), glm::vec3(6, 0, 6), Material(0.0, 1.0, 0.0, Color(255, 255, 255)));
    //scene->addObjects(floor);

    /*vector<unique_ptr<Object>> wall1 = Rect(glm::vec3(-6, 0, 6), glm::vec3(-6, 0, -6), glm::vec3(-6, 12, -6),
                                            glm::vec3(-6, 12, 6), Material(0.0, 1.0, 0.0, Color(255, 50, 50)));
    scene->addObjects(wall1); // left
    vector<unique_ptr<Object>> wall2 = Rect(glm::vec3(6, 0, -6), glm::vec3(6, 0, 6), glm::vec3(6, 12, 6),
                                            glm::vec3(6, 12, -6), Material(0.0, 1.0, 0.0, Color(50, 255, 50)));
    scene->addObjects(wall2); // right
    vector<unique_ptr<Object>> wall3 = Rect(glm::vec3(-6, 0, -6), glm::vec3(6, 0, -6), glm::vec3(6, 12, -6),
                                            glm::vec3(-6, 12, -6), Material(0.0, 1.0, 0.0, Color(255, 255, 255)));
    scene->addObjects(wall3); // straight

    vector<unique_ptr<Object>> ceiling = Rect(glm::vec3(-6, 12, -6), glm::vec3(6, 12, -6), glm::vec3(6, 12, 6),
                                              glm::vec3(-6, 12, 6), Material(0.0, 1.0, 0.0, Color(255, 255, 255)));
    scene->addObjects(ceiling);*/
}