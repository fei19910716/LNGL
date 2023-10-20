#ifndef EGL_EXT_compositor
#define EGL_EXT_compositor 1
#define EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT 0x3460
#define EGL_EXTERNAL_REF_ID_EXT           0x3461
#define EGL_COMPOSITOR_DROP_NEWEST_FRAME_EXT 0x3462
#define EGL_COMPOSITOR_KEEP_NEWEST_FRAME_EXT 0x3463
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetContextListEXT (const EGLint *external_ref_ids, EGLint num_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetContextAttributesEXT (EGLint external_ref_id, const EGLint *context_attributes, EGLint num_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetWindowListEXT (EGLint external_ref_id, const EGLint *external_win_ids, EGLint num_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetWindowAttributesEXT (EGLint external_win_id, const EGLint *window_attributes, EGLint num_entries);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorBindTexWindowEXT (EGLint external_win_id);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSetSizeEXT (EGLint external_win_id, EGLint width, EGLint height);
EGLAPI EGLBoolean EGLAPIENTRY eglCompositorSwapPolicyEXT (EGLint external_win_id, EGLint policy);
#endif /* EGL_EXT_compositor */