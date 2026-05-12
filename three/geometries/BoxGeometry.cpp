/*
 * BoxGeometry.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <three/geometries/BoxGeometry.h>

namespace three {

BoxGeometry::BoxGeometry(double width, double height, double depth,
    int widthSegments, int heightSegments, int depthSegments) :
    width_(width), height_(height), depth_(depth), widthSegments_(widthSegments), heightSegments_(
        heightSegments), depthSegments_(depthSegments) {
  generateGeometry();
}

BoxGeometry::~BoxGeometry() {
}

void BoxGeometry::generateGeometry() {
  Vector3 v0 { 0, 0, 0 };
  Vector3 v1 { width_, 0, 0 };
  Vector3 v2 { width_, height_, 0 };
  Vector3 v3 { 0, height_, 0 };

  Vector3 v4 { 0, 0, depth_ };
  Vector3 v5 { width_, 0, depth_ };
  Vector3 v6 { width_, height_, depth_ };
  Vector3 v7 { 0, height_, depth_ };

  this->vertices = {v0, v1, v2, v3, v4, v5, v6, v7};

  // Back
  Face3 f0 { 0, 2, 1 };
  Face3 f1 { 0, 3, 2 };

  // Left
  Face3 f2 { 0, 7, 3 };
  Face3 f3 { 0, 4, 7 };

  // Front
  Face3 f4 { 4, 6, 7 };
  Face3 f5 { 4, 5, 6 };

  // bottom
  Face3 f6 { 0, 1, 5 };
  Face3 f7 { 0, 5, 4 };

  // Top
  Face3 f8 { 7, 2, 3 };
  Face3 f9 { 7, 6, 2 };

  // Right
  Face3 f10 { 6, 5, 1 };
  Face3 f11 { 6, 1, 2 };

  this->faces = {f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11};

  // Translate center to (0,0,0);
  Matrix4 m = Matrix4::makeTranslation(
      Vector3(-width_ / 2, -height_ / 2, -depth_ / 2));

  this->applyMatrix(m);
}

BoxGeometry& BoxGeometry::width(double width) {
  this->width_ = width;
  generateGeometry();
  return *this;
}

BoxGeometry& BoxGeometry::height(double height) {
  this->height_ = height;
  generateGeometry();
  return *this;
}

BoxGeometry& BoxGeometry::depth(double depth) {
  this->depth_ = depth;
  generateGeometry();
  return *this;
}

BoxGeometry& BoxGeometry::widthSegments(int widthSegments) {
  this->widthSegments_ = widthSegments;
  generateGeometry();
  return *this;
}

BoxGeometry& BoxGeometry::heightSegments(int heightSegments) {
  this->heightSegments_ = heightSegments;
  generateGeometry();
  return *this;
}

BoxGeometry& BoxGeometry::depthSegments(int depthSegments) {
  this->depthSegments_ = depthSegments;
  generateGeometry();
  return *this;
}

} /* namespace three */
