#ifndef EGL_EXT_output_base
#define EGL_EXT_output_base 1
typedef void *EGLOutputLayerEXT;
typedef void *EGLOutputPortEXT;
#define EGL_NO_OUTPUT_LAYER_EXT           EGL_CAST(EGLOutputLayerEXT,0)
#define EGL_NO_OUTPUT_PORT_EXT            EGL_CAST(EGLOutputPortEXT,0)
#define EGL_BAD_OUTPUT_LAYER_EXT          0x322D
#define EGL_BAD_OUTPUT_PORT_EXT           0x322E
#define EGL_SWAP_INTERVAL_EXT             0x322F
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputLayersEXT (EGLDisplay dpy, const EGLAttrib *attrib_list, EGLOutputLayerEXT *layers, EGLint max_layers, EGLint *num_layers);
EGLAPI EGLBoolean EGLAPIENTRY eglGetOutputPortsEXT (EGLDisplay dpy, const EGLAttrib *attrib_list, EGLOutputPortEXT *ports, EGLint max_ports, EGLint *num_ports);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib value);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputLayerAttribEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib *value);
EGLAPI const char *EGLAPIENTRY eglQueryOutputLayerStringEXT (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
EGLAPI EGLBoolean EGLAPIENTRY eglOutputPortAttribEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib value);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryOutputPortAttribEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib *value);
EGLAPI const char *EGLAPIENTRY eglQueryOutputPortStringEXT (EGLDisplay dpy, EGLOutputPortEXT port, EGLint name);
#endif /* EGL_EXT_output_base */

#ifndef EGL_EXT_output_drm
#define EGL_EXT_output_drm 1
#define EGL_DRM_CRTC_EXT                  0x3234
#define EGL_DRM_PLANE_EXT                 0x3235
#define EGL_DRM_CONNECTOR_EXT             0x3236
#endif /* EGL_EXT_output_drm */

#ifndef EGL_EXT_output_openwf
#define EGL_EXT_output_openwf 1
#define EGL_OPENWF_PIPELINE_ID_EXT        0x3238
#define EGL_OPENWF_PORT_ID_EXT            0x3239
#endif /* EGL_EXT_output_openwf */