/*
 * Vector3.cc
 *
 *  Created on: Feb 8, 2017
 *      Author: zxi
 */

#include "math/Vector3.h"

#include "test/catch.hpp"

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

    Vector3 v = v1 + v2;

    REQUIRE(v.x == 3);
    REQUIRE(v.y == 6);
    REQUIRE(v.z == 9);
  }

  // +=
  {

    Vector3 v(v1);
    v += v2;

    REQUIRE(v.x == 3);
    REQUIRE(v.y == 6);
    REQUIRE(v.z == 9);
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

}
