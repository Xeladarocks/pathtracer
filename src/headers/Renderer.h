using namespace std;

#include "Color.h"
#include "Scene.h"
#include "Object.h"
#include "Ray.h"
#include <vector>
#include <optional>

struct IntersectionData { // intersection data
    Object* object;
    glm::vec3 point;
    float distance;
};
class Renderer {
    public:
        Scene scene;
        int width;
        int height;
        int samples;
        int recursion_depth = 5;
        float light_loss = 0.2;

        Renderer(Scene scene, int width, int height, int samples, int recursion_depth=2, float light_loss=0.2);

        Color renderPixel(Ray oray);
        optional<IntersectionData> ClosestIntersection(Ray ray);
        Color bounceToColor(int b, Color sphere_color);
};