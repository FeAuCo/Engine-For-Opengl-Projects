#pragma once

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>

namespace fv_shader{
    unsigned int compileShader(unsigned int type, const std::string& source);

    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
}