#ifndef EGL_EXT_gl_colorspace_bt2020_hlg
#define EGL_EXT_gl_colorspace_bt2020_hlg 1
#define EGL_GL_COLORSPACE_BT2020_HLG_EXT  0x3540
#endif /* EGL_EXT_gl_colorspace_bt2020_hlg */

#ifndef EGL_EXT_gl_colorspace_bt2020_linear
#define EGL_EXT_gl_colorspace_bt2020_linear 1
#define EGL_GL_COLORSPACE_BT2020_LINEAR_EXT 0x333F
#endif /* EGL_EXT_gl_colorspace_bt2020_linear */

#ifndef EGL_EXT_gl_colorspace_bt2020_pq
#define EGL_EXT_gl_colorspace_bt2020_pq 1
#define EGL_GL_COLORSPACE_BT2020_PQ_EXT   0x3340
#endif /* EGL_EXT_gl_colorspace_bt2020_pq */

#ifndef EGL_EXT_gl_colorspace_display_p3
#define EGL_EXT_gl_colorspace_display_p3 1
#define EGL_GL_COLORSPACE_DISPLAY_P3_EXT  0x3363
#endif /* EGL_EXT_gl_colorspace_display_p3 */

#ifndef EGL_EXT_gl_colorspace_display_p3_linear
#define EGL_EXT_gl_colorspace_display_p3_linear 1
#define EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT 0x3362
#endif /* EGL_EXT_gl_colorspace_display_p3_linear */

#ifndef EGL_EXT_gl_colorspace_display_p3_passthrough
#define EGL_EXT_gl_colorspace_display_p3_passthrough 1
#define EGL_GL_COLORSPACE_DISPLAY_P3_PASSTHROUGH_EXT 0x3490
#endif /* EGL_EXT_gl_colorspace_display_p3_passthrough */

#ifndef EGL_EXT_gl_colorspace_scrgb
#define EGL_EXT_gl_colorspace_scrgb 1
#define EGL_GL_COLORSPACE_SCRGB_EXT       0x3351
#endif /* EGL_EXT_gl_colorspace_scrgb */

#ifndef EGL_EXT_gl_colorspace_scrgb_linear
#define EGL_EXT_gl_colorspace_scrgb_linear 1
#define EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT 0x3350
#endif /* EGL_EXT_gl_colorspace_scrgb_linear */


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