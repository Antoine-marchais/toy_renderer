#include "test_utils.hpp"

TEST(GeomTest, vectorAdd) {
  Vector3D a = Vector3D(1, 2, 3);
  Vector3D b = Vector3D(2, 0, 5);
  Vector3D c = a + b;
  EXPECT_EQ(c, Vector3D(3, 2, 8));

  Vector2D d = Vector2D(1, 2);
  Vector2D e = Vector2D(2, 0);
  Vector2D f = d + e;
  EXPECT_EQ(f, Vector2D(3, 2));
}

TEST(GeomTest, vectorSub) {
  Vector3D a = Vector3D(1, 2, 3);
  Vector3D b = Vector3D(2, 0, 5);
  Vector3D c = a - b;
  EXPECT_EQ(c, Vector3D(-1, 2, -2));

  Vector2D d = Vector2D(1, 2);
  Vector2D e = Vector2D(2, 0);
  Vector2D f = d - e;
  EXPECT_EQ(f, Vector2D(-1, 2));
}

TEST(GeomTest, vectorDot) {
  Vector3D a = Vector3D(1, 2, 3);
  Vector3D b = Vector3D(2, 0, 5);
  EXPECT_EQ(a.dot(b), 17);

  Vector2D c = Vector2D(1, 2);
  Vector2D d = Vector2D(2, 0);
  EXPECT_EQ(c.dot(d), 2);
}

TEST(GeomTest, vectorNorm) {
  Vector2D a(3, 4);
  EXPECT_EQ(a.norm(), 5);

  Vector3D b(3, 4, 5);
  EXPECT_NEAR(b.norm(), 7.071, 0.001);
}

TEST(GeomTest, vectorScale) {
  Vector2D a(2, 1);
  EXPECT_EQ(a * 1.5, Vector2D(3, 1.5));
  EXPECT_EQ(a / 2, Vector2D(1, 0.5));

  Vector3D b(3, 4, 2);
  EXPECT_EQ(b * 2, Vector3D(6, 8, 4));
  EXPECT_EQ(b / 2, Vector3D(1.5, 2, 1));
}

TEST(GeomTest, vectorialProduct) {
  Vector3D a(1, 1, 0);
  Vector3D b(0, 0, 1);
  Vector3D product = a.vec(b);
  Vector3D expected_dir(1, -1, 0);
  EXPECT_EQ(product/product.norm(), expected_dir/expected_dir.norm());
}

TEST(GeomTest, rotation) {
  Vector3D a(1, 0, 1);
  Vector3D rotated = rotate(a, Vector3D(0, 0, 1), Vector3D(0, 0, 1), 90);
  Vector3D expected = Vector3D(0, 1, 1);
  EXPECT_TRUE(VectorNear(rotated, expected, 0.000001));
}

TEST(GeomTest, pointInVertices){
    Vector2D v1(0, 0);
    Vector2D v2(0.5, 1);
    Vector2D v3(0, 1);
    Vector2D point_in(0.1, 0.5);
    Vector2D point_out(-0.1, 0.5);
    EXPECT_TRUE(pointInsideVertices(point_in, v1, v2, v3));
    EXPECT_FALSE(pointInsideVertices(point_out, v1, v2, v3));
}

TEST(GeomTest, projectToPlane){
    Vector3D v1(1, 1, 3);
    Vector3D v2(3, 1, 3);
    Vector3D v3(2, 3, 3);
    Vector3D point(2, 2, 3);
    Vector3D axis = (v2-v1)/(v2-v1).norm();
    Vector3D rotatedV3 = rotate(v3, v1, axis, 30);
    Vector3D rotatedPoint = rotate(point, v1, axis, 30);
    Vector2D projected = projectToPlane(v1, v2, v3, point);
    Vector2D rotatedProjected = projectToPlane(v1, v2, rotatedV3, rotatedPoint);
    Vector2D expected = Vector2D(1, 1);
    EXPECT_TRUE(VectorNear(projected, expected, 0.000001));
    EXPECT_TRUE(VectorNear(rotatedProjected, expected, 0.000001));
}

TEST(GeomTest, expandFromPlane){
    Vector3D v1(1, 1, 3);
    Vector3D v2(3, 1, 3);
    Vector3D v3(2, 3, 3);
    Vector3D point(2, 2, 3);
    Vector3D axis = (v2-v1)/(v2-v1).norm();
    Vector3D rotatedV3 = rotate(v3, v1, axis, 30);
    Vector3D rotatedPoint = rotate(point, v1, axis, 30);
    Vector2D rotatedProjected = projectToPlane(v1, v2, rotatedV3, rotatedPoint);
    Vector3D expanded = expandFromPlane(v1, v2, rotatedV3, rotatedProjected);
    EXPECT_TRUE(VectorNear(rotatedPoint, expanded, 0.000001));
}
