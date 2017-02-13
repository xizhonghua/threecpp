/*
 * BoxGeometry.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_GEOMETRIES_BOXGEOMETRY_H_
#define SRC_GEOMETRIES_BOXGEOMETRY_H_

#include <core/Geometry.h>

namespace three {

class BoxGeometry: public Geometry {
public:
  BoxGeometry();
  ~BoxGeometry();
};

} /* namespace three */

#endif /* SRC_GEOMETRIES_BOXGEOMETRY_H_ */
