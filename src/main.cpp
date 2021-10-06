#include <iostream>
#include "camera.hpp"

using namespace std;

int main() {
    Camera cam = Camera(600, 840);
    Scene scene = Scene();
    Vector3D v1(-0.2, -0.2, 1.1);
    Vector3D v2(-0.2, 0.2, 0.95);
    Vector3D v3(0.1, 0, 1);
    Triangle tr1(v1, v2, v3, 120, 0, 230);
    scene.addTriangle(tr1);
    v1 = Vector3D(0.2, 0.2, 1.1);
    v2 = Vector3D(0.2, -0.2, 0.9);
    v3 = Vector3D(-0.1, 0, 1);
    Triangle tr2(v1, v2, v3, 10, 120, 100);
    scene.addTriangle(tr2);
    cam.renderScene(scene);
    cam.writeToFile("rasterize1.png");
}