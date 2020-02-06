#include "pch.h"
using namespace std;

#include "Material.h"

Material::Material(float reflectivity, float diffuse, float specular, float emissive) {
	this->reflectivity = reflectivity;
	this->diffuse = diffuse;
	this->specular = specular;
	this->emissive = emissive;
}
