#pragma once

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <iostream>
#include <vector>

namespace texture{
    class Texture{
        private:
            unsigned int ID;
            int width, height, nrChannels;
            unsigned char* imageData;
            GLenum type;

        public:
            unsigned int getID();

            int getWidth();

            int getHeight();

            unsigned char* getImageData();

            Texture();

            Texture(const char* texturePath);

            void generate(const GLenum& type);

            void bind();

            void attach(const std::vector<std::string>& faces);
    };

    GLenum setType(const int& nrChannels);
}
