#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.hpp"
#include "scene.hpp"
#include <tuple>

using namespace std;

class RenderedVertex
{
public:
    Vector2D coords;
    double z;
    RenderedVertex()= default;
    RenderedVertex(Vector2D, double);
};

class Camera
{
public:
    Vector3D origin;
    Vector3D direction;
    Vector3D width_dir;
    Vector3D height_dir;
    double focal_length;
    double field_height;
    double field_width;
    double rot;
    int vertical_resolution;
    int horizontal_resolution;
    Camera();
    Camera(Vector3D o, Vector3D d);
    Camera(Vector3D o, Vector3D d, int ny, int nx);
    Camera(int ny, int nx);
    Camera(Vector3D o, Vector3D d, double f, double fh, double fw, int ny, int nx, double rot);
    ~Camera();
    RenderedVertex project(Vector3D vec);
    tuple<RenderedVertex, RenderedVertex, RenderedVertex> projectTriangle(Triangle tri);
    void rasterize(Triangle tri);
    void writeToFile(char *name);
    bool inCameraSpace(RenderedVertex vert);
    void renderScene(Scene scene);
private:
    double *zBuffer;
    unsigned char *imgBuffer;
    void computeDirections();
};

void orderVertices(RenderedVertex *v1, RenderedVertex *v2, RenderedVertex *v3);

#endif