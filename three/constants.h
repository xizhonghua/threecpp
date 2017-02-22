/*
 * constants.h
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#ifndef THREE_CONSTANTS_H_
#define THREE_CONSTANTS_H_

enum class SideMode {
  FrontSide, BackSide, DoubleSide
};

enum class ShadingMode {
  SmoothShading, FlatShading
};

enum class ColorMode {
  NoColors, FaceColors, VertexColors
};

enum class BlendingMode {
  NoBlending,
  NormalBlending,
  AdditiveBlending,
  SubtractiveBlending,
  MultiplyBlending,
  CustomBlending
};

enum DepthMode {
  NeverDepth,
  AlwaysDepth,
  LessDepth,
  LessEqualDepth,
  GreaterEqualDepth,
  GreaterDepth,
  NotEqualDepth
};

enum TextureCombineMode {
  MultiplyOperation, MixOperation, AddOperation
};

#endif /* THREE_CONSTANTS_H_ */
