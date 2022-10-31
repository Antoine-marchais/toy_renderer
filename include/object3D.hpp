#ifndef OBJECT3D_H
#define OBJEC3D_H

#include "geometry.hpp"

class Object3D
{
public:
    int num_faces;
    Vector3D centroid;
    Triangle faces[];
    Object3D(string filename);
    ~Object3D();
    void translate(Vector3D translation);
};

#endif