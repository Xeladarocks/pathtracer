#ifndef UTIL_H
#define UTIL_H

using namespace std;

#include "../glm/glm.hpp"
#include <string>
#include <random>

static float rand_float(float low, float high){
    static std::default_random_engine re {}; //static means that your generator will not be created again and again
    using Dist = std::uniform_real_distribution<float>;
    static Dist uid {};
    return uid(re, Dist::param_type{low, high});
}

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