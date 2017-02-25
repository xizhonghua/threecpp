/*
 * glExtension.h
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#ifndef SRC_RENDERERS_GLEXTENSION_H_
#define SRC_RENDERERS_GLEXTENSION_H_

#include <GLFW/glfw3.h>

#include <three/math/Vector3.h>
#include <three/math/Euler.h>

using namespace three;

inline void glVertex3d(const Vector3& v) {
  glVertex3d(v.x, v.y, v.z);
}

inline void glVertex3d(Vector3* const v) {
  glVertex3d(*v);
}

inline void glTranslated(const Vector3& v) {
  glTranslated(v.x, v.y, v.z);
}

inline void glTranslated(Vector3* const v) {
  glTranslated(*v);
}

inline void glRotated(const Euler& rotation) {
  glRotated(rotation.x, 1, 0, 0);
  glRotated(rotation.y, 0, 1, 0);
  glRotated(rotation.z, 0, 0, 1);
}

#endif /* SRC_RENDERERS_GLEXTENSION_H_ */
