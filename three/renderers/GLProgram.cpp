/*
 * GLProgram.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: zxi
 */

#include <three/renderers/GLProgram.h>

#include <GL/glu.h>

#include <sstream>

namespace three {

uint32_t GLProgram::programIdCount = 0;

std::string GLProgram::getVertexPrefix(const GLParamtersType& paramters) {
  std::stringstream ss;

  ss <<
      "uniform mat4 modelMatrix;" << std::endl <<
      "uniform mat4 modelViewMatrix;" << std::endl <<
      "uniform mat4 projectionMatrix;" << std::endl <<
      "uniform mat4 viewMatrix;" << std::endl <<
      "uniform mat3 normalMatrix;" << std::endl <<
      "uniform vec3 cameraPosition;" << std::endl <<

      "attribute vec3 position;" << std::endl <<
      "attribute vec3 normal;" << std::endl <<
      "attribute vec2 uv;" << std::endl <<
      "attribute vec2 uv2;" << std::endl <<

      "#ifdef USE_COLOR" << std::endl <<

      "attribute vec3 color;" << std::endl <<

      "#endif" << std::endl;

  return ss.str();
}

std::string GLProgram::getFragmentPrefix(const GLParamtersType& paramters) {
  std::stringstream ss;

  ss << "uniform mat4 viewMatrix;" << std::endl <<
        "uniform vec3 cameraPosition;" << std::endl;

  return ss.str();
}

GLProgram::GLProgram(const std::string& code, Material* material,
    const GLParamtersType& parameters) {

  this->id_ = programIdCount++;
  this->code_ = code;
  this->program_ = glCreateProgram();

  std::string vertexGLSL = this->getVertexPrefix(parameters) + material->vertexGLSL;
  std::string fragmentGLSL = this->getFragmentPrefix(parameters) + material->fragmentGLSL;

  glVertexShader.reset(new GLShader(ShaderType::VertexShader, vertexGLSL));
  glFragmentShader.reset(new GLShader(ShaderType::FragmentShader, fragmentGLSL));

  glAttachShader(this->program_, glVertexShader->id());
  glAttachShader(this->program_, glFragmentShader->id());

  glLinkProgram(this->program_);

//  glGetProgramInfoLog()

//TODO(zxi) check shaders

  glDeleteShader(glVertexShader->id());
  glDeleteShader(glFragmentShader->id());

}

GLProgram::~GLProgram() {
  glDeleteProgram(this->program_);
  this->program_ = 0;
}

} /* namespace three */
