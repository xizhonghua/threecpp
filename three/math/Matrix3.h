/*
 * Matrix3.h
 *
 *  Created on: Feb 22, 2017
 *      Author: zxi
 */

#ifndef THREE_MATH_MATRIX3_H_
#define THREE_MATH_MATRIX3_H_

namespace three {

class Matrix4;

struct __Matrix3 {
  union {

    struct {
      double m00, m01, m02;
      double m10, m11, m12;
      double m20, m21, m22;
    };

    double elements[9];
  };
};

class Matrix3: public __Matrix3 {
public:
  Matrix3();
  virtual ~Matrix3();

  Matrix3& set(double m00, double m01, double m02, double m10, double m11,
      double m12, double m20, double m21, double m22) {

    this->m00 = m00;
    this->m01 = m01;
    this->m02 = m02;
    this->m10 = m10;
    this->m11 = m11;
    this->m12 = m12;
    this->m20 = m20;
    this->m21 = m21;
    this->m22 = m22;

    return *this;
  }


  Matrix3& getNormalMatrix(const Matrix4& m);

  Matrix3& setFromMatrix4(const Matrix4& m);

  Matrix3& transpose();

};

} /* namespace three */

#endif /* THREE_MATH_MATRIX3_H_ */
