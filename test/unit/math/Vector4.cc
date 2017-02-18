/*
 * Vector4.cc
 *
 *  Created on: Feb 8, 2017
 *      Author: zxi
 */

#include "math/Vector4.h"

#include "test/catch.hpp"

using three::Vector4;

TEST_CASE( "Vector4 constructor", "[Vector4]" ) {

  {
    Vector4 v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
    REQUIRE(v.z == 0);
    REQUIRE(v.w == 0);
  }

  {
    Vector4 v(1, 2, 3, 4);
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
    REQUIRE(v.z == 3);
    REQUIRE(v.w == 4);

    Vector4 v2(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
    REQUIRE(v2.z == 3);
    REQUIRE(v2.w == 4);

    Vector4 v3 = v;
    REQUIRE(v3.x == 1);
    REQUIRE(v3.y == 2);
    REQUIRE(v3.z == 3);
    REQUIRE(v3.w == 4);
  }
}

TEST_CASE( "Vector4 operators", "[Vector4]") {

  Vector4 v1(1, 2, 3, 4);
  Vector4 v2(2, 4, 6, 8);

  // +
  {

    Vector4 v = v1 + v2;

    REQUIRE(v.x == 3);
    REQUIRE(v.y == 6);
    REQUIRE(v.z == 9);
    REQUIRE(v.w == 12);
  }

  // +=
  {

    Vector4 v(v1);
    v += v2;

    REQUIRE(v.x == 3);
    REQUIRE(v.y == 6);
    REQUIRE(v.z == 9);
    REQUIRE(v.w == 12);
  }

  // -
  {
    Vector4 v = v1 - v2;

    REQUIRE(v.x == -1);
    REQUIRE(v.y == -2);
    REQUIRE(v.z == -3);
    REQUIRE(v.w == -4);
  }

  // -=
  {
    Vector4 v(v1);
    v -= v2;

    REQUIRE(v.x == -1);
    REQUIRE(v.y == -2);
    REQUIRE(v.z == -3);
    REQUIRE(v.w == -4);
  }

  // *, dot product
  REQUIRE(v1 * v2 == 2 + 8 + 18 + 32);

  // ^ component-wise multiplication
  {
    Vector4 v = v1 ^ v2;
    REQUIRE(v == Vector4(2, 8, 18, 32));
  }

  // ^=
  {
    Vector4 v(v1);
    v ^= v2;
    REQUIRE(v == Vector4(2, 8, 18, 32));
  }
}
