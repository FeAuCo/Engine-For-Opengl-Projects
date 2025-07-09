#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "../shaders/fragment_vertex/fragment_vertex.h"

namespace handler{
    enum class type{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    struct program{
        std::string vertex;
        std::string fragment;
    };

    program  parse(const std::string& filePath);

    int applyBasicFVShader(const float& r, const float& g, const float& b, const float& a);
}
