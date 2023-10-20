#define KHRONOS_SUPPORT_INT64

#ifndef EGL_KHR_fence_sync
#define EGL_KHR_fence_sync 1
typedef khronos_utime_nanoseconds_t EGLTimeKHR;
#ifdef KHRONOS_SUPPORT_INT64
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR 0x30F0
#define EGL_SYNC_CONDITION_KHR            0x30F8
#define EGL_SYNC_FENCE_KHR                0x30F9
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSyncKHR     (EGLDisplay dpy, EGLenum type, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySyncKHR    (EGLDisplay dpy, EGLSyncKHR sync);
EGLAPI EGLint     EGLAPIENTRY eglClientWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttribKHR  (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint *value);
#endif /* KHRONOS_SUPPORT_INT64 */
#endif /* EGL_KHR_fence_sync */

#ifndef EGL_KHR_wait_sync
#define EGL_KHR_wait_sync 1
EGLAPI EGLint EGLAPIENTRY eglWaitSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
#endif /* EGL_KHR_wait_sync */

#ifndef EGL_KHR_reusable_sync
#define EGL_KHR_reusable_sync 1
#ifdef KHRONOS_SUPPORT_INT64
#define EGL_SYNC_STATUS_KHR               0x30F1
#define EGL_SIGNALED_KHR                  0x30F2
#define EGL_UNSIGNALED_KHR                0x30F3
#define EGL_TIMEOUT_EXPIRED_KHR           0x30F5
#define EGL_CONDITION_SATISFIED_KHR       0x30F6
#define EGL_SYNC_TYPE_KHR                 0x30F7
#define EGL_SYNC_REUSABLE_KHR             0x30FA
#define EGL_SYNC_FLUSH_COMMANDS_BIT_KHR   0x0001
#define EGL_FOREVER_KHR                   0xFFFFFFFFFFFFFFFFull
#define EGL_NO_SYNC_KHR                   EGL_CAST(EGLSyncKHR,0)
EGLAPI EGLBoolean EGLAPIENTRY eglSignalSyncKHR (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
#endif /* KHRONOS_SUPPORT_INT64 */
#endif /* EGL_KHR_reusable_sync */

#ifndef EGL_EXT_client_sync
#define EGL_EXT_client_sync 1
#define EGL_SYNC_CLIENT_EXT               0x3364
#define EGL_SYNC_CLIENT_SIGNAL_EXT        0x3365
EGLAPI EGLBoolean EGLAPIENTRY eglClientSignalSyncEXT (EGLDisplay dpy, EGLSync sync, const EGLAttrib *attrib_list);
#endif /* EGL_EXT_client_sync */

#ifndef EGL_EXT_sync_reuse
#define EGL_EXT_sync_reuse 1
EGLAPI EGLBoolean EGLAPIENTRY eglUnsignalSyncEXT (EGLDisplay dpy, EGLSync sync, const EGLAttrib *attrib_list);
#endif /* EGL_EXT_sync_reuse */

#ifndef EGL_KHR_cl_event
#define EGL_KHR_cl_event 1
#define EGL_CL_EVENT_HANDLE_KHR           0x309C
#define EGL_SYNC_CL_EVENT_KHR             0x30FE
#define EGL_SYNC_CL_EVENT_COMPLETE_KHR    0x30FF
#endif /* EGL_KHR_cl_event */

#ifndef EGL_KHR_cl_event2
#define EGL_KHR_cl_event2 1
typedef void *EGLSyncKHR;
typedef intptr_t EGLAttribKHR;
EGLAPI EGLSyncKHR EGLAPIENTRY eglCreateSync64KHR (EGLDisplay dpy, EGLenum type, const EGLAttribKHR *attrib_list);
#endif /* EGL_KHR_cl_event2 */