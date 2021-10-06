#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <iostream>
#include <tuple>

using namespace std;
class Vector2D
{
public:
    double x;
    double y;
    Vector2D() = default;
    Vector2D(double x, double y);
    Vector2D operator + (Vector2D other);
    Vector2D operator - ();
    Vector2D operator - (Vector2D other);
    Vector2D operator * (double scal);
    Vector2D operator / (double scal);
    double cross(Vector2D other);
    double dot(Vector2D other);
    double norm();
    static double norm(Vector2D vec);
    bool operator == (Vector2D other) const;
};

ostream& operator<<(ostream& os, const Vector2D& vec);  

class Vector3D
{
public:
    public:
    double x;
    double y;
    double z;
    Vector3D() = default;
    Vector3D(double x, double y, double z);
    Vector3D operator + (Vector3D other);
    Vector3D operator - ();
    Vector3D operator - (Vector3D other);
    Vector3D operator * (double scal);
    Vector3D operator / (double scal);
    double dot(Vector3D other);
    double norm();
    static double norm(Vector3D vec);
    Vector3D vec(Vector3D other);
    bool operator == (Vector3D other) const;
};

ostream& operator<<(ostream& os, const Vector3D& vec); 

class Triangle
{
public:
    Vector3D v1;
    Vector3D v2;
    Vector3D v3;
    unsigned char color[3];
    Triangle() = default;
    Triangle(Vector3D v1, Vector3D v2, Vector3D v3);
    Triangle(Vector3D v1, Vector3D v2, Vector3D v3, unsigned char r, unsigned char g, unsigned char b);
};

Vector3D rotate(Vector3D vec, Vector3D center, Vector3D axis, double angle);

ostream& operator<<(ostream& os, const Triangle& tri);

bool pointInsideVertices(Vector2D point, Vector2D v1, Vector2D v2, Vector2D v3);

tuple<double, double, double> getExtrapolationCoefs(Vector2D point, Vector2D v1, Vector2D v2, Vector2D v3);

#endif