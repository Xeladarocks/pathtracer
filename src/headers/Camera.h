using namespace std;

#include <glm/glm.hpp>

#include "headers/Util.h"

class Camera {
    public:
        glm::vec3 position;
        Rotation rotation;

        Camera(glm::vec3 nposition=glm::vec3(0, 1, 0), Rotation nrotation=defaultRotation);
};