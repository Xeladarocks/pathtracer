#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

using namespace std;

#include <glm/glm.hpp>
#include "Object.h"
#include "Color.h"
#include "Material.h"
#include "Ray.h"

class Triangle : public Object {
public:
	// glm::vec3 position; // from Object
	glm::vec3 v1, v2, v3;
	Material material;
	Color color;
	//Texture texture;

	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Color color, Material material);
	float RayIntersects(Ray ray);
	glm::vec3 CalculateNormal(glm::vec3 point);
	Color GetColor(glm::vec3 intersect);
	Material GetMaterial();
	string GetName() { return typeid(this).name(); };
};

#endif