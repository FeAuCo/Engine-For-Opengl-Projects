#include "fragment_vertex.h"

unsigned int fv_shader::compileShader(unsigned int type, const char* source){
    unsigned int id = glCreateShader(type);  
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (!result){
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader" << std::endl; 
    
        glDeleteShader(id);
        
        return 0;
    }

    return id;
}

unsigned int fv_shader::createShader(const char* vertexShader, const char* fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
