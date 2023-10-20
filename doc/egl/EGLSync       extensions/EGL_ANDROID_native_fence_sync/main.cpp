
#ifndef EGL_ANDROID_native_fence_sync
#define EGL_ANDROID_native_fence_sync 1
#define EGL_SYNC_NATIVE_FENCE_ANDROID     0x3144
#define EGL_SYNC_NATIVE_FENCE_FD_ANDROID  0x3145
#define EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID 0x3146
#define EGL_NO_NATIVE_FENCE_FD_ANDROID    -1
EGLAPI EGLint EGLAPIENTRY eglDupNativeFenceFDANDROID (EGLDisplay dpy, EGLSyncKHR sync);
#endif /* EGL_ANDROID_native_fence_sync */


/**
 * @brief EGL_ANDROID_native_fence_sync
 * 
 * This extension enables the creation of EGL fence sync objects that are associated with a native synchronization fence object that is referenced using a fd.
 * 
 * 为了实现跨进程纹理共享，在两个进程进行该纹理的读写同步是有必要的。利用该扩展，可以将sync object通过fd进行跨进程共享。
*/

void main()
{
    //===============
    // Process A:
    //===============
    EGLSyncKHR eglSyncKHR = eglCreateSyncKHR(eglDisplay, EGL_SYNC_REUSABLE_KHR, NULL);
    EGLint FileDescriptor = eglDupNativeFenceFDANDROID(eglDisplay, eglSyncKHR);
    
    //===============
    // Process B:
    //===============
    EGLint attrs[] = {
    EGL_SYNC_NATIVE_FENCE_FD_ANDROID, FileDescriptor,
    EGL_SYNC_CONDITION_KHR, EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID
    EGL_NONE,
    };
    EGLSyncKHR eglSyncKHR = eglCreateSyncKHR(eglDisplay, EGL_SYNC_NATIVE_FENCE_ANDROID, attrs);
    eglClientWaitSyncKHR(eglDisplay, eglSyncKHR, 0, EGL_FOREVER_KHR);
}