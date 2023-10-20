#ifndef EGL_EXT_device_base
#define EGL_EXT_device_base 1
typedef void *EGLDeviceEXT;
#define EGL_NO_DEVICE_EXT                 EGL_CAST(EGLDeviceEXT,0)
#define EGL_BAD_DEVICE_EXT                0x322B
#define EGL_DEVICE_EXT                    0x322C
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceAttribEXT (EGLDeviceEXT device, EGLint attribute, EGLAttrib *value);
EGLAPI const char *EGLAPIENTRY eglQueryDeviceStringEXT (EGLDeviceEXT device, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDevicesEXT (EGLint max_devices, EGLDeviceEXT *devices, EGLint *num_devices);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayAttribEXT (EGLDisplay dpy, EGLint attribute, EGLAttrib *value);
#endif /* EGL_EXT_device_base */

#ifndef EGL_EXT_device_drm
#define EGL_EXT_device_drm 1
#define EGL_DRM_DEVICE_FILE_EXT           0x3233
#define EGL_DRM_MASTER_FD_EXT             0x333C
#endif /* EGL_EXT_device_drm */

#ifndef EGL_EXT_device_drm_render_node
#define EGL_EXT_device_drm_render_node 1
#define EGL_DRM_RENDER_NODE_FILE_EXT      0x3377
#endif /* EGL_EXT_device_drm_render_node */

#ifndef EGL_EXT_device_enumeration
#define EGL_EXT_device_enumeration 1
#endif /* EGL_EXT_device_enumeration */

#ifndef EGL_EXT_device_openwf
#define EGL_EXT_device_openwf 1
#define EGL_OPENWF_DEVICE_ID_EXT          0x3237
#define EGL_OPENWF_DEVICE_EXT             0x333D
#endif /* EGL_EXT_device_openwf */

#ifndef EGL_EXT_device_persistent_id
#define EGL_EXT_device_persistent_id 1
#define EGL_DEVICE_UUID_EXT               0x335C
#define EGL_DRIVER_UUID_EXT               0x335D
#define EGL_DRIVER_NAME_EXT               0x335E
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDeviceBinaryEXT (EGLDeviceEXT device, EGLint name, EGLint max_size, void *value, EGLint *size);
#endif /* EGL_EXT_device_persistent_id */

#ifndef EGL_EXT_device_query
#define EGL_EXT_device_query 1
#endif /* EGL_EXT_device_query */

#ifndef EGL_EXT_device_query_name
#define EGL_EXT_device_query_name 1
#define EGL_RENDERER_EXT                  0x335F
#endif /* EGL_EXT_device_query_name */

#ifndef EGL_EXT_explicit_device
#define EGL_EXT_explicit_device 1
#endif /* EGL_EXT_explicit_device */