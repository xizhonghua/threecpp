/*
 * Color.h
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#ifndef MATH_COLOR_H_
#define MATH_COLOR_H_

namespace three {

class Color {
public:
  Color(float r = 0, float g = 0, float b = 0);
  Color(long long hex);

  ~Color();

  inline Color& setRGB(float r, float g, float b);

  float r { 0 };
  float g { 0 };
  float b { 0 };
};

} /* namespace three */

#endif /* MATH_COLOR_H_ */
