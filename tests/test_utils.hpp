#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <gtest/gtest.h>
#include "geometry.hpp"

using namespace testing;

AssertionResult VectorNear(Vector3D a, Vector3D b, double margin);

AssertionResult VectorNear(Vector2D a, Vector2D b, double margin);

#endif