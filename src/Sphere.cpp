using namespace std;

#include "headers/Sphere.h"
#include <optional>

Sphere::Sphere(glm::vec3 position, float radius, Color color, Material material): Object(position) {
    this->radius = radius;
    this->material = material;
    this->color = color;
    //this->texture = texture;
}

float Sphere::RayIntersects(Ray ray) {
    glm::vec3 oc = ray.position - this->position;
    float k1 = glm::dot(ray.direction, ray.direction);
    float k2 = 2*glm::dot(oc, ray.direction);
    float k3 = glm::dot(oc, oc) - this->radius*this->radius;
    float discriminant = k2*k2 - 4*k1*k3;
    if (discriminant < 0) {
        return -1;
    }
    float t1 = (-k2 + sqrt(discriminant)) / (2*k1);
    float t2 = (-k2 - sqrt(discriminant)) / (2*k1);
    float t = -1;
    /*if (min_dist < t1 && t1 < max_dist) {
        t = t1;
    }
    if (min_dist < t2 && t2 < max_dist) {
        t = t2;
    }*/
    t=t1;
    // return distance
    return t;
}

// CalculateNormal Calculates the normal of the collision point
glm::vec3 Sphere::CalculateNormal(glm::vec3 point) {
    glm::vec3 v = point - this->position;
    return glm::normalize(v);
}

/*// GetColor Gets the color of the sphere
Color Sphere::GetColor(glm::vec3 intersect) {
    if (this->texture != null) {
        return this.texture.GetColor(intersect)
    }
    return this.color;
}*/