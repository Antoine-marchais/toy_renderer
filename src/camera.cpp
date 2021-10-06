#include "camera.hpp"
#include <png++/png.hpp>

using namespace png;

RenderedVertex::RenderedVertex(Vector2D coords, double z_distance){
    this->coords = coords;
    this->z = z_distance;
}

Camera::Camera(){
    origin = Vector3D(0, 0, 0);
    direction = Vector3D(0, 0, 1);
    focal_length = 0.1;
    field_height = 0.1;
    field_width = 0.14;
    vertical_resolution = 100;
    horizontal_resolution = 140;
    rot = 0;
    width_dir = Vector3D(1, 0, 0);
    height_dir = Vector3D(0, 1, 0);
    this->zBuffer = new double[vertical_resolution * horizontal_resolution];
    this->imgBuffer = new unsigned char[vertical_resolution * horizontal_resolution * 3];
}

Camera::Camera(Vector3D o, Vector3D d): Camera() {
    this->origin = o;
    this->direction = d;
    this->computeDirections();
}

Camera::Camera(Vector3D o, Vector3D d, int ny, int nx): Camera(o, d) {
    this->vertical_resolution = ny;
    this->horizontal_resolution = nx;
    delete this->imgBuffer;
    delete this->zBuffer;
    this->imgBuffer = new unsigned char[nx * ny * 3];
    this->zBuffer = new double[nx * ny];
}

Camera::Camera(int ny, int nx): Camera() {
    this->vertical_resolution = ny;
    this->horizontal_resolution = nx;
    delete this->imgBuffer;
    delete this->zBuffer;
    this->imgBuffer = new unsigned char[nx * ny * 3];
    this->zBuffer = new double[nx * ny];
}

Camera::Camera(Vector3D o, Vector3D d, double f, double fh, double fw, int ny, int nx, double rot): Camera(o, d, ny, nx) {
    this->focal_length = f;
    this->field_height = fh;
    this->field_width = fw;
    this->rot = rot;
    this->computeDirections();
}

Camera::~Camera(){
    delete this->imgBuffer;
    delete this->zBuffer;
}

void Camera::computeDirections(){
    this->direction = this->direction/this->direction.norm();
    this->width_dir = this->direction.vec(Vector3D(0, -1, 0));
    this->width_dir = rotate(
        this->width_dir, 
        Vector3D(0, 0, 0),
        this->direction,
        this->rot);
    this->width_dir = this->width_dir/this->width_dir.norm();
    this->height_dir = this->direction.vec(this->width_dir);
}

RenderedVertex Camera::project(Vector3D vec){
    Vector3D ul_corner = this->direction * focal_length
    - this->width_dir * this->field_width/2
    - this->height_dir * this->field_height/2;
    double z_distance = (vec - this->origin).dot(this->direction);
    Vector3D in_raster = (vec - this->origin) * this->focal_length/z_distance;
    Vector3D projected = in_raster - ul_corner;
    Vector2D coords(
        projected.dot(this->width_dir)/this->field_width*this->horizontal_resolution,
        projected.dot(this->height_dir)/this->field_height*this->vertical_resolution
    );
    return RenderedVertex(coords, z_distance);
}

tuple<RenderedVertex, RenderedVertex, RenderedVertex> Camera::projectTriangle(Triangle tri){
    RenderedVertex v1 = this->project(tri.v1);
    RenderedVertex v2 = this->project(tri.v2);
    RenderedVertex v3 = this->project(tri.v3);
    orderVertices(&v1, &v2, &v3);
    return make_tuple(v1, v2, v3);
}

void Camera::rasterize(Triangle tri){
    RenderedVertex v1, v2, v3;
    tie(v1, v2, v3) = projectTriangle(tri);
    if (!(this->inCameraSpace(v1) || this->inCameraSpace(v2) || this->inCameraSpace(v3))){
        return;
    }
    orderVertices(&v1, &v2, &v3);
    int min_x = max((int)v1.coords.x, 0);
    int max_x = min((int)max({v1.coords.x, v2.coords.x, v3.coords.x}), this->horizontal_resolution);
    int min_y = max((int)min({v1.coords.y, v2.coords.y, v3.coords.y}), 0);
    int max_y = min((int)max({v1.coords.y, v2.coords.y, v3.coords.y}), this->vertical_resolution);
    for (int x = min_x; x <= max_x; x++){
        for (int y = min_y; y < max_y; y++){
            Vector2D vec(x + 0.5, y + 0.5);
            if (pointInsideVertices(vec, v1.coords, v2.coords, v3.coords)){
                double w1, w2, w3;
                tie(w1, w2, w3) = getExtrapolationCoefs(vec, v1.coords, v2.coords, v3.coords);
                double inverse_z = w1/v1.z + w2/v2.z + w3/v3.z;
                if (inverse_z > zBuffer[this->horizontal_resolution * y + x]){
                    memcpy(imgBuffer+((this->horizontal_resolution * y + x) * 3), tri.color, 3 * sizeof(char));
                    zBuffer[this->horizontal_resolution * y + x] = inverse_z;
                }
            }
        }
    }
}

void Camera::renderScene(Scene scene){
    list<Triangle>::iterator tri_it;
    for (tri_it = scene.triangles.begin(); tri_it != scene.triangles.end(); ++tri_it){
        this->rasterize(*tri_it);
    }
}

void Camera::writeToFile(char *name){
    png::image< png::rgb_pixel > image(this->horizontal_resolution, this->vertical_resolution);
    for (int x = 0; x < this->horizontal_resolution; x++)
    {
        for (int y = 0; y < this->vertical_resolution; y++)
        {
            image[y][x] = png::rgb_pixel(this->imgBuffer[(y * this->horizontal_resolution + x) * 3], 
                                         this->imgBuffer[(y * this->horizontal_resolution + x) * 3 + 1], 
                                         this->imgBuffer[(y * this->horizontal_resolution + x) * 3 + 2]);
        }
    }
    image.write(name);
}

bool Camera::inCameraSpace(RenderedVertex vert){
    return (vert.z > 0) 
        && (vert.coords.x >= 0)
        && (vert.coords.x <= this->horizontal_resolution)
        && (vert.coords.y >= 0)
        && (vert.coords.y <= this->vertical_resolution);
}

void orderVertices(RenderedVertex *v1, RenderedVertex *v2, RenderedVertex *v3){
    if ((v2->coords.x <= v1->coords.x) && (v2->coords.x <= v3->coords.x)){
        swap(*v1, *v2);
    } else if ((v3->coords.x <= v1->coords.x) && (v3->coords.x <= v2->coords.x)){
        swap(*v1, *v3);
    }
    if ((v2->coords - v1->coords).cross(v3->coords - v1->coords) <= 0){
        swap(*v2, *v3);
    }
}