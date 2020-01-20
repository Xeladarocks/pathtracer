#include <iostream>
using namespace std;

#include "headers/Vec3.h"

int main() {
    Vec3 v(5, 3, 2);
    cout << v.scale(5).toString();
    return 0;
}