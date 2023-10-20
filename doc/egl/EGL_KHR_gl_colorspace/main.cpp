
#ifndef EGL_KHR_gl_colorspace
#define EGL_KHR_gl_colorspace 1
#define EGL_GL_COLORSPACE_KHR             0x309D
#define EGL_GL_COLORSPACE_SRGB_KHR        0x3089
#define EGL_GL_COLORSPACE_LINEAR_KHR      0x308A
#endif /* EGL_KHR_gl_colorspace */

/**
 * @brief EGL_KHR_gl_colorspace
 * 
 * This extension allows creating EGLSurfaces which will be rendered to in sRGB by OpenGL contexts supporting that capability.
 * 创建sRGB format的default FBO.
 * 
 * @note
 * Only OpenGL and OpenGL ES contexts which support sRGB rendering must respect requests for EGL_GL_COLORSPACE_SRGB_KHR, and only to sRGB formats 
 * supported by the context (normally just SRGB8).
 * 
 * 
*/

void Samples()
{
    EGLint attrs[] = 
    {
        EGL_GL_COLORSPACE_KHR, EGL_GL_COLORSPACE_SRGB_KHR,
        EGL_NONE,
    };

    EGLSurface windowSurface = eglCreateWindowSurface (display, config, hwind, attrs);
    // EGLSurface pbuffer       = eglCreatePbufferSurface(display, config, attrs);
    // EGLSurface pixmapSurface = eglCreatePixmapSurface (display, config, hpixmap, attrs);
}