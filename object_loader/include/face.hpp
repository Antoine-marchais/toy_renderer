#ifndef FACE_H
#define FACE_H

#include "geometry.hpp"

class Face
{
public:
    int n_vertices;
    unsigned char color[3];
    Vector3D *vertices;
    Face() = default;
    Face(const Face& face);
    Face(Vector3D vertices[], int n_vertices);
    Face(Vector3D vertices[], int n_vertices, unsigned char r, unsigned char g, unsigned char b);
    ~Face();
    void getChain(int chainLength, int startingVertex, Vector3D vertexBuffer[]);
};


#endif