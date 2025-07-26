#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "fragment_vertex/fragment_vertex.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace handler{
    class Shader{
        public: 
            unsigned int ID;

            void setBool(const std::string& name, bool value);

            void setInt(const std::string& name, int value);

            void setFloat(const std::string& name, float value);

            void setVec2(const std::string& name, const glm::vec2& value);
 
            void setVec2(const std::string& name, float x, float y);
 
            void setVec3(const std::string& name, const glm::vec3& value);
 
            void setVec3(const std::string& name, float x, float y, float z);
 
            void setVec4(const std::string& name, const glm::vec4& value);
 
            void setVec4(const std::string& name, float x, float y, float z, float w);
 
            void setMat2(const std::string& name, const glm::mat2& mat);
 
            void setMat3(const std::string& name, const glm::mat3& mat);
 
            void setMat4(const std::string& name, const glm::mat4& mat);

            void use();
    };

    std::string parse(const std::string& filePath);
}
