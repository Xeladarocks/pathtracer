#ifndef SKYBOX_H
#define SKYBOX_H

using namespace std;

#include "../glm/glm.hpp"
#include "Color.h"

class Skybox {
    public:
        glm::vec3 up;
        Color topColor;
        Color sideColor;
        Color bottomColor;
        bool override;
        Color overrideColor;
        float intensity;

        Skybox() {
            this->up = glm::vec3(0,1,0);
            this->topColor, this->sideColor, this->bottomColor = Color();
            this->override = true; this->overrideColor = Color(255, 20, 147);
            this->intensity = 1;
        }
        Skybox(Color topColor, Color sideColor, Color bottomColor, glm::vec3 up, bool override=false, Color overrideColor=Color(255, 20, 147), float intensity=1);
        Color getColorAt(glm::vec3 dir);
};

#endif