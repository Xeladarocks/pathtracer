using namespace std;

#include <glm/glm.hpp>
#include "headers/Color.h"

const static Skybox defaultSkybox(glm::vec3(0,1,0),Color(),Color(),Color(),true);
class Skybox : public Object {
    public:
        glm::vec3 up;
        Color topColor;
        Color sideColor;
        Color bottomColor;
        bool override;
        Color overrideColor;
        float intensity;

        Skybox(glm::vec3 up=glm::vec3(0,1,0), Color topColor=Color(0,0,0), Color sideColor=Color(), Color bottomColor=Color(), bool override=false, Color overrideColor=Color(255, 20, 147), float intensity=1);
        Color getColorAt(glm::vec3 dir);
};