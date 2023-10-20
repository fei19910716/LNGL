#ifndef EGL_EXT_protected_surface
#define EGL_EXT_protected_surface 1
#endif /* EGL_EXT_protected_surface */

#ifndef EGL_EXT_surface_CTA861_3_metadata
#define EGL_EXT_surface_CTA861_3_metadata 1
#define EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT 0x3360
#define EGL_CTA861_3_MAX_FRAME_AVERAGE_LEVEL_EXT 0x3361
#endif /* EGL_EXT_surface_CTA861_3_metadata */

#ifndef EGL_EXT_surface_SMPTE2086_metadata
#define EGL_EXT_surface_SMPTE2086_metadata 1
#define EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT 0x3341
#define EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT 0x3342
#define EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT 0x3343
#define EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT 0x3344
#define EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT 0x3345
#define EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT 0x3346
#define EGL_SMPTE2086_WHITE_POINT_X_EXT   0x3347
#define EGL_SMPTE2086_WHITE_POINT_Y_EXT   0x3348
#define EGL_SMPTE2086_MAX_LUMINANCE_EXT   0x3349
#define EGL_SMPTE2086_MIN_LUMINANCE_EXT   0x334A
#define EGL_METADATA_SCALING_EXT          50000
#endif /* EGL_EXT_surface_SMPTE2086_metadata */

#ifndef EGL_EXT_surface_compression
#define EGL_EXT_surface_compression 1
#define EGL_SURFACE_COMPRESSION_EXT       0x34B0
#define EGL_SURFACE_COMPRESSION_PLANE1_EXT 0x328E
#define EGL_SURFACE_COMPRESSION_PLANE2_EXT 0x328F
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_NONE_EXT 0x34B1
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_DEFAULT_EXT 0x34B2
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_1BPC_EXT 0x34B4
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_2BPC_EXT 0x34B5
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_3BPC_EXT 0x34B6
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_4BPC_EXT 0x34B7
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_5BPC_EXT 0x34B8
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_6BPC_EXT 0x34B9
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_7BPC_EXT 0x34BA
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_8BPC_EXT 0x34BB
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_9BPC_EXT 0x34BC
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_10BPC_EXT 0x34BD
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_11BPC_EXT 0x34BE
#define EGL_SURFACE_COMPRESSION_FIXED_RATE_12BPC_EXT 0x34BF
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySupportedCompressionRatesEXT (EGLDisplay dpy, EGLConfig config, const EGLAttrib *attrib_list, EGLint *rates, EGLint rate_size, EGLint *num_rates);
#endif /* EGL_EXT_surface_compression */

#ifndef EGL_EXT_yuv_surface
#define EGL_EXT_yuv_surface 1
#define EGL_YUV_ORDER_EXT                 0x3301
#define EGL_YUV_NUMBER_OF_PLANES_EXT      0x3311
#define EGL_YUV_SUBSAMPLE_EXT             0x3312
#define EGL_YUV_DEPTH_RANGE_EXT           0x3317
#define EGL_YUV_CSC_STANDARD_EXT          0x330A
#define EGL_YUV_PLANE_BPP_EXT             0x331A
#define EGL_YUV_BUFFER_EXT                0x3300
#define EGL_YUV_ORDER_YUV_EXT             0x3302
#define EGL_YUV_ORDER_YVU_EXT             0x3303
#define EGL_YUV_ORDER_YUYV_EXT            0x3304
#define EGL_YUV_ORDER_UYVY_EXT            0x3305
#define EGL_YUV_ORDER_YVYU_EXT            0x3306
#define EGL_YUV_ORDER_VYUY_EXT            0x3307
#define EGL_YUV_ORDER_AYUV_EXT            0x3308
#define EGL_YUV_SUBSAMPLE_4_2_0_EXT       0x3313
#define EGL_YUV_SUBSAMPLE_4_2_2_EXT       0x3314
#define EGL_YUV_SUBSAMPLE_4_4_4_EXT       0x3315
#define EGL_YUV_DEPTH_RANGE_LIMITED_EXT   0x3318
#define EGL_YUV_DEPTH_RANGE_FULL_EXT      0x3319
#define EGL_YUV_CSC_STANDARD_601_EXT      0x330B
#define EGL_YUV_CSC_STANDARD_709_EXT      0x330C
#define EGL_YUV_CSC_STANDARD_2020_EXT     0x330D
#define EGL_YUV_PLANE_BPP_0_EXT           0x331B
#define EGL_YUV_PLANE_BPP_8_EXT           0x331C
#define EGL_YUV_PLANE_BPP_10_EXT          0x331D
#endif /* EGL_EXT_yuv_surface */


#ifndef EGL_KHR_mutable_render_buffer
#define EGL_KHR_mutable_render_buffer 1
#define EGL_MUTABLE_RENDER_BUFFER_BIT_KHR 0x1000
#endif /* EGL_KHR_mutable_render_buffer */
// https://registry.khronos.org/EGL/extensions/KHR/EGL_KHR_mutable_render_buffer.txt

#ifndef EGL_EXT_bind_to_front
#define EGL_EXT_bind_to_front 1
#define EGL_FRONT_BUFFER_EXT              0x3464
#endif /* EGL_EXT_bind_to_front */

#ifndef EGL_EXT_present_opaque
#define EGL_EXT_present_opaque 1
#define EGL_PRESENT_OPAQUE_EXT            0x31DF
#endif /* EGL_EXT_present_opaque */

#ifndef EGL_ANDROID_front_buffer_auto_refresh
#define EGL_ANDROID_front_buffer_auto_refresh 1
#define EGL_FRONT_BUFFER_AUTO_REFRESH_ANDROID 0x314C
#endif /* EGL_ANDROID_front_buffer_auto_refresh */