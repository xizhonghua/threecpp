/*
 * glExtension.h
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#ifndef SRC_RENDERERS_GLEXTENSION_H_
#define SRC_RENDERERS_GLEXTENSION_H_

#include <GLFW/glfw3.h>

#include <math/Vector3.h>

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

#endif /* SRC_RENDERERS_GLEXTENSION_H_ */
