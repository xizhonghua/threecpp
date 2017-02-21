/*
 * Vector3.cc
 *
 *  Created on: Feb 8, 2017
 *      Author: zxi
 */

#include <three/math/Vector3.h>

#include <test/catch.hpp>

using three::Vector3;

TEST_CASE( "Vector3 constructor", "[Vector3]" ) {

  {
    Vector3 v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
    REQUIRE(v.z == 0);
  }

  {
    Vector3 v(1, 2, 3);
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
    REQUIRE(v.z == 3);

    Vector3 v2(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
    REQUIRE(v2.z == 3);
  }
}

TEST_CASE( "Vector3 operators", "[Vector3]") {

  Vector3 v1(1, 2, 3);
  Vector3 v2(2, 4, 6);

  // +
  {
    REQUIRE(v1 + v2 == Vector3(3, 6, 9));
  }

  // +=
  {

    Vector3 v(v1);
    v += v2;

    REQUIRE(v == Vector3(3, 6, 9));
  }

  // -
  {
    Vector3 v = v1 - v2;

    REQUIRE(v.x == -1);
    REQUIRE(v.y == -2);
    REQUIRE(v.z == -3);
  }

  // -=
  {
    Vector3 v(v1);
    v -= v2;

    REQUIRE(v.x == -1);
    REQUIRE(v.y == -2);
    REQUIRE(v.z == -3);
  }

  // *, dot product
  REQUIRE(v1 * v2 == 2 + 8 + 18);

  // *= Scalar
  {
    Vector3 v(v1);
    v *= 2;
    REQUIRE(v.x == 2);
    REQUIRE(v.y == 4);
    REQUIRE(v.z == 6);
  }

  // *= Scalar
  {
    REQUIRE((Vector3(v1) *= 2) == Vector3(2, 4, 6));
  }

  // / Scalar
  {
    REQUIRE(v2 / 2 == v1);
    REQUIRE((Vector3(v2) /= 2) == v1);
  }

}
