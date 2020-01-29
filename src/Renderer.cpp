using namespace std;

#include <iostream>
#include <random>
#include "headers/Renderer.h"
#include "headers/Util.h"

Renderer::Renderer(Scene& scene, int width, int height, int samples, int thread_count, int recursion_depth, float light_loss, float viewport_size, float projection_plane_z) {
    this->scene = &scene;
    this->width = width;
    this->height = height;
    this->samples = samples;
    this->thread_count = thread_count;
    this->recursion_depth = recursion_depth;
    this->light_loss = light_loss;
    this->projection_plane_z = projection_plane_z;
    this->viewport_size = viewport_size;
}

std::uniform_real_distribution<float> flipcoin(0.0f, 1.0f);
Color Renderer::renderPixel(Ray oray) {
    vector<Color> local_colors;
    Ray ray = oray;

    for (int b = 0; b < this->recursion_depth; b++) {
        //rays_shot++;
        optional<IntersectionData> result = this->ClosestIntersection(ray);
        if (!result.has_value()) { // hit nothings
            local_colors.push_back(this->scene->skybox.getColorAt(ray.direction));
            break;
        }
        Object* object = result.value().object;
        glm::vec3 point = result.value().point;
        glm::vec3 normal = object->CalculateNormal(point);
        Color object_color = object->GetColor(point);
        Material object_mat = object->GetMaterial();

        if(object_mat.emissive > 0.0f) {
            object_color = object_color.add(object_color.multiply(object_mat.emissive));
        } else {
            object_color = Color(0, 0, 0);
        }

        glm::vec3 reflectionDirection = glm::normalize( ray.direction - (normal*(glm::dot(normal, ray.direction)*2) ) );
        if(object_mat.diffuse > 0 || object_mat.reflectivity > 0 || object_mat.emissive > 0) {
            float diffuse_amount; // 0 = mirror reflection | 1 = full diffusion
            if(object_mat.diffuse > 0)
                diffuse_amount = object_mat.diffuse;
            else if(object_mat.reflectivity > 0)
                diffuse_amount = 1-object_mat.reflectivity;
                
            if(object_mat.reflectivity > 0 && object_mat.diffuse > 0) {
                if(rand_float(0.0f, 1.0f) < 0.5)diffuse_amount = 1-object_mat.reflectivity; // 50% chance of reflecting if there's diffuse
            }
            if(object_mat.reflectivity < 1 || object_mat.diffuse > 0)
                local_colors.push_back(this->bounceToColor(b, object_color));

            if(object_mat.reflectivity <= 0 && object_mat.diffuse <= 0) {
                break;
            } else {
                ray = Ray::GenerateRandomRay(point, normal, reflectionDirection, diffuse_amount);
            }
        }
    }
    return Color::average(local_colors);
}

// Find the closest intersection between a ray and the objects in the scene.
optional<IntersectionData> Renderer::ClosestIntersection(Ray ray) {
    float closest_t = INFINITY;
    optional<Object*> closest_obj;
    
    for (int i = 0; i < this->scene->objects.size(); i++) {
        float ts = this->scene->objects[i]->RayIntersects(ray);
        if(ts >= 0) {
            if (ts < closest_t) {
                closest_t = ts;
                closest_obj = this->scene->objects[i];
            }
        }
    }
    
    if (closest_obj.has_value()) {
        glm::vec3 closest_point = ray.position+(ray.direction*closest_t);
        return IntersectionData({*closest_obj, closest_point, closest_t});
    }
    return {}; // no intersection
}

Color Renderer::bounceToColor(int b, Color sphere_color) {
	float c = b*255*this->light_loss;
	return sphere_color.subVal(c);
}

glm::vec3 Renderer::CanvasToViewport(glm::vec2 p2d) {
	return glm::vec3(
        p2d.x * this->viewport_size / (this->width * sqrt(this->thread_count)) - 0.5,
		p2d.y * this->viewport_size / (this->height * sqrt(this->thread_count)) - 0.5,
		this->projection_plane_z
    );
}

void Renderer::SetScene(Scene& scene) {
    this->scene = &scene;
}