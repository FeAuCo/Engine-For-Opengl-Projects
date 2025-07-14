#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "../shaders/fragment_vertex/fragment_vertex.h"

namespace handler{
    std::string parse(const std::string& filePath);

    int applyBasicFVShader(const float& r, const float& g, const float& b, const float& a);
}
