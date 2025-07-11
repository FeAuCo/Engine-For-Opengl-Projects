#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "../shaders/fragment_vertex/fragment_vertex.h"

namespace handler{
    enum class type{
        NONE = -1, VERTEX2D = 0, VERTEX3D = 1, FRAGMENT = 2
    };

    struct program{
        std::string vertex2D;
        std::string vertex3D;
        std::string fragment;
    };

    program  parse(const std::string& filePath);

    int applyBasicFVShader(const float& r, const float& g, const float& b, const float& a, const unsigned int& is2Dor3D);
}
