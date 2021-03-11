#include <GLES2/gl2.h>

#include "display.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "texture.hpp"

const int x_pos = 1308, y_pos = 468, width = 800, height = 600;

int main()
{
    init_display(x_pos, y_pos, width,height);

    glViewport(0, 0, width, height);

    // Load everything
    load_shader();
    load_mesh();
    load_texture();

    while(1)
    {
        glClearColor(0.25, 0.5, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        swap_display();
    }
}