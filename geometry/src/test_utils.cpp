#include "test_utils.hpp"

AssertionResult VectorNear(Vector3D a, Vector3D b, double margin){
  double distance = Vector3D::norm(a-b);
  if (distance < margin){
    return AssertionSuccess();
  } else {
    return AssertionFailure() << "expected: " << a << " - actual: " << b << " - distance: " << distance;
  }
}

AssertionResult VectorNear(Vector2D a, Vector2D b, double margin){
    double distance = Vector2D::norm(a-b);
    if (distance < margin){
        return AssertionSuccess();
    } else {
        return AssertionFailure() << "expected: " << a << " - actual: " << b << " - distance: " << distance;
    }
}