/*
 * Geometry.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#include <three/core/Geometry.h>

#include <cmath>

namespace three {

Geometry::Geometry() {
}

Geometry::~Geometry() {
}

Geometry& Geometry::applyMatrix(const Matrix4& m) {

  for (Vector3& v : vertices) {
    v *= m;
  }

  //TODO(zxi)
  // face normals, etc.

  return *this;
}

void Geometry::computeVertexNormals() {
  normalsArray.assign(vertices.size() * 3, 0.0f);

  for (const Face3& f : faces) {
    const Vector3& vA = vertices[f.a];
    const Vector3& vB = vertices[f.b];
    const Vector3& vC = vertices[f.c];

    double ux = vB.x - vA.x;
    double uy = vB.y - vA.y;
    double uz = vB.z - vA.z;
    double vx = vC.x - vA.x;
    double vy = vC.y - vA.y;
    double vz = vC.z - vA.z;

    double nx = uy * vz - uz * vy;
    double ny = uz * vx - ux * vz;
    double nz = ux * vy - uy * vx;

    normalsArray[f.a * 3] += static_cast<float>(nx);
    normalsArray[f.a * 3 + 1] += static_cast<float>(ny);
    normalsArray[f.a * 3 + 2] += static_cast<float>(nz);

    normalsArray[f.b * 3] += static_cast<float>(nx);
    normalsArray[f.b * 3 + 1] += static_cast<float>(ny);
    normalsArray[f.b * 3 + 2] += static_cast<float>(nz);

    normalsArray[f.c * 3] += static_cast<float>(nx);
    normalsArray[f.c * 3 + 1] += static_cast<float>(ny);
    normalsArray[f.c * 3 + 2] += static_cast<float>(nz);
  }

  for (size_t i = 0; i < vertices.size(); ++i) {
    float nx = normalsArray[i * 3];
    float ny = normalsArray[i * 3 + 1];
    float nz = normalsArray[i * 3 + 2];
    float len = std::sqrt(nx * nx + ny * ny + nz * nz);
    if (len > 0.0f) {
      normalsArray[i * 3] = nx / len;
      normalsArray[i * 3 + 1] = ny / len;
      normalsArray[i * 3 + 2] = nz / len;
    }
  }
}

void Geometry::computeVerticesArray() {
  verticesArray.reserve(vertices.size() * 3);
  for (const Vector3& v : vertices) {
    verticesArray.push_back(static_cast<float>(v.x));
    verticesArray.push_back(static_cast<float>(v.y));
    verticesArray.push_back(static_cast<float>(v.z));
  }
}

void Geometry::computeFacesArray() {
  facesArray.reserve(faces.size() * 3);
  for (const Face3& f : faces) {
    facesArray.push_back(f.a);
    facesArray.push_back(f.b);
    facesArray.push_back(f.c);
  }
}

void Geometry::computeColorsArray() {
  colorsArray.assign(normalsArray.size(), 0.0f);
  for (size_t i = 0; i < normalsArray.size(); ++i) {
    colorsArray[i] = (normalsArray[i] + 1.0f) / 2.0f;
  }
}

} /* namespace three */
