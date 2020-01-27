using namespace std;

#include "headers/Renderer.h"

Renderer::Renderer(Scene scene, int width, int height, int samples, int recursion_depth, float light_loss) {
    this->scene = scene;
    this->width = width;
    this->height = height;
    this->samples = samples;
    this->recursion_depth = recursion_depth;
    this->light_loss = light_loss;
}

Color Renderer::renderPixel(Ray ray) {
    vector<Color> local_colors;

    for (int b = 0; b < this->recursion_depth; b++) {
        //rays_shot++;
        optional<IntersectionData> result = this->ClosestIntersection(ray);
        if (!result.has_value()) { // hit nothings
            //local_colors.push_back(GetSkyAt(ray.direction))
            break;
        }
        Object* object = result.value().object;
        glm::vec3 point = result.value().point;

        glm::vec3 normal = object->CalculateNormal(point);
        Color object_color = object->GetColor(point);
        Material object_mat = object->GetMaterial();

        if(object_mat.emissive > 0)
            object_color = object_color.add(object_color.multiply(object_mat.emissive));

        glm::vec3 reflectionDirection = glm::normalize( ray.direction - (normal*(glm::dot(normal, ray.direction)*2), normal) );
        if(object_mat.diffuse > 0 || object_mat.reflectivity > 0 || object_mat.emissive > 0) {
            // value of 0 = mirror reflection    |    value of 1 = full diffusion
            float diffuse_amount;
            if(object_mat.diffuse > 0)
                diffuse_amount = object_mat.diffuse;
            else if(object_mat.reflectivity > 0)
                diffuse_amount = 1-object_mat.reflectivity;
                
            if(object_mat.reflectivity > 0 && object_mat.diffuse > 0) {
                if((rand()/RAND_MAX) < 0.5)diffuse_amount = 1-object_mat.reflectivity; // 50% chance of reflecting if there's diffuse
            }
            if(object_mat.reflectivity < 1 || object_mat.diffuse > 0)
                local_colors.push_back(bounceToColor(b, object_color));

            if(object_mat.reflectivity <= 0 && object_mat.diffuse <= 0)break;else 
            ray = Ray::GenerateRandomRay(point, normal, reflectionDirection, diffuse_amount);
        }
    }
    return Color::average(local_colors);
}

// Find the closest intersection between a ray and the objects in the scene.
optional<IntersectionData> Renderer::ClosestIntersection(Ray ray) {
    float closest_t = INFINITY;
    Object* closest_obj;
    
    for (int i = 0; i < this->scene.objects.size(); i++) {
        float ts = this->scene.objects[i]->RayIntersects(ray);
        if (ts < closest_t) {
            closest_t = ts;
            closest_obj = scene.objects[i];
        }
    }
    
    if (closest_obj) {
        glm::vec3 closest_point = ray.position+(ray.direction*closest_t);
        return IntersectionData({closest_obj, closest_point, closest_t});
    }
    return {}; // no intersection
}

Color Renderer::bounceToColor(int b, Color sphere_color) {
	float c = b*255*this->light_loss;
	return sphere_color.subVal(c);
}