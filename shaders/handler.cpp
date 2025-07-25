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
