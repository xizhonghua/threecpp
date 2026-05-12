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

/**
 * BoxGeometry creates a box geometry with the specified dimensions.
 * The box is centered at the origin and consists of 8 vertices and 12 triangular faces.
 */
class BoxGeometry: public Geometry {
public:
  /**
   * Constructs a BoxGeometry.
   * @param width The width of the box. Default is 1.
   * @param height The height of the box. Default is 1.
   * @param depth The depth of the box. Default is 1.
   * @param widthSegments The number of width segments (currently unused). Default is 1.
   * @param heightSegments The number of height segments (currently unused). Default is 1.
   * @param depthSegments The number of depth segments (currently unused). Default is 1.
   */
  BoxGeometry(double width = 1, double height = 1, double depth = 1, int widthSegments = 1,
      int heightSegments = 1, int depthSegments = 1);

  ~BoxGeometry();

  // Getters and setters
  double width() const { return width_; }
  BoxGeometry& width(double width);

  double height() const { return height_; }
  BoxGeometry& height(double height);

  double depth() const { return depth_; }
  BoxGeometry& depth(double depth);

  int widthSegments() const { return widthSegments_; }
  BoxGeometry& widthSegments(int widthSegments);

  int heightSegments() const { return heightSegments_; }
  BoxGeometry& heightSegments(int heightSegments);

  int depthSegments() const { return depthSegments_; }
  BoxGeometry& depthSegments(int depthSegments);

private:
  void generateGeometry();

  double width_;
  double height_;
  double depth_;
  int widthSegments_;
  int heightSegments_;
  int depthSegments_;
};

} /* namespace three */

#endif /* THREE_GEOMETRIES_BOXGEOMETRY_H_ */
