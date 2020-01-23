using namespace std;

#include <glm/glm.hpp>

#include "headers/Ray.h"
#include "headers/Material.h"
#include "headers/Color.h"

// Object interface
class Object {
    public:
        virtual pair<bool, glm::vec3> RayIntersects(Ray Ray);
        virtual glm::vec3 CalculateNormal(glm::vec3 point);
        virtual Material GetMaterial();
        virtual Color GetColor(glm::vec3 point);
        //Texture GetTexture()
};