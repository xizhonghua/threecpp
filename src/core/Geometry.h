/*
 * Geometry.h
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#ifndef CORE_GEOMETRY_H_
#define CORE_GEOMETRY_H_

#include <vector>

#include "core/Face3.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Color.h"


namespace three {

class Geometry {
public:
  Geometry();
  ~Geometry();

  std::vector<Vector3> vertices;
  std::vector<Face3> faces;
  std::vector<Color> colors;
};

} /* namespace three */

#endif /* CORE_GEOMETRY_H_ */
