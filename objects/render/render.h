#pragma once

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <iostream>
#include "../../useful/math/quaternions/quaternion.h"

namespace rendering{
    class Obj{
        private:
            unsigned int vbo, ibo = 0, vao;
            int componentsPerPos, componentsPerColor, componentsPerTexture, verticesRepetion, verticesAmount;
            std::vector<float> vertices;
            std::vector<unsigned int> indices;

        public:
            unsigned int getVBO() const;

            unsigned int getVAO() const;
            
            unsigned int getIBO() const;

            unsigned int getVerticesAmount() const;

            std::vector<float> getVertices() const;

            std::vector<unsigned int> getIndices() const;

            void setBuffersForRendering(const GLenum& type, const std::vector<float>& vertices, const std::vector<unsigned int>& indices = {});

            void setVertexAttributes(const int& componentsPerPos, const int& shaderIndexPos = 0, const int& componentsPerColor = 0, const int& shaderIndexColor = 1,
                                                    const int& componentsPerTexture = 0, const int& shaderIndexTexture = 2, const bool& normalize = GL_FALSE, const int& verticesRepetion = 1);
            
            void clearObjBuffers();

            void render();

            void updateVertices(const std::vector<float>& newVertices);

            void rotateVertices3D(const quaternions::Quaternion& q);
    };
}
