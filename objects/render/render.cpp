#include "render.h"

unsigned int rendering::Obj::getVBO() const{
    return this->vbo;
}

unsigned int rendering::Obj::getIBO() const{
    return this->ibo;
}

unsigned int rendering::Obj::getVAO() const{
    return this->vao;
}

int rendering::Obj::getComponentsPerVertex() const{
    return this->componentsPerVertex;
}

std::vector<double> rendering::Obj::getVertices() const{
    return this->vertices;
}

std::vector<unsigned int> rendering::Obj::getIndices() const{
    return this->indices;
}

void rendering::Obj::setBuffersForRendering(const std::vector<double>& vertices, const std::vector<unsigned int>& indices){
    this->vertices = vertices;

    glGenVertexArrays(1, &(this->vao));
    glBindVertexArray(this->vao);

    glGenBuffers(1, &(this->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_STATIC_DRAW);
    
    if (!indices.empty()){
        this->indices = indices;

        glGenBuffers(1, &(this->ibo));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }
}

void rendering::Obj::setVertexAttributes(const int& componentsPerVertex, const int& shaderIndex, const bool& normalize){
    this->componentsPerVertex = componentsPerVertex;
    glVertexAttribPointer(shaderIndex, this->componentsPerVertex, GL_DOUBLE, normalize, (this->componentsPerVertex) * sizeof(double),  0);
    glEnableVertexAttribArray(0);
}

void rendering::Obj::clearObjBuffers(){
    glDeleteVertexArrays(1, &(this->vao));
    glDeleteBuffers(1, &(this->vbo));
    
    this->vao = 0;
    this->vbo = 0;

    if (this->ibo != 0){
        glDeleteBuffers(1, &(this->ibo));
        this->ibo = 0;
    }
}

void rendering::Obj::render(){
    glBindVertexArray(this->vao);

    if (this->ibo == 0){
        glDrawArrays(GL_TRIANGLES, 0, (this->vertices).size() / (this->componentsPerVertex));
    }

    else {
        glDrawElements(GL_TRIANGLES, (this->indices).size(), GL_UNSIGNED_INT, nullptr);
    }
}
