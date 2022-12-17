#include "test_utils.hpp"
#include "face.hpp"
#include "triangulation.hpp"


TEST(PolygonChains, monotonePolygon){
    Vector3D vertices[6] = {Vector3D(0,0,0), Vector3D(1,0,0), Vector3D(1.5,1,0), Vector3D(1,2,0), Vector3D(0,2,0), Vector3D(-0.5,1,0)};
    Face hexagon(vertices, 6);
    int starting_vertices[10];
    int chain_lengths[10];
    EXPECT_EQ(getPolygonChains(hexagon, chain_lengths, starting_vertices), 2);
    EXPECT_EQ(chain_lengths[0], 4);
    EXPECT_EQ(chain_lengths[1], 4);
    EXPECT_EQ(starting_vertices[0], 0);
    EXPECT_EQ(starting_vertices[1], 3);
}

TEST(PolygonChains, nonMonotonePolygon){
  Vector3D vertices[7] = {Vector3D(0,0,0), Vector3D(2,0,0), Vector3D(3,1,0), Vector3D(2,2,0), Vector3D(1,1,0), Vector3D(0,2,0), Vector3D(-1,1,0)};
  Face heart(vertices, 7);
  int starting_vertices[10];
  int chain_lengths[10];
  EXPECT_EQ(getPolygonChains(heart, chain_lengths, starting_vertices), 4);
  EXPECT_EQ(chain_lengths[0], 4);
  EXPECT_EQ(chain_lengths[1], 2);
  EXPECT_EQ(chain_lengths[2], 2);
  EXPECT_EQ(chain_lengths[3], 3);
  EXPECT_EQ(starting_vertices[0], 0);
  EXPECT_EQ(starting_vertices[1], 3);
  EXPECT_EQ(starting_vertices[2], 4);
  EXPECT_EQ(starting_vertices[3], 5);
}