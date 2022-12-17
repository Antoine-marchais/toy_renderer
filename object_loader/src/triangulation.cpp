#include "triangulation.hpp"

/**
 * Split polygon into monotone chains, and returns the number of chains.
 * The starting index of the chains and their lengths are stored in the given
 * buffers.
 * the length of a chain is the number of vertices in the chain (ie: a chain with
 * 2 segments has length 3)
 */
int getPolygonChains(Face face, int chain_lengths[], int starting_vertices[]){
    int num_chains = 0;
    int len_chain = 1;
    Vector2D current_point = projectToPlane(face.vertices[0], face.vertices[1], face.vertices[2], face.vertices[0]);
    Vector2D new_point = projectToPlane(face.vertices[0], face.vertices[1], face.vertices[2], face.vertices[1]);
    bool going_up = new_point.y > current_point.y || ((new_point.y == current_point.y) && (new_point.x > current_point.x));
    bool new_going_up;
    for (int i=2; i <= face.n_vertices+1; i++){
        len_chain++;
        current_point = new_point;
        new_point = projectToPlane(face.vertices[0], face.vertices[1], face.vertices[2], face.vertices[i%face.n_vertices]);
        new_going_up = new_point.y > current_point.y || ((new_point.y == current_point.y) && (new_point.x > current_point.x));
        if (new_going_up != going_up){
            chain_lengths[num_chains] = len_chain;
            starting_vertices[num_chains] = (i-len_chain)%face.n_vertices;
            len_chain = 1;
            num_chains++;
        }
        going_up = new_going_up;
    }
    return num_chains;
}