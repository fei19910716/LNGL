
#ifndef EGL_KHR_create_context
#define EGL_KHR_create_context 1
// version control
#define EGL_OPENGL_ES3_BIT_KHR            0x00000040
#define EGL_CONTEXT_MAJOR_VERSION_KHR     0x3098
#define EGL_CONTEXT_MINOR_VERSION_KHR     0x30FB
// core vs compatibility layer control for OpenGL
#define EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR 0x30FD
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR 0x00000001
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR 0x00000002
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR 0x00000002
// Debug Contexts
#define EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR  0x00000001
// OpenGL Robustness
#define EGL_CONTEXT_FLAGS_KHR             0x30FC
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR 0x00000004
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR 0x31BD
#define EGL_NO_RESET_NOTIFICATION_KHR     0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_KHR     0x31BF
#endif /* EGL_KHR_create_context */

#ifndef EGL_KHR_create_context_no_error
#define EGL_KHR_create_context_no_error 1
#define EGL_CONTEXT_OPENGL_NO_ERROR_KHR   0x31B3                    // attribute, boolean
#endif /* EGL_KHR_create_context_no_error */

#ifndef EGL_EXT_create_context_robustness
#define EGL_EXT_create_context_robustness 1
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF                 // attribute, boolean
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138   // attribute
#define EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#endif /* EGL_EXT_create_context_robustness */

/**
 * @brief EGL_KHR_create_context
 * 
 * @deprecated
 * @note This functionality is core to EGL 1.5, so the extension is no longer needed.
 * 
 * This extension enables a number of new context attributes to be specified in EGL to allow greater control of the returned context. 
 * The new functionality consists of four aspects; version control, core vs compatibility layer control for OpenGL, debugging (see extension GL_KHR_debug), 
 * and robustness in OpenGL (see desktop extension “GL_ARB_robustness”)
 * 
*/


/**
 * @brief EGL_EXT_create_context_robustness
 * 
 * @deprecated
 * @note This functionality is core to EGL 1.5, so the extension is no longer needed.
 * 
 * 该扩展用于创建robust context, 当该context被make current的时候，对所有buffer的访问都会进行安全限制; 同时，当硬件reset时也需要通知app。
 * 
 * The extension adds two new attributes for context creation:
 * EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT, attempting to access data outside of a buffer’s bounds will result in undefined.
 * 
 * EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT, This allows users to force a context to be deleted in the event of it causing a hardware reset.
*/

void Samples()
{
    // Create a robust context with hardware notifications
    EGLint contextAttribs[] =
    {
        EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT, EGL_TRUE,
        EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT, EGL_LOSE_CONTEXT_ON_RESET_EXT, // context lost
        EGL_NONE
    };
    EGLContext context = eglCreateContext(display, config, NULL, contextAttribs);
}