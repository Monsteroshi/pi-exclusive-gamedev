#include <GLES2/gl2.h>

#include "display.h"

const int width = 800, height = 600;

int main()
{
    init_display(width,height);

    glViewport(0, 0, width, height);

    while(1)
    {
        glClearColor(0.25, 0.5, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        swap_display();
    }
}