/*
 * Face3.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#include "core/Face3.h"

namespace three {

Face3::Face3(const Vector3& a, const Vector3& b, const Vector3& c) :
    Face3(a, b, c, Vector3 { 0, 0, 0 }) {

}

Face3::~Face3() {
  // TODO Auto-generated destructor stub
}

} /* namespace three */
