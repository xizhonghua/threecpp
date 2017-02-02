/*
 * Face3.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef CORE_FACE3_H_
#define CORE_FACE3_H_

#include <vector>

#include "math/Vector3.h"
#include "math/Color.h"

namespace three {

class Face3 {
public:
  Face3(const Vector3& a, const Vector3& b, const Vector3& c);
  Face3(const Vector3& a, const Vector3& b, const Vector3& c,
      const Vector3& normal);

  Face3(const Face3& f) = default;
  Face3(Face3&& f) = default;

  ~Face3();

  Vector3 a;
  Vector3 b;
  Vector3 c;
  Vector3 normal;

  Color color;

  std::vector<Vector3> vertexNormals;
  std::vector<Color> vertexColors;

  int materialIndex { 0 };
};

} /* namespace three */

#endif /* CORE_FACE3_H_ */
