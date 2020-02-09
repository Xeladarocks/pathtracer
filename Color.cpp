#include "Color.h"
#include <string>
#include <algorithm> // min/max
using namespace std;

Color::Color(float nr, float ng, float nb) {
	this->r = nr;
	this->g = ng;
	this->b = nb;
}
void Color::set(float nr, float ng, float nb) {
	this->r = nr;
	this->g = ng;
	this->b = nb;
}
Color Color::add(Color c) {
	return Color(this->r + c.r, this->g + c.g, this->b + c.b);
}
Color Color::sub(Color c) {
	return Color(this->r - c.r, this->g - c.g, this->b - c.b);
}
Color Color::addVal(float f) {
	return Color(this->r + f, this->g + f, this->b + f);
}
Color Color::subVal(float f) {
	return Color(this->r - f, this->g - f, this->b - f);
}
Color Color::multiply(float f) {
	return Color(this->r*f, this->g*f, this->b*f);
}
Color Color::divide(float f) {
	return Color(this->r / f, this->g / f, this->b / f);
}
Color Color::interpolate(Color c, float f) {
	return Color(
		this->r + (c.r - this->r)*f,
		this->g + (c.g - this->g)*f,
		this->b + (c.b - this->b)*f
	);
}
Color Color::average(vector<Color> colors) {
	float r = 0; float g = 0; float b = 0;
	int length = colors.size();
	for (int i = 0; i < length; i++) {
		r += colors[i].r;
		g += colors[i].g;
		b += colors[i].b;
	}
	int lengthFixed = max(length, 1);
	return Color(r / lengthFixed, g / lengthFixed, b / lengthFixed);
}
Color Color::clamp() {
	return Color(
		max(min(this->r, 255.0f), 0.0f),
		max(min(this->g, 255.0f), 0.0f),
		max(min(this->b, 255.0f), 0.0f)
	);
}
string Color::toString() {
	return "Color(" + to_string(this->r) + ", " + to_string(this->g) + ", " + to_string(this->b) + ")";
}