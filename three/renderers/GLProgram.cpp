/*
 * GLProgram.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: zxi
 */

#include <three/renderers/GLProgram.h>

#include <GL/glu.h>

namespace three {

uint32_t GLProgram::programIdCount = 0;

GLProgram::GLProgram(const std::string& code, Material* material,
    const GLParamtersType& parameters) {

  this->id_ = programIdCount++;
  this->code_ = code;
  this->program_ = glCreateProgram();

}

GLProgram::~GLProgram() {
//TODO(zxi) release resources...
}

} /* namespace three */
