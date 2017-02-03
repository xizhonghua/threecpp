/*
 * Face3.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#include "core/Face3.h"

namespace three {

Face3::Face3(int a, int b, int c) :
    Face3(a, b, c, Vector3 { 0, 0, 0 }) {

}

Face3::Face3(int a, int b, int c, const Vector3& normal) :
    a(a), b(b), c(c), normal(normal) {
}

Face3::~Face3() {
  // TODO Auto-generated destructor stub
}

} /* namespace three */
