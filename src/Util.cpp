using namespace std;

#include <glm/glm.hpp>
#include <map> 
#include <string>

#include "headers/Util.h"

Light::Light(glm::vec3 nposition, float nintensity, int ntype) {
    this->position = nposition;
    this->intensity = nintensity;
    this->type = ntype;
}
const map<string, int> Light::types = {
    pair<string, int>("AMBIENT", 0),
    pair<string, int>("POINT", 1), 
    pair<string, int>("DIRECTIONAL", 2),
    pair<string, int>("DIFFUSE", 3)
};