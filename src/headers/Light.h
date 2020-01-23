using namespace std;

#include <glm/glm.hpp>

#include <map>

class Light {
    const static map<string, int> types;
    public:
        glm::vec3 position;
        float intensity;
        int type;

        Light(glm::vec3 nposition, float nintensity=1, int ntype=1);
};