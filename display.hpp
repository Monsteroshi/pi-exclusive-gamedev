#ifndef DISPLAY_H
#define DISPLAY_H

// Dependencies
#include <bcm_host.h>
#include <EGL/egl.h>

// Data
EGL_DISPMANX_WINDOW_T       native_window;

DISPMANX_ELEMENT_HANDLE_T   dispmanx_element;
DISPMANX_DISPLAY_HANDLE_T   dispmanx_display;
DISPMANX_UPDATE_HANDLE_T    dispmanx_update;
VC_RECT_T                   dst_rect;
VC_RECT_T                   src_rect;

EGLDisplay                  display;
EGLSurface                  surface;
EGLContext                  context;
EGLint                      num_config;
EGLConfig                   config;

const EGLint config_attrib[] = {
    EGL_RED_SIZE,       8,
    EGL_GREEN_SIZE,     8,
    EGL_BLUE_SIZE,      8,
    EGL_ALPHA_SIZE,     8,
    EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
    EGL_NONE
};

const EGLint context_attrib[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

// Function
void init_display(int x_pos, int y_pos, int width, int height)
{
    bcm_host_init();

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    
    eglInitialize(display, NULL, NULL);

    eglChooseConfig(display, config_attrib, &config, 1, &num_config);

    eglBindAPI(EGL_OPENGL_ES_API);

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attrib);

    dst_rect.x      = x_pos;
    dst_rect.y      = y_pos;
    dst_rect.width  = width;
    dst_rect.height = height;
    src_rect.x      = 0;
    src_rect.y      = 0;
    src_rect.width  = width << 16;
    src_rect.height = height << 16;

    dispmanx_display = vc_dispmanx_display_open(0);

    dispmanx_update  = vc_dispmanx_update_start(0);

    dispmanx_element = vc_dispmanx_element_add(
        dispmanx_update, dispmanx_display,
        0, &dst_rect, 0, &src_rect, 
        DISPMANX_PROTECTION_NONE,
        0, 0, 0
    );

    native_window.element = dispmanx_element;
    native_window.width   = width;
    native_window.height  = height;
    vc_dispmanx_update_submit_sync(dispmanx_update);

    surface = eglCreateWindowSurface(display, config, &native_window, NULL);

    eglMakeCurrent(display, surface, surface, context);
}

void swap_display() 
{
    eglSwapBuffers(display, surface);
}

#endif /* DISPLAY_H */