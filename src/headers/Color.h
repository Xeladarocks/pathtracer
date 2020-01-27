#ifndef COLOR_H
#define COLOR_H

using namespace std;

#include <string>
#include <vector>

class Color {
    public:
        float r, g, b;

        Color(float nr=0.0f,float ng=0.0f,float nb=0.0f); // constructor
        void set(float nr, float ng, float nb);
        Color add(Color c);
        Color sub(Color c);
        Color addVal(float f);
        Color subVal(float f);
        Color multiply(float f);
        Color divide(float f);
        Color interpolate(Color c, float f);
        static Color average(vector<Color> colors);
        Color clamp();
        string toString();
};

#endif