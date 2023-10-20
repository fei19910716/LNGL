#ifndef EGL_KHR_platform_android
#define EGL_KHR_platform_android 1
#define EGL_PLATFORM_ANDROID_KHR          0x3141
#endif /* EGL_KHR_platform_android */

#ifndef EGL_KHR_platform_gbm
#define EGL_KHR_platform_gbm 1
#define EGL_PLATFORM_GBM_KHR              0x31D7
#endif /* EGL_KHR_platform_gbm */

#ifndef EGL_KHR_platform_wayland
#define EGL_KHR_platform_wayland 1
#define EGL_PLATFORM_WAYLAND_KHR          0x31D8
#endif /* EGL_KHR_platform_wayland */

#ifndef EGL_KHR_platform_x11
#define EGL_KHR_platform_x11 1
#define EGL_PLATFORM_X11_KHR              0x31D5
#define EGL_PLATFORM_X11_SCREEN_KHR       0x31D6
#endif /* EGL_KHR_platform_x11 */


#ifndef EGL_EXT_platform_base
#define EGL_EXT_platform_base 1
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplayEXT (EGLenum platform, void *native_display, const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurfaceEXT (EGLDisplay dpy, EGLConfig config, void *native_window, const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurfaceEXT (EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLint *attrib_list);
#endif /* EGL_EXT_platform_base */

#ifndef EGL_EXT_platform_device
#define EGL_EXT_platform_device 1
#define EGL_PLATFORM_DEVICE_EXT           0x313F
#endif /* EGL_EXT_platform_device */

#ifndef EGL_EXT_platform_wayland
#define EGL_EXT_platform_wayland 1
#define EGL_PLATFORM_WAYLAND_EXT          0x31D8
#endif /* EGL_EXT_platform_wayland */

#ifndef EGL_EXT_platform_x11
#define EGL_EXT_platform_x11 1
#define EGL_PLATFORM_X11_EXT              0x31D5
#define EGL_PLATFORM_X11_SCREEN_EXT       0x31D6
#endif /* EGL_EXT_platform_x11 */

#ifndef EGL_MESA_platform_gbm
#define EGL_MESA_platform_gbm 1
#define EGL_PLATFORM_GBM_MESA             0x31D7
#endif /* EGL_MESA_platform_gbm */

#ifndef EGL_EXT_platform_xcb
#define EGL_EXT_platform_xcb 1
#define EGL_PLATFORM_XCB_EXT              0x31DC
#define EGL_PLATFORM_XCB_SCREEN_EXT       0x31DE
#endif /* EGL_EXT_platform_xcb */

#ifndef EGL_QNX_platform_screen
#define EGL_QNX_platform_screen 1
#define EGL_PLATFORM_SCREEN_QNX           0x3550
#endif /* EGL_QNX_platform_screen */