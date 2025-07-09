#pragma once

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

namespace rendering{
    class Obj{
        private:
            unsigned int vbo, ibo = 0, vao;
            int componentsPerVertex;
            std::vector<double> vertices;
            std::vector<unsigned int> indices;

        public:
            unsigned int getVBO() const;

            unsigned int getIBO() const;

            unsigned int getVAO() const;

            int getComponentsPerVertex() const;

            std::vector<double> getVertices() const;

            std::vector<unsigned int> getIndices() const;

            void setBuffersForRendering(const std::vector<double>& vertices, const std::vector<unsigned int>& indices = {});

            void setVertexAttributes(const int& componentsPerVertex, const int& shaderIndex, const bool& normalize = GL_FALSE);

            
            void clearObjBuffers();

            void render();
    };
}
