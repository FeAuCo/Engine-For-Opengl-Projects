#include "handler.h"

std::string handler::parse(const std::string& filePath){
    std::ifstream stream(filePath, std::ios::binary);
    
    if (!stream.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << stream.rdbuf(); 
    return buffer.str(); 
}

int handler::applyBasicFVShader(const float& r, const float& g, const float& b, const float& a){
    std::string sourceVertex = handler::parse("../shaders/fragment_vertex/vertex.shader");
    std::string sourceFragment = handler::parse("../shaders/fragment_vertex/fragment.shader");

    unsigned int shader = fv_shader::createShader(sourceVertex.c_str(), sourceFragment.c_str());

    glUseProgram(shader);
    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, r, g, b, a);

    return shader;
}
