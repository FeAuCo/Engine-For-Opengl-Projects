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

unsigned int rendering::Obj::getVerticesAmount() const{
    return this->verticesAmount;
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

void rendering::Obj::setVertexAttributes(const int& componentsPerPos, const int& shaderIndexPos, const int& componentsPerColor, const int& shaderIndexColor,
                                                    const int& componentsPerTexture, const int& shaderIndexTexture, const bool& normalize, const int& verticesRepetion){
    this->verticesRepetion = verticesRepetion;

    this->componentsPerPos = componentsPerPos;
    this->componentsPerColor = componentsPerColor;
    this->componentsPerTexture = componentsPerTexture;

    int offsetPos = (this->componentsPerPos) * sizeof(float);
    int offsetColor = (this->componentsPerColor) * sizeof(float);
    int offsetTexture = (this->componentsPerTexture) * sizeof(float);

    this->verticesAmount = (this->vertices).size() / (this->componentsPerPos + this->componentsPerColor + this->componentsPerTexture) / (this->verticesRepetion);

    glVertexAttribPointer(shaderIndexPos, this->componentsPerPos, GL_FLOAT, normalize, offsetPos + offsetColor + offsetTexture,  0);
    glEnableVertexAttribArray(shaderIndexPos);

    if (this->componentsPerColor != 0){
        glVertexAttribPointer(shaderIndexColor, this->componentsPerColor, GL_FLOAT, normalize, offsetPos + offsetColor + offsetTexture, reinterpret_cast<void*>(static_cast<uintptr_t>(offsetPos)));
        glEnableVertexAttribArray(shaderIndexColor);
    }
    
    if (this->componentsPerTexture != 0){
        glVertexAttribPointer(shaderIndexTexture, this->componentsPerTexture, GL_FLOAT, normalize, offsetPos + offsetColor + offsetTexture, reinterpret_cast<void*>(static_cast<uintptr_t>(offsetPos + offsetColor)));
        glEnableVertexAttribArray(shaderIndexTexture);
    }
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
        glDrawArrays(GL_TRIANGLES, 0, this->verticesAmount);
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
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
}

void rendering::Obj::rotateVertices3D(const quaternions::Quaternion& q){
    int stride = (this->componentsPerPos) + (this->componentsPerColor) + (this->componentsPerTexture);

    std::vector<float> newVertices = this->vertices;
    quaternions::Quaternion h;
    
    for (int i = 0; i < vertices.size(); i += stride){
        h = quaternions::createH(vertices[i], vertices[i + 1], vertices[i + 2]);
        quaternions::Quaternion rotated = quaternions::rotate(q, h);

        newVertices[i] = rotated[1];
        newVertices[i + 1] = rotated[2];
        newVertices[i + 2] = rotated[3];
    }
    
    this->updateVertices(newVertices);
}
