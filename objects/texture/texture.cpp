#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"

unsigned int texture::Texture::getID(){
    return this->ID;
}

int texture::Texture::getWidth(){
    return this->width;
}

int texture::Texture::getHeight(){
    return this->height;
}

unsigned char* texture::Texture::getImageData(){
    return this->imageData;
}

texture::Texture::Texture(){};

texture::Texture::Texture(const char* texturePath){
    this->imageData = stbi_load(texturePath, &(this->width), &(this->height), &(this->nrChannels), 0);
}

void texture::Texture::generate(const GLenum& type){
    this->type = type;

    glGenTextures(1, &(this->ID));
}

void texture::Texture::bind(){
    glBindTexture(type, this->ID);
}

void texture::Texture::attach(const std::vector<std::string>& faces){
    if (type == GL_TEXTURE_2D){
        if (this->imageData){
            glTexImage2D(GL_TEXTURE_2D, 0, texture::setType(this->nrChannels), this->width, this->height, 0, texture::setType(this->nrChannels), GL_UNSIGNED_BYTE, this->imageData);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(this->imageData);
        }

        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }   
    }

    else if (type == GL_TEXTURE_CUBE_MAP){
        int width, height, nrChannels;

        for (unsigned int i = 0; i < faces.size(); i++){
            unsigned char* faceData = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            
            if (faceData){
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, texture::setType(nrChannels), width, height, 0, texture::setType(nrChannels), GL_UNSIGNED_BYTE, faceData);
                stbi_image_free(faceData);
            }

            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(faceData);
            }
        }

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
}

GLenum texture::setType(const int& nrChannels){
    switch (nrChannels) {
        case 1:
            return GL_RED;
        case 2:
            return GL_RG;

        case 3:
            return GL_RGB;

        case 4:
            return GL_RGBA;
        
        default:
            throw std::invalid_argument("Received invalid value");
    }
}
