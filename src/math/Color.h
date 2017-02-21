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
  Color();
  Color(int hex);
  Color(float r, float g, float b);
  Color(const Color& c) = default;
  Color(Color&& c) = default;
  Color& operator=(const Color& c) = default;

  ~Color();

  Color& setRGB(float r, float g, float b);
  Color& setHex(int hex);

  // Convert int to Color
  Color& operator=(int hex);

  float r { 0 };
  float g { 0 };
  float b { 0 };
};

} /* namespace three */

#endif /* MATH_COLOR_H_ */
