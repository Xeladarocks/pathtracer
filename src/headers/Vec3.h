#include <string>
using namespace std;

class Vec3 {
    public:
        float x, y, z;

        Vec3(float nx=0.0f,float ny=0.0f,float nz=0.0f); // constructor
        void set(float nx, float ny, float nz);
        Vec3 copy(Vec3 v);
        Vec3 clone();

        Vec3 add(Vec3 v);
        Vec3 sub(Vec3 v);
        Vec3 scale(float f);
        float distance(Vec3 v);
        float distanceSquared(Vec3 v);
        float dot(Vec3 v);
        Vec3 cross(Vec3 v);
        float length();
        float lengthSquared();
        Vec3 normalize();
        Vec3 interpolate(Vec3 v, float f);
        Vec3 multiplyMat3(float mat[3][3]);

        string toString();
};