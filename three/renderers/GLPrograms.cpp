/*
 * GLPrograms.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: zxi
 */

#include <three/renderers/GLPrograms.h>

#include <algorithm>

namespace three {

GLPrograms::GLPrograms() {
  // TODO Auto-generated constructor stub

}

GLPrograms::~GLPrograms() {
  // TODO Auto-generated destructor stub
}

std::string getProgramCode(Material* material,
    std::map<std::string, std::string> parameters) {
  //TODO(zxi)
  return "haha";
}

GLProgram* GLPrograms::acquireProgram(Material* material,
    const GLParamtersType& parameters, std::string code) {
  GLProgram* program = nullptr;

  for (auto p : programs_) {
    if (p->code() == code) {
      ++(p->usedTimes);
      program = p;
      break;
    }
  }

  if (program == nullptr) {
    program = new GLProgram(code, material, parameters);
    this->programs_.push_back(program);
  }

  return program;
}

void GLPrograms::releaseProgram(GLProgram* program) {
  if (--program->usedTimes == 0) {
    auto it = std::find(programs_.begin(), programs_.end(), program);

    std::swap(programs_.back(), *it);

    programs_.pop_back();

    // Free GL resource
    delete program;
  }
}

} /* namespace three */
