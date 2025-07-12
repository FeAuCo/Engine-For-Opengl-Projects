#include "render.h"

unsigned int rendering::Obj::getVBO() const{
    return this->vbo;
}

unsigned int rendering::Obj::getVAO() const{
    return this->vao;
}
   
unsigned int rendering::Obj::getIBO() const{
    return this->ibo;
}

int rendering::Obj::getComponentsPerVertex() const{
    return this->componentsPerVertex;
}

std::vector<float> rendering::Obj::getVertices() const{
    return this->vertices;
}

std::vector<unsigned int> rendering::Obj::getIndices() const{
    return this->indices;
}

void rendering::Obj::setBuffersForRendering(const GLenum& type, const std::vector<float>& vertices, const std::vector<unsigned int>& indices){
    this->vertices = vertices;

    glGenVertexArrays(1, &(this->vao));
    glBindVertexArray(this->vao);

    glGenBuffers(1, &(this->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), type);
    
    if (!indices.empty()){
        this->indices = indices;

        glGenBuffers(1, &(this->ibo));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), type);
    }
}

void rendering::Obj::setVertexAttributes(const int& componentsPerVertex, const int& shaderIndex, const bool& normalize){
    this->componentsPerVertex = componentsPerVertex;
    glVertexAttribPointer(shaderIndex, this->componentsPerVertex, GL_FLOAT, normalize, (this->componentsPerVertex) * sizeof(float),  0);
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

void rendering::Obj::updateVertices(const std::vector<float>& newVertices){
    if (newVertices.size() != (this->vertices).size()) {
        std::cerr << "Error: New vertices size doesn't match original size\n";
        return;
    }

    this->vertices = newVertices;

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    void* buffer = glMapBufferRange(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), GL_MAP_WRITE_BIT);

    if (buffer) {
        memcpy(buffer, vertices.data(), vertices.size() * sizeof(float));
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
}

void rendering::Obj::rotateVertices3D(const quaternions::Quaternion& q){
    std::vector<float> newVertices;
    std::vector<float> vertex;

    quaternions::Quaternion h;
    
    for (float vertexComponent : this->vertices){
        vertex.emplace_back(vertexComponent);

        if (vertex.size() == 3){
            h = quaternions::createH(vertex[0], vertex[1], vertex[2]);
            quaternions::Quaternion rotated = quaternions::rotate(q, h);

            newVertices.emplace_back(rotated[1]);
            newVertices.emplace_back(rotated[2]);
            newVertices.emplace_back(rotated[3]);

            vertex.clear();
        }

    }

    this->updateVertices(newVertices);
}
