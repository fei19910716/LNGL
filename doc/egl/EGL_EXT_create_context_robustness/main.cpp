
#ifndef EGL_EXT_create_context_robustness
#define EGL_EXT_create_context_robustness 1
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT 0x30BF
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT 0x3138
#define EGL_NO_RESET_NOTIFICATION_EXT     0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET_EXT     0x31BF
#endif /* EGL_EXT_create_context_robustness */

/**
 * @brief EGL_EXT_create_context_robustness
 * @deprecated EGL 1.5
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