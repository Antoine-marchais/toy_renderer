#include "face.hpp"
#include <string.h>


/**
 * Copy constuctor for the triangle face
 */
Face::Face(const Face& face): n_vertices(face.n_vertices), vertices(new Vector3D[face.n_vertices]){
    memcpy(color, face.color, 3);
    memcpy(vertices, face.vertices, sizeof(Vector3D) * face.n_vertices);
}

/**
 * Regular constructor for a face using a list of vertices
 * The color will lbe initialized white
 */
Face::Face(Vector3D vertices[], int n_vertices){
    this->n_vertices = n_vertices;
    this->vertices = new Vector3D[n_vertices];
    for (int i=0; i<n_vertices; i++){
        this->vertices[i] = vertices[i];
    }
    this->color[0] = 255;
    this->color[1] = 255;
    this->color[2] = 255;
}

/**
 * Regular constructor for a face using a list of vertices and a color
 */
Face::Face(Vector3D vertices[], int n_vertices, unsigned char r, unsigned char g, unsigned char b): Face(vertices, n_vertices){
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}

/**
 * Destructor of face
 * Dealocate the list of vertices
 */
Face::~Face(){
    delete[] vertices;
}

/**
 * fill a vertices buffer with the vertex from the polygon, given a starting index
 * and a chain length
 */
void Face::getChain(int length, int starting_position, Vector3D vertexBuffer[]){
    for (int i=0; i < length; i++){
        vertexBuffer[i] = vertices[(starting_position + i)%n_vertices];
    }
}