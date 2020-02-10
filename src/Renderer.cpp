using namespace std;

#include <iostream>
#include <random>
#include "inc/Renderer.h"
#include "inc/Util.h"

Renderer::Renderer(Scene *scene, int width, int height, int samples, int thread_count, int recursion_depth,
                   float light_loss, float viewport_size, float projection_plane_z) {
    this->scene = scene;
    this->width = width;
    this->height = height;
    this->samples = samples;
    this->thread_count = thread_count;
    this->recursion_depth = recursion_depth;
    this->light_loss = light_loss;
    this->projection_plane_z = projection_plane_z;
    this->viewport_size = viewport_size;
}

Color Renderer::renderPixel(Ray ray) {
    vector<Color> local_colors;

    for (int b = 0; b < this->recursion_depth; b++) {
        //rays_shot++;
        Intersection intersect = this->scene->castRay(ray);
        if (!intersect.hit) {
            if (scene->skybox) {
                local_colors.push_back(scene->skybox->getColorAt(ray.direction));
                break;
            }
            local_colors.push_back(Color(0.0, 0.0, 0.0));
            break;
        }
        glm::vec3 normal = intersect.object->calculateNormal(intersect.collisionPoint);
        Material material = intersect.object->getMaterial();

        Color object_color;
        if (material.emissive > 0.0f) {
            object_color = material.color.multiply(material.emissive);
        } else {
            object_color = material.color;
        }

        glm::vec3 reflectionDirection = glm::normalize(
                ray.direction - (normal * (glm::dot(normal, ray.direction) * 2)));
        if (material.diffuse > 0 || material.reflectivity > 0 || material.emissive > 0) {
            float diffuse_amount; // 0 = mirror reflection | 1 = full diffusion
            if (material.diffuse > 0)
                diffuse_amount = material.diffuse;
            if (material.reflectivity > 0)
                diffuse_amount = 1 - material.reflectivity;

            if (material.reflectivity > 0 && material.diffuse > 0 && material.reflectivity != material.diffuse) {
                if (randomDouble() < 0.5)
                    diffuse_amount = material.diffuse; // 50% chance of diffusing if there's reflection
            }
            if (material.reflectivity < 1 || material.diffuse > 0)
                local_colors.push_back(this->bounceToColor(b, object_color));

            if (material.reflectivity <= 0 && material.diffuse <= 0)
                break;
            else
                ray = Ray::GenerateRandomRay(intersect.collisionPoint, normal, reflectionDirection, diffuse_amount);
        }
	}
	return Color::average(local_colors);
}

Color Renderer::bounceToColor(int b, Color color) {
    float c = (float) b * 255.0f * this->light_loss;
    return color.subVal(c);
}

glm::vec3 Renderer::CanvasToViewport(glm::vec2 p2d) {
	return glm::vec3(
		p2d.x * this->viewport_size / (this->width) - 0.5,
		(p2d.y * this->viewport_size / (this->height) - 0.5) * (this->height / this->width),
		this->projection_plane_z
	);
}

void Renderer::SetScene(Scene& scene) {
	this->scene = &scene;
}