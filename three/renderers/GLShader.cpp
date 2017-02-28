/*
 * Shader.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: zxi
 */

#include <three/renderers/GLShader.h>

#include <GL/glu.h>

#include <iostream>

namespace three {

GLShader::GLShader(ShaderType type, const std::string& source) :
    id_(0), type_(type), source_(source) {

  id_ = glCreateShader(
      type == ShaderType::VertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

  const char* src = source_.c_str();

  glShaderSource(id_, 1, &src, nullptr);

  glCompileShader(id_);

  int status;

  glGetShaderiv(id_, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    std::cerr << "Shader can't compile." << std::endl;
  }
}

}
/* namespace three */
