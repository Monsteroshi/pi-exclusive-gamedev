#ifndef SHADER_H
#define SHADER_H

// Dependencies
#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>

// Data
const char vertex_src[] = 
    "attribute vec3 v_pos                                            \n"
    "attribute vec2 uv_coord                                         \n"
    "                                                                \n"
    "varying vec2 v_tex_coord                                        \n"
    "                                                                \n"
    "uniform mat4 model                                              \n"
    "uniform mat4 view                                               \n"
    "uniform mat4 projection                                         \n"
    "                                                                \n"
    "void main() {                                                   \n"
    "// gl_Position = projection * view * model * vec4(v_pos, 1.0f); \n"
    "   gl_Position = vec4(v_pos, 1.0f);                             \n"
    "   v_tex_coord = uv_coord;                                      \n"
    "}                                                               \n";

const char fragment_src[] = 
    "precision mediump float;                                        \n"
    "                                                                \n"
    "varying vec2 v_tex_coord                                        \n"
    "uniform sampler2D s_texture;                                    \n"
    "                                                                \n"
    "void main() {                                                   \n"
    "  gl_FragColor = texture2D(s_texture, v_tex_coord);             \n"
    "}                                                               \n";

GLuint shader_program;
GLint position_loc, uv_loc;
GLint model_loc, view_loc, projection_loc, sampler_loc;

// Function
void shader_post_procedure()
{
    // Variable definition in mesh.hpp and others
    position_loc   = glGetAttribLocation(shader_program, "v_pos");
    uv_loc         = glGetAttribLocation(shader_program, "uv_coord");

    model_loc      = glGetUniformLocation(shader_program, "model");
    view_loc       = glGetUniformLocation(shader_program, "view");
    projection_loc = glGetUniformLocation(shader_program, "projection");
    sampler_loc    = glGetUniformLocation(shader_program, "s_texture"); 

    glUseProgram(shader_program);
}

GLuint compile_shader(GLenum type, const char source[])
{
    GLuint shader;
    shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled)   
    {
	    GLint info_len = 0;
	    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

	    if(info_len > 1)    
        {
		    char* err_log = malloc(sizeof(char) * info_len);

		    glGetShaderInfoLog(shader, info_len, NULL, err_log);
		    fprintf(stderr, "Error compiling shader:\n%s\n", err_log);

		    free(err_log);
		}

	    glDeleteShader(shader);
	    return 0;
	}
    return shader;
}

void load_shader()
{
    GLuint vertex_shader;
    vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_src);

    GLuint fragment_shader;
    fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_src);

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    GLint linked;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &linked);
    if(!linked) 
    {
        GLint info_len = 0;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_len);

        if(info_len > 1) 
        {
            char* err_log = malloc(sizeof(char) * info_len);

            glGetProgramInfoLog(shader_program, info_len, NULL, err_log);
            fprintf(stderr, "Error linking shader program:\n%s\n", err_log);            
            
            free(err_log);
        }
        glDeleteProgram(shader_program);
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    shader_post_procedure();
}

#endif /* SHADER_H */