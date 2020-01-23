using namespace std;

class Material {
    public:
        float reflectivity;
        float diffuse;
        float specular;
        float emissive;

        Material(float reflectivity, float diffuse, float specular, float emissive);
};