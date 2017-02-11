/*
 * Vector2.cc
 *
 *  Created on: Feb 8, 2017
 *      Author: zxi
 */

#include "math/Vector2.h"

#include "test/catch.hpp"

using three::Vector2;


TEST_CASE( "Vector2 constructor", "[Vector2]" ) {

  {
    Vector2 v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
  }

  {
    Vector2 v(1, 2);
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);

    Vector2 v2(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
  }
}

TEST_CASE( "Vector2 operators", "[Vector2]") {

  Vector2 v1(1, 2);
  Vector2 v2(2, 4);

  // +
  {

    Vector2 v = v1 + v2;

    REQUIRE(v.x == 3);
    REQUIRE(v.y == 6);
  }

  // +=
  {

    Vector2 v(v1);
    v += v2;

    REQUIRE(v.x == 3);
    REQUIRE(v.y == 6);
  }

  // -
  {
    Vector2 v = v1 - v2;

    REQUIRE(v.x == -1);
    REQUIRE(v.y == -2);
  }

  // -=
  {
    Vector2 v(v1);
    v -= v2;

    REQUIRE(v.x == -1);
    REQUIRE(v.y == -2);
  }

  // *, dot product
  REQUIRE(v1 * v2 == 2 + 8);

}
