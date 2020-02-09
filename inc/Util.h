#pragma once
#ifndef UTIL_H
#define UTIL_H

using namespace std;

#include <glm/glm.hpp>
#include <string>
#include <random>
#include <memory>
#include "Triangle.h"

static float rand_float(float low, float high) {
	static std::default_random_engine re{}; //static means that your generator will not be created again and again
	using Dist = std::uniform_real_distribution<float>;
	static Dist uid{};
	return uid(re, Dist::param_type{ low, high });
}

const static vector<Triangle> newQuad(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, Material material, Color color) {
	vector<Triangle> tris;
	tris.push_back(Triangle(v1, v2, v3, color, material));
	tris.push_back(Triangle(v3, v4, v1, color, material));
	return tris;
}

struct Rotation {
	glm::mat3 yaw;
	glm::mat3 pitch;
	glm::mat3 roll;
};

static Rotation defaultRotation = {
	glm::mat3(0, 0, 0,   0, 1, 0,   0, 0, 0),
	glm::mat3(0, 0, 0,   0, 1, 0,   0, 0, 0),
	glm::mat3(0, 0, 0,   0, 1, 0,   0, 0, 0),
};

#endif