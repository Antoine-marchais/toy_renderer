#include <iostream>
#include "geometry.hpp"
#include <cmath>
#include <string.h>
using namespace std;

Vector2D::Vector2D(double x, double y){
    this->x = x;
    this->y = y;
}

double Vector2D::dot(Vector2D other){
    return this->x*other.x + this->y*other.y;
}

double Vector2D::norm(){
    return sqrt(this->x*this->x + this->y*this->y);
}

double Vector2D::norm(Vector2D vec){
    return vec.norm();
}

Vector2D Vector2D::operator+ (Vector2D other){
    return Vector2D(
        this->x+other.x,
        this->y+other.y
    );
}

Vector2D Vector2D::operator- (Vector2D other){
    return Vector2D(
        this->x-other.x,
        this->y-other.y
    );
}

Vector2D Vector2D::operator- (){
    return Vector2D(-this->x, -this->y);
}

Vector2D Vector2D::operator* (double scal){
    return Vector2D(scal*this->x, scal*this->y);
}

Vector2D Vector2D::operator/ (double scal){
    return Vector2D(this->x/scal, this->y/scal);
}

bool Vector2D::operator== (Vector2D other) const {
    return (this->x == other.x) && (this->y == other.y);
}

double Vector2D::cross(Vector2D other){
    return this->x*other.y - this->y*other.x;
}

Vector3D::Vector3D(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D Vector3D::operator+ (Vector3D other){
    return Vector3D(
        this->x+other.x,
        this->y+other.y,
        this->z+other.z
    );
}

Vector3D Vector3D::operator- (Vector3D other){
    return Vector3D(
        this->x-other.x,
        this->y-other.y,
        this->z-other.z
    );
}

Vector3D Vector3D::operator- (){
    return Vector3D(-this->x, -this->y, -this->z);
}

Vector3D Vector3D::operator* (double scal){
    return Vector3D(scal*this->x, scal*this->y, scal*this->z);
}

Vector3D Vector3D::operator/ (double scal){
    return Vector3D(this->x/scal, this->y/scal, this->z/scal);
}

bool Vector3D::operator== (Vector3D other) const {
    return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
}

double Vector3D::dot(Vector3D other){
    return this->x*other.x + this->y*other.y + this->z*other.z;
}

double Vector3D::norm(){
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

double Vector3D::norm(Vector3D vec){
    return vec.norm();
}

Vector3D Vector3D::vec(Vector3D other){
    return Vector3D(
        this->y*other.z - this->z*other.y,
        this->z*other.x - this->x*other.z,
        this->x*other.y - this->y*other.x
    );
}

Triangle::Triangle(Vector3D v1, Vector3D v2, Vector3D v3){
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->color[0] = 255;
    this->color[1] = 255;
    this->color[2] = 255;
}

Triangle::Triangle(Vector3D v1, Vector3D v2, Vector3D v3, unsigned char r, unsigned char g, unsigned char b): Triangle(v1, v2, v3){
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}

Vector2D projectToPlane(Vector3D v1, Vector3D v2, Vector3D v3, Vector3D expanded){
    Vector3D x_axis = (v2 - v1)/(v2 - v1).norm();
    Vector3D y_axis = (v3 - v1) - x_axis * x_axis.dot(v3-v1);
    y_axis = y_axis / y_axis.norm();
    return Vector2D((expanded-v1).dot(x_axis), (expanded-v1).dot(y_axis));
}

Vector3D expandFromPlane(Vector3D v1, Vector3D v2, Vector3D v3, Vector2D projected){
    Vector3D x_axis = (v2 - v1)/(v2 - v1).norm();
    Vector3D y_axis = (v3 - v1) - x_axis * x_axis.dot(v3-v1);
    y_axis = y_axis / y_axis.norm();
    return v1 + x_axis * projected.x + y_axis * projected.y;
}


ostream& operator<<(ostream& os, const Vector2D& vec){
    os << "Vector2D(" << vec.x << ", " << vec.y << ")";
    return os;
}

ostream& operator<<(ostream& os, const Vector3D& vec){
    os << "Vector3D(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

ostream& operator<<(ostream& os, const Triangle& tri){
    os << "Triangle(" << tri.v1 << ", " << tri.v2 << ", " << tri.v3 << ")";
    return os;
}

Vector3D rotate(Vector3D vec, Vector3D center, Vector3D axis, double angle){
    Vector3D centered_vector = vec-center;
    double rad_angle = M_PI/180*angle;
    return axis*axis.dot(centered_vector)
    + axis.vec(centered_vector).vec(axis)*cos(rad_angle)
    + axis.vec(centered_vector)*sin(rad_angle)
    + center;
}


bool pointInsideVertices(Vector2D point, Vector2D v1, Vector2D v2, Vector2D v3){
    return ((v2-v1).cross(point-v1) >= 0)
            && ((v1-v3).cross(point-v3) >= 0)
            && ((v3-v2).cross(point-v2) >= 0);
}

tuple<double, double, double> getExtrapolationCoefs(Vector2D point, Vector2D v1, Vector2D v2, Vector2D v3){
    double area2 = abs((v2-v1).cross(v3-v1));
    double coef1 = abs((v2-point).cross(v3-point)/area2);
    double coef2 = abs((v3-point).cross(v1-point)/area2);
    double coef3 = abs((v2-point).cross(v1-point)/area2);
    return make_tuple(coef1, coef2, coef3);
}