#include "handler.h"

void handler::Shader::setBool(const std::string& name, bool value){         
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value); 
}

void handler::Shader::setInt(const std::string& name, int value){
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void handler::Shader::setFloat(const std::string& name, float value){
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void handler::Shader::setVec2(const std::string &name, const glm::vec2 &value){ 
    glUniform2fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]); 
}

void handler::Shader::setVec2(const std::string& name, float x, float y){ 
    glUniform2f(glGetUniformLocation(this->ID, name.c_str()), x, y); 
}

void handler::Shader::setVec3(const std::string& name, const glm::vec3 &value){ 
    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]); 
}

void handler::Shader::setVec3(const std::string& name, float x, float y, float z){ 
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z); 
}

void handler::Shader::setVec4(const std::string& name, const glm::vec4 &value){ 
    glUniform4fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]); 
}

void handler::Shader::setVec4(const std::string& name, float x, float y, float z, float w){ 
    glUniform4f(glGetUniformLocation(this->ID, name.c_str()), x, y, z, w); 
}

void handler::Shader::setMat2(const std::string& name, const glm::mat2& mat){
    glUniformMatrix2fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void handler::Shader::setMat3(const std::string& name, const glm::mat3& mat) {
    glUniformMatrix3fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void handler::Shader::setMat4(const std::string& name, const glm::mat4& mat){
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void handler::Shader::use(){
    glUseProgram(this->ID);
}

std::string handler::parse(const std::string& filePath){
    std::ifstream stream(filePath, std::ios::binary);
    
    if (!stream.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << stream.rdbuf(); 
    return buffer.str(); 
}
