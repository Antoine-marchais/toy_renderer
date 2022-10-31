#include "camera.hpp"
#include "test_utils.hpp"

TEST(CameraTest, directionSetup) {
    Camera test_camera(Vector3D(0, 1, 1), Vector3D(1, 1, 1));
    EXPECT_NEAR(test_camera.direction.norm(), 1, 0.000001);
    EXPECT_NEAR(test_camera.width_dir.norm(), 1, 0.000001);
    EXPECT_NEAR(test_camera.height_dir.norm(), 1, 0.000001);

    EXPECT_LT(test_camera.direction.dot(test_camera.width_dir), 0.000001);
    EXPECT_LT(test_camera.width_dir.dot(test_camera.height_dir), 0.000001);
    EXPECT_LT(test_camera.height_dir.dot(test_camera.direction), 0.000001);
}

TEST(CameraTest, projection) {
    Camera test_camera(Vector3D(0, 0, 0), Vector3D(0, 0, 1), 0.1, 0.1, 0.1, 100, 100, 0);
    RenderedVertex projUL = test_camera.project(Vector3D(-0.1, -0.1, 0.2));
    EXPECT_TRUE(VectorNear(projUL.coords, Vector2D(0, 0), 0.000001));
    RenderedVertex projUR = test_camera.project(Vector3D(0.2, -0.2, 0.4));
    EXPECT_TRUE(VectorNear(projUR.coords, Vector2D(100, 0), 0.000001));
    RenderedVertex projCenter = test_camera.project(Vector3D(0, 0, 0.4));
    EXPECT_TRUE(VectorNear(projCenter.coords, Vector2D(50, 50), 0.000001));
}

TEST(CameraTest, displacedProjection){
    Camera test_camera(Vector3D(-0.2, 0, 0.2), Vector3D(1, 0, 0), 0.1, 0.1, 0.1, 100, 100, 0);
    RenderedVertex projUM = test_camera.project(Vector3D(0.2, -0.2, 0.2));
    EXPECT_TRUE(VectorNear(projUM.coords, Vector2D(50, 0), 0.000001));
    EXPECT_EQ(projUM.z, 0.4);
}

TEST(CameraTest, verticesOrdering){
    RenderedVertex v1(Vector2D(0, 1), 1);
    RenderedVertex v2(Vector2D(0, 0), 2);
    RenderedVertex v3(Vector2D(0.5, 1), 3);
    orderVertices(&v1, &v2, &v3);
    EXPECT_EQ(Vector2D(0, 0), v1.coords);
    EXPECT_EQ(Vector2D(0.5, 1), v2.coords);
    EXPECT_EQ(Vector2D(0, 1), v3.coords);
}
