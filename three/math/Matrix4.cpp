/*
 * Matrix4.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: zxi
 */

#include <three/math/Matrix4.h>

#include <three/math/Quaternion.h>

namespace three {

Matrix4::Matrix4() {
  this->identity();
}

Matrix4::~Matrix4() {
}

////////////////////////////////////////////////////////////////////
Matrix4& Matrix4::lookAt(const Vector3& eye, const Vector3& target,
    const Vector3& up) {

  Vector3 z = (eye - target).normalize();
  if (z.lengthSq() == 0) {
    z.z = 1.0;
  }

  Vector3 x = (up % z).normalize();
  if (x.lengthSq() == 0) {
    z.z += 0.0001;
    x = up % z;
  }

  Vector3 y = z % x;

  auto& te = this->elements;

  te[0] = x.x;
  te[1] = x.y;
  te[2] = x.z;

  te[4] = y.x;
  te[5] = y.y;
  te[6] = y.z;

  te[8] = z.x;
  te[9] = z.y;
  te[10] = z.z;

  return *this;
}

double Matrix4::determinant() const {
  auto te = this->elements;

  auto n11 = te[0], n12 = te[4], n13 = te[8], n14 = te[12];
  auto n21 = te[1], n22 = te[5], n23 = te[9], n24 = te[13];
  auto n31 = te[2], n32 = te[6], n33 = te[10], n34 = te[14];
  auto n41 = te[3], n42 = te[7], n43 = te[11], n44 = te[15];

  //TODO: make this more efficient
  //( based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm )

  return (n41
      * (+n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33
          + n13 * n22 * n34 - n12 * n23 * n34)
      + n42
          * (+n11 * n23 * n34 - n11 * n24 * n33 + n14 * n21 * n33
              - n13 * n21 * n34 + n13 * n24 * n31 - n14 * n23 * n31)
      + n43
          * (+n11 * n24 * n32 - n11 * n22 * n34 - n14 * n21 * n32
              + n12 * n21 * n34 + n14 * n22 * n31 - n12 * n24 * n31)
      + n44
          * (-n13 * n22 * n31 - n11 * n23 * n32 + n11 * n22 * n33
              + n13 * n21 * n32 - n12 * n21 * n33 + n12 * n23 * n31)

  );
}

Matrix4& Matrix4::toArray(std::vector<double>& array, int offset) {
  return this->toArray(&array[0], offset);
}

Matrix4& Matrix4::toArray(double* array, int offset) {
  for (int i = 0; i < 16; ++i) {
    array[offset + i] = this->elements[i];
  }

  return *this;
}

Matrix4& Matrix4::asPerspective(double left, double right, double top,
    double bottom, double near, double far) {

  auto te = this->elements;
  double x = 2 * near / (right - left);
  double y = 2 * near / (top - bottom);

  double a = (right + left) / (right - left);
  double b = (top + bottom) / (top - bottom);
  double c = -(far + near) / (far - near);
  double d = -2 * far * near / (far - near);

  te[0] = x;
  te[4] = 0;
  te[8] = a;
  te[12] = 0;
  te[1] = 0;
  te[5] = y;
  te[9] = b;
  te[13] = 0;
  te[2] = 0;
  te[6] = 0;
  te[10] = c;
  te[14] = d;
  te[3] = 0;
  te[7] = 0;
  te[11] = -1;
  te[15] = 0;

  return *this;
}

Matrix4& Matrix4::asOrthographic(double left, double right, double top,
    double bottom, double near, double far) {

  auto te = this->elements;
  auto w = 1.0 / (right - left);
  auto h = 1.0 / (top - bottom);
  auto p = 1.0 / (far - near);

  auto x = (right + left) * w;
  auto y = (top + bottom) * h;
  auto z = (far + near) * p;

  te[0] = 2 * w;
  te[4] = 0;
  te[8] = 0;
  te[12] = -x;
  te[1] = 0;
  te[5] = 2 * h;
  te[9] = 0;
  te[13] = -y;
  te[2] = 0;
  te[6] = 0;
  te[10] = -2 * p;
  te[14] = -z;
  te[3] = 0;
  te[7] = 0;
  te[11] = 0;
  te[15] = 1;

  return *this;
}

Matrix4& Matrix4::asLookAt(const Vector3& eye, const Vector3& target,
    const Vector3& up) {

  double* te = this->elements;

  Vector3 z = (eye - target).normalize();

  if (z.lengthSq() == 0) {

    z.z = 1;

  }

  Vector3 x = (up % z).normalize();

  if (x.lengthSq() == 0) {

    z.z += 0.0001;
    x = (up % z).normalize();

  }

  Vector3 y = z % x;

  te[0] = x.x;
  te[4] = y.x;
  te[8] = z.x;
  te[1] = x.y;
  te[5] = y.y;
  te[9] = z.y;
  te[2] = x.z;
  te[6] = y.z;
  te[10] = z.z;

  te[12] = -(x * eye);
  te[13] = -(y * eye);
  te[14] = -(z * eye);

  return *this;
}

Matrix4& Matrix4::asRotation(const Quaternion& q) {
  auto te = this->elements;

  auto x = q.x, y = q.y, z = q.z, w = q.w;
  auto x2 = x + x, y2 = y + y, z2 = z + z;
  auto xx = x * x2, xy = x * y2, xz = x * z2;
  auto yy = y * y2, yz = y * z2, zz = z * z2;
  auto wx = w * x2, wy = w * y2, wz = w * z2;

  te[0] = 1 - (yy + zz);
  te[4] = xy - wz;
  te[8] = xz + wy;

  te[1] = xy + wz;
  te[5] = 1 - (xx + zz);
  te[9] = yz - wx;

  te[2] = xz - wy;
  te[6] = yz + wx;
  te[10] = 1 - (xx + yy);

  // last column
  te[3] = 0;
  te[7] = 0;
  te[11] = 0;

  // bottom row
  te[12] = 0;
  te[13] = 0;
  te[14] = 0;
  te[15] = 1;

  return *this;
}

Matrix4& Matrix4::asCompose(const Vector3& position,
    const Quaternion& quaternion, const Vector3& scale) {

  this->asRotation(quaternion);
  this->scale(scale);
  this->setPosition(position);

  return *this;
}

Matrix4& Matrix4::getInverse(const Matrix4& m) {

  // based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
  auto te = this->elements;
  auto me = m.elements;

  auto

  n11 = me[0], n21 = me[1], n31 = me[2], n41 = me[3], n12 = me[4], n22 = me[5],
      n32 = me[6], n42 = me[7], n13 = me[8], n23 = me[9], n33 = me[10], n43 =
          me[11], n14 = me[12], n24 = me[13], n34 = me[14], n44 = me[15],

      t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43
          - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44, t12 = n14 * n33
          * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43
          + n13 * n32 * n44 - n12 * n33 * n44, t13 = n13 * n24 * n42
          - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43
          - n13 * n22 * n44 + n12 * n23 * n44, t14 = n14 * n23 * n32
          - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33
          + n13 * n22 * n34 - n12 * n23 * n34;

  auto det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

  if (det == 0) {
    //TODO(throw)

//        var msg = "THREE.Matrix4.getInverse(): can't invert matrix, determinant is 0";
//
//        if ( throwOnDegenerate === true ) {
//
//          throw new Error( msg );
//
//        } else {
//
//          console.warn( msg );
//
//        }

    return this->identity();

  }

  auto detInv = 1.0 / det;

  te[0] = t11 * detInv;
  te[1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43
      + n23 * n31 * n44 - n21 * n33 * n44) * detInv;
  te[2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42
      - n22 * n31 * n44 + n21 * n32 * n44) * detInv;
  te[3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42
      + n22 * n31 * n43 - n21 * n32 * n43) * detInv;

  te[4] = t12 * detInv;
  te[5] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43
      - n13 * n31 * n44 + n11 * n33 * n44) * detInv;
  te[6] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42
      + n12 * n31 * n44 - n11 * n32 * n44) * detInv;
  te[7] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42
      - n12 * n31 * n43 + n11 * n32 * n43) * detInv;

  te[8] = t13 * detInv;
  te[9] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43
      + n13 * n21 * n44 - n11 * n23 * n44) * detInv;
  te[10] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42
      - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * detInv;
  te[11] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42
      + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * detInv;

  te[12] = t14 * detInv;
  te[13] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33
      - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * detInv;
  te[14] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32
      + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * detInv;
  te[15] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32
      - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * detInv;

  return *this;
}

Matrix4& Matrix4::decompose(Vector3* position, Quaternion* q, Vector3* scale) {
  //TODO(zxi)
  auto te = this->elements;

  auto sx = position->set(te[0], te[1], te[2]).length();
  auto sy = position->set(te[4], te[5], te[6]).length();
  auto sz = position->set(te[8], te[9], te[10]).length();

  // if determine is negative, we need to invert one scale
  auto det = this->determinant();
  if (det < 0) {

    sx = -sx;

  }

  position->x = te[12];
  position->y = te[13];
  position->z = te[14];

  // Copy
  Matrix4 matrix(*this);

  auto invSX = 1.0 / sx;
  auto invSY = 1.0 / sy;
  auto invSZ = 1.0 / sz;

  matrix.elements[0] *= invSX;
  matrix.elements[1] *= invSX;
  matrix.elements[2] *= invSX;

  matrix.elements[4] *= invSY;
  matrix.elements[5] *= invSY;
  matrix.elements[6] *= invSY;

  matrix.elements[8] *= invSZ;
  matrix.elements[9] *= invSZ;
  matrix.elements[10] *= invSZ;

  q->setFromRotationMatrix(matrix);

  scale->x = sx;
  scale->y = sy;
  scale->z = sz;

  return *this;
}

////////////////////////////////////////////////////////////
// Factory methods
////////////////////////////////////////////////////////////
Matrix4 Matrix4::makeTranslation(const Vector3& t) {
  return Matrix4().setPosition(t);
}

Matrix4 Matrix4::makePerspective(double left, double right, double top,
    double bottom, double near, double far) {

  return Matrix4().asPerspective(left, right, top, bottom, near, far);
}

Matrix4 Matrix4::makeOrthographic(double left, double right, double top,
    double bottom, double near, double far) {
  return Matrix4().asOrthographic(left, right, top, bottom, near, far);
}

Matrix4 Matrix4::makeLookAt(const Vector3& eye, const Vector3& target,
    const Vector3& up) {
  return Matrix4().asLookAt(eye, target, up);
}

std::ostream& operator<<(std::ostream& out, const Matrix4& m) {
  auto& te = m.elements;
  out << te[0] << " " << te[4] << " " << te[8] << " " << te[12] << std::endl;
  out << te[1] << " " << te[5] << " " << te[9] << " " << te[13] << std::endl;
  out << te[2] << " " << te[6] << " " << te[10] << " " << te[14] << std::endl;
  out << te[3] << " " << te[7] << " " << te[11] << " " << te[15] << std::endl;
  return out;
}

} /* namespace three */
