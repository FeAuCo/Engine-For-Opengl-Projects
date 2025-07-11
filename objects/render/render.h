#pragma once

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

namespace rendering{
    class Obj{
        private:
            unsigned int vbo, ibo = 0, vao;
            int componentsPerVertex;
            std::vector<float> vertices;
            std::vector<unsigned int> indices;

        public:
            unsigned int getVBO() const;

            unsigned int getIBO() const;

            unsigned int getVAO() const;

            int getComponentsPerVertex() const;

            std::vector<float> getVertices() const;

            std::vector<unsigned int> getIndices() const;

            void setBuffersForRendering(const std::vector<float>& vertices, const std::vector<unsigned int>& indices = {});

            void setVertexAttributes(const int& componentsPerVertex, const int& shaderIndex, const bool& normalize = GL_FALSE);

            
            void clearObjBuffers();

            void render();
    };
}
