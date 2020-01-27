using namespace std;

#include <iostream>
#include <string>
#include <ctime>

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
    /*Scene scene;

    Sphere sphere = Sphere(glm::vec3(0, 1, 5), 1, Color(255, 0, 0), Material());

    scene.AddObject(&sphere);

    cout << glm::to_string(scene.objects[0]->CalculateNormal(glm::vec3(0, 1, 5.5))) << endl;*/
    int nx = 200;
    int ny = 100;
    FILE *fp;
    string file_loc = "../output/test"+to_string(std::time(nullptr))+".ppm";
    fp=fopen(file_loc.c_str(), "w");
    fprintf(fp, "P3\n%d %d\n255\n", nx, ny);
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(125.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            fprintf(fp, "%d %d %d\n", ir, ig, ib);
        }
    }
    fclose(fp);
    return 0;
}