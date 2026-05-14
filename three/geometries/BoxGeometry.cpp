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
  this->vertices.clear();
  this->faces.clear();

  Vector3 v0 { 0, 0, 0 };
  Vector3 v1 { width_, 0, 0 };
  Vector3 v2 { width_, height_, 0 };
  Vector3 v3 { 0, height_, 0 };

  Vector3 v4 { 0, 0, depth_ };
  Vector3 v5 { width_, 0, depth_ };
  Vector3 v6 { width_, height_, depth_ };
  Vector3 v7 { 0, height_, depth_ };

  // Back
  this->vertices.insert(this->vertices.end(), {v0, v1, v2, v3});
  this->faces.emplace_back(0, 2, 1);
  this->faces.emplace_back(0, 3, 2);

  // Left
  this->vertices.insert(this->vertices.end(), {v0, v4, v7, v3});
  this->faces.emplace_back(4, 6, 7);
  this->faces.emplace_back(4, 5, 6);

  // Front
  this->vertices.insert(this->vertices.end(), {v4, v5, v6, v7});
  this->faces.emplace_back(8, 10, 11);
  this->faces.emplace_back(8, 9, 10);

  // Bottom
  this->vertices.insert(this->vertices.end(), {v0, v1, v5, v4});
  this->faces.emplace_back(12, 13, 14);
  this->faces.emplace_back(12, 14, 15);

  // Top
  this->vertices.insert(this->vertices.end(), {v3, v2, v6, v7});
  this->faces.emplace_back(19, 17, 16);
  this->faces.emplace_back(19, 18, 17);

  // Right
  this->vertices.insert(this->vertices.end(), {v1, v5, v6, v2});
  this->faces.emplace_back(22, 21, 20);
  this->faces.emplace_back(22, 20, 23);

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
