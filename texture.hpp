#ifndef TEXTURE_H
#define TEXTURE_H

// Dependencies
#include <GLES2/gl2.h>
#include <stdio.h.>

#define STB_IMAGE_IMPLEMENTATION
#include "./include/stb_image.h"

#include "shader.hpp"

// Data
const char res_path[] = "./res/wooden_box.png";
GLuint texture_id;

// Function
void texture_post_procedure()
{
   glActiveTexture(GL_TEXTURE0);
   glUniform1i(sampler_loc, 0);
}

void load_texture()
{
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int tex_width, tex_height, n;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(res_path, &tex_width, &tex_height, &n, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
    }
    else
    {
        fprintf(stderr, "Failed to load texture");
    }

    texture_post_procedure();
}

#endif /* TEXTURE_H */