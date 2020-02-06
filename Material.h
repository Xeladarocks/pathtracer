#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

using namespace std;

class Material {
public:
	float reflectivity;
	float diffuse;
	float specular;
	float emissive;

	Material() {
		this->reflectivity = 0;
		this->diffuse = 1;
		this->specular = 0;
		this->emissive = 0;
	}
	Material(float reflectivity, float diffuse, float specular, float emissive);
};

#endif