/*
 * BoxGeometry.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_GEOMETRIES_BOXGEOMETRY_H_
#define THREE_GEOMETRIES_BOXGEOMETRY_H_

#include <three/core/Geometry.h>

namespace three {

class BoxGeometry: public Geometry {
public:
  BoxGeometry(double width, double height, double depth, int widthSegments = 1,
      int heightSegments = 1, int depthSegments = 1);

  ~BoxGeometry();
private:
  double width;
  double height;
  double depth;
  int widthSegments;
  int heightSegments;
  int depthSegments;
};

} /* namespace three */

#endif /* THREE_GEOMETRIES_BOXGEOMETRY_H_ */
