#include <iostream>
using namespace std;

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

int main() {
    Scene scene;

    Sphere sphere = Sphere(glm::vec3(0, 1, 5), 1, Color(255, 0, 0), Material());

    scene.AddObject(&sphere);

    cout << glm::to_string(scene.objects[0]->CalculateNormal(glm::vec3(0, 1, 5.5))) << endl;
    return 0;
}