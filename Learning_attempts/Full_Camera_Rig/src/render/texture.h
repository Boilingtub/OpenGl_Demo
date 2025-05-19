#ifndef TEXTURE_H
#define TEXTURE_H

#include "../glad/glad.h"
#include "stb_image.h"
#include<iostream>

class Texture {
    public:
    unsigned int texture; 
    Texture(const char* tex_path) {
        glGenTextures(1 , &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        //set texture wraping/filtering oprions (on currently bound texture)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture 
        stbi_set_flip_vertically_on_load(true);
        int width, height, nrChannels;
        unsigned char* data = stbi_load(tex_path,&width, &height, &nrChannels,
                                        STBI_rgb_alpha);
        
        if(data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
                         GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
           printf("Failed to load texture\n");  
        }
        stbi_image_free(data); 
    };
    
    ~Texture() {
    
    }
};

#endif
