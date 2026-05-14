/*
 * Geometry.h
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#ifndef THREE_CORE_GEOMETRY_H_
#define THREE_CORE_GEOMETRY_H_

#include <vector>

#include <three/core/Face3.h>
#include <three/math/Color.h>
#include <three/math/Matrix4.h>
#include <three/math/Vector2.h>
#include <three/math/Vector3.h>

namespace three {

class Geometry {
public:
  Geometry();
  ~Geometry();

  Geometry& applyMatrix(const Matrix4& m);

  virtual void computeVertexNormals();
  virtual void computeVerticesArray();
  virtual void computeFacesArray();
  virtual void computeColorsArray();

  std::vector<Vector3> vertices;
  std::vector<Face3> faces;
  std::vector<Color> colors;

  // Computed arrays for rendering
  std::vector<float> normalsArray;
  std::vector<float> verticesArray;
  std::vector<unsigned int> facesArray;
  std::vector<float> colorsArray;
};

} /* namespace three */

#endif /* THREE_CORE_GEOMETRY_H_ */
