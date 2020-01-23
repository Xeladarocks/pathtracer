#ifndef UTIL_H
#define UTIL_H

using namespace std;

#include "../glm/glm.hpp"
#include <string>

struct Rotation {
    glm::mat3 yaw;
    glm::mat3 pitch;
    glm::mat3 roll;
};
static Rotation defaultRotation({
    glm::mat3(0, 0, 0,   0, 1, 0,   0, 0, 0),
    glm::mat3(0, 0, 0,   0, 1, 0,   0, 0, 0),
    glm::mat3(0, 0, 0,   0, 1, 0,   0, 0, 0)
});

#endif