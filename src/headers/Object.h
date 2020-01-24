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
        Object(glm::vec3 position) {
            this->position = position;
        };
        glm::vec3 getPos() {return this->position;};
        virtual float RayIntersects(Ray Ray)=0;
        virtual glm::vec3 CalculateNormal(glm::vec3 point)=0;
        /*Material GetMaterial();
        Color GetColor(glm::vec3 point);
        //Texture GetTexture()*/
};

#endif