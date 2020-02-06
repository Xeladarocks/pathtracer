#include "pch.h"
using namespace std;

#include "Triangle.h"

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Color color, Material material) : Object(v1) {
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->material = material;
	this->color = color;
	//this->texture = texture;
}

float Triangle::RayIntersects(Ray ray) {
	glm::vec3 edge1 = this->v2 - this->v1;
	glm::vec3 edge2 = this->v3 - this->v1;

	glm::vec3 h = glm::cross(ray.direction, edge2);
	float a = glm::dot(edge1, h);

	if (a > -0.0001 && a < 0.0001) {
		return -1;
	}

	float f = 1.0 / a;
	glm::vec3 s = ray.position - this->v1;
	float u = f * glm::dot(s, h);

	if (u < 0 || u > 1) {
		return -1;
	}

	glm::vec3 q = glm::cross(s, edge1);
	float v = f * glm::dot(ray.direction, q);

	if (v < 0 || u + v > 1) {
		return -1;
	}

	float t0 = f * glm::dot(edge2, q);

	if (t0 > 0.0001 && t0 < 1 / 0.0001) {
		return t0;
	}

	return -1;
}

glm::vec3 Triangle::CalculateNormal(glm::vec3 point) {
	glm::vec3 edge1 = this->v2 - this->v1;
	glm::vec3 edge2 = this->v3 - this->v1;

	glm::vec3 cross = glm::cross(edge1, edge2);

	return glm::normalize(cross);
}

Material Triangle::GetMaterial() {
	return this->material;
}

Color Triangle::GetColor(glm::vec3 intersect) {
	/*if (this->texture != NULL) {
		return this->texture.GetColor(intersect);
	}*/
	return this->color;
}