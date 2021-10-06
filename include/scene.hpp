#ifndef SCENE_H
#define SCENE_H

#include "geometry.hpp"
#include <list>

class LightSource
{
public:
    Vector3D position;
    unsigned char color[3];
    LightSource()= default;
    LightSource(Vector3D pos, unsigned char r, unsigned char g, unsigned char b);
};

class Scene
{
public:
    list<Triangle> triangles;
    list<LightSource> lights;
    void addTriangle(Triangle tri);
    void addLight(LightSource light);
};

#endif