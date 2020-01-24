using namespace std;

#include "../glm/glm.hpp"
#include "Object.h"
#include "Color.h"
#include "Material.h"
#include "Ray.h"

class Sphere: public Object {
    public:
        // glm::vec3 position; // from Object
        float radius;
        Material material;
        Color color;
        //Texture texture;

        Sphere(glm::vec3 position, float radius, Color color, Material material);
        float RayIntersects(Ray ray);
        glm::vec3 CalculateNormal(glm::vec3 point);
};