#include <iostream>
using namespace std;

#include "headers/Color.h"
#include "headers/Vec3.h"

int main() {
    Vec3 v;
    cout << v.add(Vec3(2, 3, 5)).scale(5).toString() << "\n";

    Color c(0.0f, 0.0f, 0.0f);
    cout << c.addVal(125.0f).multiply(1.5f).toString() << "\n";
    return 0;
}