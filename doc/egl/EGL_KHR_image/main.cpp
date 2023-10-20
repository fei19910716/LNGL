

#ifndef EGL_KHR_gl_renderbuffer_image
#define EGL_KHR_gl_renderbuffer_image 1
#define EGL_GL_RENDERBUFFER_KHR           0x30B9
#endif /* EGL_KHR_gl_renderbuffer_image */

#ifndef EGL_KHR_gl_texture_2D_image
#define EGL_KHR_gl_texture_2D_image 1
#define EGL_GL_TEXTURE_2D_KHR             0x30B1
#define EGL_GL_TEXTURE_LEVEL_KHR          0x30BC
#endif /* EGL_KHR_gl_texture_2D_image */

#ifndef EGL_KHR_gl_texture_3D_image
#define EGL_KHR_gl_texture_3D_image 1
#define EGL_GL_TEXTURE_3D_KHR             0x30B2
#define EGL_GL_TEXTURE_ZOFFSET_KHR        0x30BD
#endif /* EGL_KHR_gl_texture_3D_image */

#ifndef EGL_KHR_gl_texture_cubemap_image
#define EGL_KHR_gl_texture_cubemap_image 1
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X_KHR 0x30B3
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR 0x30B4
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y_KHR 0x30B5
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR 0x30B6
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z_KHR 0x30B7
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR 0x30B8
#endif /* EGL_KHR_gl_texture_cubemap_image */

#ifndef EGL_KHR_image_base
#define EGL_KHR_image_base 1
#define EGL_IMAGE_PRESERVED_KHR           0x30D2
#endif /* EGL_KHR_image_base */

#ifndef EGL_KHR_image_pixmap
#define EGL_KHR_image_pixmap 1
#endif /* EGL_KHR_image_pixmap */

#ifndef EGL_KHR_image
#define EGL_KHR_image 1
typedef void *EGLImageKHR;
#define EGL_NATIVE_PIXMAP_KHR             0x30B0
#define EGL_NO_IMAGE_KHR                  EGL_CAST(EGLImageKHR,0)
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
EGLAPI EGLBoolean  EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#endif /* EGL_KHR_image */


/**
 * @brief EGL_KHR_image
 * 
 * @deprecated
 * @note This functionality is core to EGL 1.5, so the extension is no longer needed.
 * @note EGL_KHR_image_pixmap is sill needed in EGL 1.5.
 * 
 * 
 * EGL_KHR_image is equivalent to the combination of the functionality defined by EGL_KHR_image_base and EGL_KHR_image_pixmap, with the exception that 
 * if EGL_KHR_image is supported and EGL_KHR_image_base is not, the attribute EGL_IMAGE_PRESERVED_KHR is not accepted in <attrib_list>.
 * 
 * Gralloc on Android, which is covered in ANDROID_image_native_buffer subsection.
 * dma_buf on Linux, covered in EGL_EXT_image_dma_buf_import subsection.
*/

void main()
{
    EGLint attrib_list[] =
    {
        EGL_IMAGE_PRESERVED_KHR , EGL_TRUE,
        EGL_NONE
    };

    EGLNativePixmapType hpixmap;
    
    eglCreateImageKHR (dpy, ctx, EGL_NATIVE_PIXMAP_KHR, EGLClientBuffer(hpixmap), attrib_list);
}