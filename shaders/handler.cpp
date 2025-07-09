#include "handler.h"

handler::program handler::parse(const std::string& filePath){
    std::ifstream stream(filePath, std::ios::binary);
    if (!stream.is_open()) {
        
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::string line;
    std::stringstream ss[2];

    handler::type type = handler::type::NONE;

    while (getline(stream, line)){
        if (line.find("#shader") != std::string::npos){

            if (line.find(":vertex") != std::string::npos){
                type = handler::type::VERTEX;
            }

            else if (line.find(":fragment") != std::string::npos){
                type = handler::type::FRAGMENT;
            }
        }

        else {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

int handler::applyBasicFVShader(const float& r, const float& g, const float& b, const float& a){
    handler::program program = handler::parse("../shaders/fragment_vertex/fragment_vertex.shader");
    unsigned int shader = fv_shader::createShader(program.vertex, program.fragment);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, r, g, b, a);

    return shader;
}
