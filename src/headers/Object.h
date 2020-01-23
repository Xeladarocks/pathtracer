#ifndef OBJECT_H
#define OBJECT_H

using namespace std;

#include "../glm/glm.hpp"
#include "Ray.h"
#include "Material.h"
#include "Color.h"

// Object interface
class Object {
    public:
        glm::vec3 position;

        float RayIntersects(Ray Ray);
        virtual glm::vec3 getPos()=0;
        glm::vec3 CalculateNormal(glm::vec3 point);
        Material GetMaterial();
        Color GetColor(glm::vec3 point);
        //Texture GetTexture()
};

#endif