#include "headers/Vec3.h"
#include <string>
#include <cmath>
using namespace std;

Vec3::Vec3(float nx, float ny, float nz) {
    this->x = nx;
    this->y = ny;
    this->z = nz;
}
void Vec3::set(float nx, float ny, float nz) {
    this->x = nx;
    this->y = ny;
    this->z = nz;
}
Vec3 Vec3::add(Vec3 v) {
    return Vec3(this->x+v.x, this->y+v.y, this->z+v.z);
}
Vec3 Vec3::sub(Vec3 v) {
    return Vec3(this->x-v.x, this->y-v.y, this->z-v.z);
}
Vec3 Vec3::scale(float f) {
    return Vec3(this->x*f, this->y*f, this->z*f);
}
float Vec3::distance(Vec3 v) {
    float dx = v.x - this->x;
    float dy = v.y - this->y;
    float dz = v.z - this->z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}
float Vec3::distanceSquared(Vec3 v) {
    float dx = v.x - this->x;
    float dy = v.y - this->y;
    float dz = v.z - this->z;
    return dx*dx + dy*dy + dz*dz;
}
Vec3 Vec3::copy(Vec3 v) {
    return Vec3(v.x, v.y, v.z);
}
Vec3 Vec3::clone() {
    return Vec3(this->x, this->y, this->z);
}
float Vec3::dot(Vec3 v) {
    return this->x*v.x + this->y*v.y + this->z*v.z;
}
Vec3 Vec3::cross(Vec3 v) {
    float fx = this->y * v.z - this->z * v.y;
    float fy = this->z * v.x - this->x * v.z;
    float fz = this->x * v.y - this->y * v.x;
    return Vec3(fx, fy, fz);
}
float Vec3::length() {
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}
float Vec3::lengthSquared() {
    return this->x*this->x + this->y*this->y + this->z*this->z;
}
Vec3 Vec3::normalize() {
    float len = this->length();
    if(len > 0) return this->scale(1 / len);
    return this->clone();
}
Vec3 Vec3::interpolate(Vec3 v, float p) {
    return Vec3(
        this->x + (v.x-this->x)*p,
        this->y + (v.y-this->y)*p,
        this->z + (v.z-this->z)*p
    );
}
Vec3 Vec3::multiplyMat3(float mat[3][3]) {
    Vec3 res(0,0,0);
	res.x += this->x * mat[0][0];
	res.x += this->y * mat[0][1];
	res.x += this->z * mat[0][2];

	res.y += this->x * mat[1][0];
	res.y += this->y * mat[1][1];
	res.y += this->z * mat[1][2];

	res.z += this->x * mat[2][0];
	res.z += this->y * mat[2][1];
	res.z += this->z * mat[2][2];
    return res;
}

string Vec3::toString() {
    return "Vec3("+to_string(this->x)+", "+to_string(this->y)+", "+to_string(this->z)+")";
}