#ifndef EGL_KHR_debug
#define EGL_KHR_debug 1
typedef void *EGLLabelKHR;
typedef void *EGLObjectKHR;
typedef void (EGLAPIENTRY  *EGLDEBUGPROCKHR)(EGLenum error,const char *command,EGLint messageType,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,const char* message);
#define EGL_OBJECT_THREAD_KHR             0x33B0
#define EGL_OBJECT_DISPLAY_KHR            0x33B1
#define EGL_OBJECT_CONTEXT_KHR            0x33B2
#define EGL_OBJECT_SURFACE_KHR            0x33B3
#define EGL_OBJECT_IMAGE_KHR              0x33B4
#define EGL_OBJECT_SYNC_KHR               0x33B5
#define EGL_OBJECT_STREAM_KHR             0x33B6
#define EGL_DEBUG_MSG_CRITICAL_KHR        0x33B9
#define EGL_DEBUG_MSG_ERROR_KHR           0x33BA
#define EGL_DEBUG_MSG_WARN_KHR            0x33BB
#define EGL_DEBUG_MSG_INFO_KHR            0x33BC
#define EGL_DEBUG_CALLBACK_KHR            0x33B8
EGLAPI EGLint EGLAPIENTRY eglDebugMessageControlKHR (EGLDEBUGPROCKHR callback, const EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDebugKHR (EGLint attribute, EGLAttrib *value);
EGLAPI EGLint EGLAPIENTRY eglLabelObjectKHR (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
#endif /* EGL_KHR_debug */