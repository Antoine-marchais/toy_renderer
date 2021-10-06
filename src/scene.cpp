#include "scene.hpp"

LightSource::LightSource(Vector3D pos, unsigned char r, unsigned char g, unsigned char b){
    this->position = pos;
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}

void Scene::addTriangle(Triangle tri){
    this->triangles.push_back(tri);
}

void Scene::addLight(LightSource light){
    this->lights.push_back(light);
}
