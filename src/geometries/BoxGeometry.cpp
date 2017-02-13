/*
 * BoxGeometry.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <geometries/BoxGeometry.h>

namespace three {

BoxGeometry::BoxGeometry(double width, double height, double depth,
    int widthSegments, int heightSegments, int depthSegments) :
    width(width), height(height), depth(depth), widthSegments(widthSegments), heightSegments(
        heightSegments), depthSegments(depthSegments) {

  Vector3 v0 { 0, 0, 0 };
  Vector3 v1 { width, 0, 0 };
  Vector3 v2 { width, height, 0 };
  Vector3 v3 { 0, height, 0 };

  Vector3 v4 { 0, 0, depth };
  Vector3 v5 { width, 0, depth };
  Vector3 v6 { width, height, depth };
  Vector3 v7 { 0, height, depth };

  this->vertices.push_back(v0);
  this->vertices.push_back(v1);
  this->vertices.push_back(v2);
  this->vertices.push_back(v3);
  this->vertices.push_back(v4);
  this->vertices.push_back(v5);
  this->vertices.push_back(v6);
  this->vertices.push_back(v7);

  Face3 f0 { 0, 3, 1 };
  Face3 f1 { 0, 1, 2 };
  Face3 f2 { 0, 1, 2 };
  Face3 f3 { 0, 1, 2 };
  Face3 f4 { 0, 1, 2 };
  Face3 f5 { 0, 1, 2 };
  Face3 f6 { 0, 1, 2 };
  Face3 f7 { 0, 1, 2 };
  Face3 f8 { 0, 1, 2 };
  Face3 f9 { 0, 1, 2 };
  Face3 f10 { 0, 1, 2 };
  Face3 f11 { 0, 1, 2 };
  Face3 f12 { 0, 1, 2 };

  this->faces = {f0, f1, f2, f3};


}

BoxGeometry::~BoxGeometry() {
  // TODO Auto-generated destructor stub
}

} /* namespace three */
