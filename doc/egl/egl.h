#ifndef __egl_h_
#define __egl_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright 2013-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
**
** This header is generated from the Khronos EGL XML API Registry.
** The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   http://www.khronos.org/registry/egl
**
** Khronos $Git commit SHA1: 5b1165a76f $ on $Git commit date: 2023-06-22 06:48:34 -0700 $
*/

#include <EGL/eglplatform.h>

#ifndef EGL_EGL_PROTOTYPES
#define EGL_EGL_PROTOTYPES 1
#endif

/* Generated on date 20230622 */

/* Generated C header for:
 * API: egl
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: None
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#pragma region 1.0

#ifndef EGL_VERSION_1_0
#define EGL_VERSION_1_0 1
typedef unsigned int EGLBoolean;
typedef void *EGLDisplay;
#include <KHR/khrplatform.h>
#include <EGL/eglplatform.h>
typedef void *EGLConfig;
typedef void *EGLSurface;
typedef void *EGLContext;
typedef void (*__eglMustCastToProperFunctionPointerType)(void);

#define EGL_NO_CONTEXT                    EGL_CAST(EGLContext,0)
#define EGL_NO_DISPLAY                    EGL_CAST(EGLDisplay,0)
#define EGL_NO_SURFACE                    EGL_CAST(EGLSurface,0)

#define EGL_TRUE                          1
#define EGL_FALSE                         0

#define EGL_DONT_CARE                     EGL_CAST(EGLint,-1)

/**
 * 定义eglGetError返回的status
*/
#define EGL_SUCCESS                       0x3000
#define EGL_NOT_INITIALIZED               0x3001
#define EGL_BAD_ACCESS                    0x3002
#define EGL_BAD_ALLOC                     0x3003
#define EGL_BAD_ATTRIBUTE                 0x3004
#define EGL_BAD_CONFIG                    0x3005
#define EGL_BAD_CONTEXT                   0x3006
#define EGL_BAD_CURRENT_SURFACE           0x3007
#define EGL_BAD_DISPLAY                   0x3008
#define EGL_BAD_MATCH                     0x3009
#define EGL_BAD_NATIVE_PIXMAP             0x300A
#define EGL_BAD_NATIVE_WINDOW             0x300B
#define EGL_BAD_PARAMETER                 0x300C
#define EGL_BAD_SURFACE                   0x300D

/**
 * 定义EGLConfig的attibutes
*/
#define EGL_BUFFER_SIZE                   0x3020 // total color component bits in the color buffer(RGBA8 format should be 32)
#define EGL_ALPHA_SIZE                    0x3021 // bits of Alpha in the color buffer
#define EGL_BLUE_SIZE                     0x3022 // bits of Green in the color buffer
#define EGL_GREEN_SIZE                    0x3023 // bits of Blue in the color buffer
#define EGL_RED_SIZE                      0x3024 // bits of Red in the color buffer
#define EGL_DEPTH_SIZE                    0x3025 // bits of Z in the depth buffer(D24S8 format should be 24)
#define EGL_STENCIL_SIZE                  0x3026 // bits of Stencil in the stencil buffer(D24S8 format should be 8)
#define EGL_CONFIG_CAVEAT                 0x3027 // any caveats(警告) for the config
{
    /**
     * rendering to a surface with this config may run at reduced performance
     * (for example, the hardware may not support the color buffer depths described by the config);
    */
    #define EGL_SLOW_CONFIG                   0x3050
    /**
     * rendering to a surface with this config will not pass the required OpenGL ES conformance tests(即可能不会遵守Spec)
     * 
    */
    #define EGL_NON_CONFORMANT_CONFIG         0x3051
}
#define EGL_CONFIG_ID                     0x3028 // unique EGLConfig identifier
/**
 * Buffer level zero corresponds to the default frame buffer of the display. 
 * Buffer level one is the first overlay frame buffer, level two the second overlay frame buffer, and so on. 
 * Negative buffer levels correspond to underlay frame buffers. The default value is zero. 
 * Most platforms do not support buffer levels other than zero. The behavior of windows placed in overlay and underlay planes depends on the underlying platform.
*/
#define EGL_LEVEL                         0x3029
/**
 * EGL_MAX_PBUFFER_WIDTH and EGL_MAX_PBUFFER_HEIGHT indicate the maximum width and height that can be passed into eglCreatePbufferSurface, 
 * and EGL_MAX_PBUFFER_PIXELS indicates the maximum number of pixels (width times height) for a pbuffer surface.
*/
#define EGL_MAX_PBUFFER_HEIGHT            0x302A
#define EGL_MAX_PBUFFER_PIXELS            0x302B
#define EGL_MAX_PBUFFER_WIDTH             0x302C
/**
 * The interpretation of the native visual identifier and type is platform-dependent. 
 * For example, if the platform is X11, then the identifier will be the XID of an X Visual.
*/
#define EGL_NATIVE_RENDERABLE             0x302D // whether the native API can be used to render into a surface created with the EGLConfig.
#define EGL_NATIVE_VISUAL_ID              0x302E // If an EGLConfig supports EGL_WINDOW_BIT, handle of corresponding native visual.
#define EGL_NATIVE_VISUAL_TYPE            0x302F // native visual type of the associated visual
#define EGL_SAMPLES                       0x3031 // the number of samples per pixel
#define EGL_SAMPLE_BUFFERS                0x3032 // the number of multisample buffers, which must be zero or one
#define EGL_SURFACE_TYPE                  0x3033 
{
    #define EGL_PBUFFER_BIT                   0x0001
    #define EGL_PIXMAP_BIT                    0x0002
    #define EGL_WINDOW_BIT                    0x0004
}
/**
 * If the attribute is EGL_TRANSPARENT_RGB, then the EGLConfig supports transparency; a transparent pixel will be drawn when the red, green and blue 
 * values which are read from the framebuffer are equal to EGL_TRANSPARENT_RED_VALUE, EGL_TRANSPARENT_GREEN_VALUE and EGL_TRANSPARENT_BLUE_VALUE, respectively.
*/
#define EGL_TRANSPARENT_TYPE              0x3034 // indicates whether or not a configuration supports transparency.
{
    #define EGL_TRANSPARENT_RGB               0x3052
}
#define EGL_TRANSPARENT_BLUE_VALUE        0x3035
#define EGL_TRANSPARENT_GREEN_VALUE       0x3036
#define EGL_TRANSPARENT_RED_VALUE         0x3037
#define EGL_NONE                          0x3038

/**
 * used in const char *eglQueryString(EGLDisplay dpy, EGLint name);
*/
#define EGL_VENDOR                        0x3053 // 驱动名称
#define EGL_VERSION                       0x3054 // 驱动版本名称<major version.minor version><space><vendor specific info>
#define EGL_EXTENSIONS                    0x3055 // 查询支持的扩展
{
    /**
     * used in EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
     * 
     * EGL_LARGEST_PBUFFER： 获得不超过指定的width和height的情况下能分配的最大pbuffer(比如有的实现需要width和height必须是2次幂，这时会修正width和height的大小)
    */
    #define EGL_HEIGHT                        0x3056 // the pixel width
    #define EGL_WIDTH                         0x3057 // the pixel height
    #define EGL_LARGEST_PBUFFER               0x3058
}
/**
 * used in EGLSurface eglGetCurrentSurface(EGLint readdraw);
*/
#define EGL_DRAW                          0x3059
#define EGL_READ                          0x305A
/**
 * used in EGLBoolean eglWaitNative(EGLint engine);
 * 
 * engine denotes a particular marking engine (another drawing API, such as GDI or Xlib) to be waited on. 
 * Valid values of engine are defined by EGL extensions specific to implementations, but implementations will always recognize the symbolic constant EGL_CORE_NATIVE_ENGINE, 
 * which denotes the most commonly used marking engine other then a client API.
*/
#define EGL_CORE_NATIVE_ENGINE            0x305B

typedef EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSECONFIGPROC) (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLCOPYBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
typedef EGLContext (EGLAPIENTRYP PFNEGLCREATECONTEXTPROC) (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERSURFACEPROC) (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGATTRIBPROC) (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETCONFIGSPROC) (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config);
typedef EGLDisplay (EGLAPIENTRYP PFNEGLGETCURRENTDISPLAYPROC) (void);
typedef EGLSurface (EGLAPIENTRYP PFNEGLGETCURRENTSURFACEPROC) (EGLint readdraw);
typedef EGLDisplay (EGLAPIENTRYP PFNEGLGETDISPLAYPROC) (EGLNativeDisplayType display_id);
typedef EGLint     (EGLAPIENTRYP PFNEGLGETERRORPROC) (void);
typedef __eglMustCastToProperFunctionPointerType (EGLAPIENTRYP PFNEGLGETPROCADDRESSPROC) (const char *procname);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLINITIALIZEPROC) (EGLDisplay dpy, EGLint *major, EGLint *minor);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLMAKECURRENTPROC) (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYCONTEXTPROC) (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value);
typedef const char *(EGLAPIENTRYP PFNEGLQUERYSTRINGPROC) (EGLDisplay dpy, EGLint name);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSURFACEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPBUFFERSPROC) (EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLTERMINATEPROC) (EGLDisplay dpy);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLWAITGLPROC) (void);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLWAITNATIVEPROC) (EGLint engine);
#if EGL_EGL_PROTOTYPES
/** 从驱动定义的所有Configs中选择和attrib_list中指定的属性匹配的Config
 * 
 * Spec相关定义如下(不同的Attribute的选择标准和排序方式是不一样的)：
 * Attribute            Selection Criteria      Sort Order
 * EGL_BUFFER_SIZE      AtLeast                 Smaller
 * EGL_RED_SIZE         AtLeast                 Special
 * EGL_GREEN_SIZE
 * EGL_BLUE_SIZE
 * EGL_ALPHA_SIZE
 * EGL_DEPTH_SIZE
 * EGL_STENCIL_SIZE
 * 
 * EGL_CONFIG_ID        Special                 Smaller
 * EGL_CONFIG_CAVEAT    Exact                   Special
 * EGL_LEVEL            Exact                   None
 * ...
*/
EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
/**
 * To copy the color buffer to a native pixmap, perform an implicit flush operation on the context
 * 
 * The mapping of pixels in the color buffer to pixels in the pixmap is platform dependent, 
 * since the native platform pixel coordinate system may differ from that of client APIs.
*/
EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
/**
 * config和Surface创建时的config一般应该相同，不同的话用于判断该Context和Surface是否是Compatible
*/
EGLAPI EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
/** 返回一个Config的Attribute对应的Value
 * 
*/
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);
/** 返回当前Display支持的configs，由驱动内部定义，Config即Color Format + DS Format + Samples
 * 
 * DS Format
 * { QCT_PIXELFORMAT_UNKNOWN,              QCT_PIXELFORMAT_UNKNOWN           },      // 0, 0
 * { QCT_PIXELFORMAT_D16_UNORM,            QCT_PIXELFORMAT_UNKNOWN           },      // 16, 0
 * { QCT_PIXELFORMAT_D24_UNORM_S8_UINT,    QCT_PIXELFORMAT_D24_UNORM_S8_UINT },      // 24/8 combined
 * { QCT_PIXELFORMAT_UNKNOWN,              QCT_PIXELFORMAT_S8_UINT           }       // 0, 8
 * 
 * Samples: 0,2,4
 * 
 * Color Format
 * // 这三个format可以和DS Format, Samples构成36种组合
 * QCT_PIXELFORMAT_B5G6R5_UNORM
 * QCT_PIXELFORMAT_R8G8B8X8_UNORM
 * QCT_PIXELFORMAT_R8G8B8A8_UNORM
 * 
 * // 下面的format不支持Samples, 只能和DS Format构成36种组合
 * QCT_PIXELFORMAT_R8G8B8_UNORM
 * QCT_PIXELFORMAT_A1B5G5R5_UNORM
 * QCT_PIXELFORMAT_A4B4G4R4_UNORM
 * QCT_PIXELFORMAT_R16G16B16A16_FLOAT
 * QCT_PIXELFORMAT_R10G10B10A2_UNORM
 * QCT_PIXELFORMAT_NV12_EXT
 * QCT_PIXELFORMAT_NV21
 * QCT_PIXELFORMAT_NV21_EXT
 * QCT_PIXELFORMAT_P010
*/
EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config);
/** 返回当前线程的Context绑定的Display
 * The display for the current context in the calling thread, for the current rendering API, is returned.
*/
EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (void);
/** 返回当前线程的Context绑定的Surfaces
 * readdraw is either EGL_READ or EGL_DRAW, to return respectively the read or draw surfaces bound to the current context in the calling thread, 
 * for the current rendering API
*/
EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint readdraw);
/** 根据传入的NativeDisplay构造EGLDisplay
 * 
 * EGLNativeDisplayType在win32上是HDC
 * 
*/
EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay (EGLNativeDisplayType display_id);
/** 返回最近一次EGL API的调用之后的Status
 * 
*/
EGLAPI EGLint EGLAPIENTRY eglGetError (void);
/** 通用的函数指针(相当于函数指针版的void*), 用来接收eglGetProcAddress的返回值
 * 
 * return reinterpret_cast<__eglMustCastToProperFunctionPointerType>(pEglEsxIf->pfnGetProcAddress(procname));
 * 
*/
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress (const char *procname);
/** 初始化Display并返回当前实现支持的EGL版本
 * 
*/
EGLAPI EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
/**
 *  binds ctx to the current rendering thread and to the draw and read surfaces.
 * 
 * If the calling thread already has a current context of the same client API type as ctx, then that context is flushed and marked as no longer current.
*/
EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value);
/**
 * name may be one of EGL_CLIENT_APIS, EGL_EXTENSIONS, EGL_VENDOR, or EGL_VERSION.
*/
EGLAPI const char *EGLAPIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
/**
 * EGL_CONFIG_ID        
 * the ID of the EGLConfig with respect to which the surface was created
 * 
 * EGL_GL_COLORSPACE
 * 
 * EGL_HEIGHT, EGL_WIDTH, EGL_HORIZONTAL_RESOLUTION, EGL_VERTICAL_RESOLUTION, EGL_PIXEL_ASPECT_RATIO
 * 
 * EGL_LARGEST_PBUFFER
 * a pbuffer surface returns the same attribute value specified when the surface was created with eglCreatePbufferSurface. 
 * For a window or pixmap surface, the contents of value are not modified)
 * 
 * 
 * EGL_MULTISAMPLE_RESOLVE // EGL_VERSION_1_4
 * the filtering method used when performing multisammple buffer resolution. 
 * MULTISAMPLE_RESOLVE_DEFAULT, EGL_MULTISAMPLE_RESOLVE_BOX
 * 
 * EGL_RENDER_BUFFER
 * the buffer which client API rendering is requested to use. For a window surface, this is the same attribute value specified 
 * when the surface was created. For a pbuffer surface, it is always EGL_BACK_BUFFER. For a pixmap surface, it is always EGL_SINGLE_BUFFER.
 * 
 * EGL_SWAP_BEHAVIOR
 * the effect on the color buffer when posting a surface with eglSwapBuffers
 * EGL_BUFFER_PRESERVED,EGL_BUFFER_DESTROYED
 * 
 * EGL_TEXTURE_FORMAT
 * Format of texture: RGB, RGBA, or no texture
 * 
 * EGL_TEXTURE_TARGET
 * Type of texture: 2D or no texture
 * 
 * EGL_MIPMAP_TEXTURE
 * if texture has mipmaps
 * 
 * EGL_MIPMAP_LEVEL
 * Mipmap level to render to
*/
EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value);
/**
 * 
 * Will perform an implicit flush operation on the context
 * 
 * If surface is a back-buffered window surface, then the color buffer is copied to the native window associated with that surface. 
 * If surface is a single-buffered window, pixmap, or pbuffer surface, eglSwapBuffers has no effect.
 * 
 * The contents of ancillary buffers are always undefined after calling eglSwapBuffers. The contents of the color buffer are undefined if the value of 
 * the EGL_SWAP_BEHAVIOR attribute of surface is not EGL_BUFFER_PRESERVED
*/
EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers (EGLDisplay dpy, EGLSurface surface);
/**
 * Termination marks all EGL-specific resources, such as contexts and surfaces, associated with the specified display for deletion. 
 * Handles to all such resources are invalid as soon as eglTerminate returns, but the dpy handle itself remains valid.
*/
EGLAPI EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy);
/**
 * The same result can be achieved using client API-specific calls such as glFinish
*/
EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (void);
/**
 * 等待Native rendering渲染完成
 * 
 * engine denotes a particular marking engine (another drawing API, such as GDI or Xlib) to be waited on. Valid values of engine are defined by EGL extension 
 * specific to implementations, but implementations will always recognize the symbolic constant EGL_CORE_NATIVE_ENGINE, which denotes the most commonly 
 * used marking engine other then a client API.
*/
EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine);
#endif
#endif /* EGL_VERSION_1_0 */

#pragma endregion

#pragma region 1.1
/**
 * 1_1主要加入了pbuffe surface绑定为gles纹理的函数，以及eglSwapInterval
*/
#ifndef EGL_VERSION_1_1
#define EGL_VERSION_1_1 1
/**
 * which buffer of the surface will used to rendering
*/
#define EGL_BACK_BUFFER                   0x3084
/**
 * Power management events can occur asynchronously while an application is running.
 * If a power management event has occurred. The application must destroy all contexts and reinitialise client API state and objects to continue rendering
*/
#define EGL_CONTEXT_LOST                  0x300E

/**
 * Config attribute about SWAP_INTERVAL
*/
#define EGL_MIN_SWAP_INTERVAL             0x303B
#define EGL_MAX_SWAP_INTERVAL             0x303C

#define EGL_BIND_TO_TEXTURE_RGB           0x3039 // True if pbuffer is bindable to RGB textures.
#define EGL_BIND_TO_TEXTURE_RGBA          0x303A // True if pbuffer is bindable to RGBA textures.
/**
 * Used in eglCreatePbufferSurface(const EGLint* attrib_list)
 * 
 * 如果pbuffer将被绑定为gles的mipmaps纹理，需要在这里进行设置
 * indicates whether storage for OpenGL ES mipmaps should be allocated. Space for mipmaps will be set aside if the attribute value 
 * is EGL_TRUE and EGL_TEXTURE_FORMAT is not EGL_NO_TEXTURE.
*/
#define EGL_MIPMAP_TEXTURE                0x3082
/**
 * Used in eglSurfaceAttrib(EGLint attribute, EGLint value)
 * 
 * indicates which level of the OpenGL ES mipmap texture should be rendered
*/
#define EGL_MIPMAP_LEVEL                  0x3083

/**
 * Used in eglSurfaceAttrib(EGLint attribute, EGLint value)
 * 
 * specifies the target for the OpenGL ES texture that will be created. The target can be set to EGL_NO_TEXTURE or EGL_TEXTURE_2D.
*/
#define EGL_TEXTURE_TARGET                0x3081
#define EGL_NO_TEXTURE                    0x305C
#define EGL_TEXTURE_2D                    0x305F
/**
 * specifies the format of the OpenGL ES texture that will be created when a pbuffer is bound to a texture.
 * 
 * It can be set to EGL_TEXTURE_RGB, EGL_TEXTURE_RGBA, or EGL_NO_TEXTURE.
*/
#define EGL_TEXTURE_FORMAT                0x3080
#define EGL_TEXTURE_RGB                   0x305D
#define EGL_TEXTURE_RGBA                  0x305E

typedef EGLBoolean (EGLAPIENTRYP PFNEGLBINDTEXIMAGEPROC)    (EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETEXIMAGEPROC) (EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSURFACEATTRIBPROC)   (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPINTERVALPROC)    (EGLDisplay dpy, EGLint interval);
#if EGL_EGL_PROTOTYPES
/**
 * 设置Surface的属性值，与eglQuerySurface对应
 * 
 * EGL_MIPMAP_LEVEL 
 * indicates which level of theOpenGL ES mipmap texture should be rendered.
 * only for pbuffer surface,if pbuffer attribute EGL_TEXTURE_FORMAT is EGL_NO_TEXTURE or attribute EGL_TEXTURE_TARGET is EGL_NO_TEXTURE, EGL_MIPMAP_LEVEL has no effect. 
 * 
 * EGL_MULTISAMPLE_RESOLVE // EGL_VERSION_1_4
 * specifies the filter to use when resolving the multisample buffer.
 * EGL_MULTISAMPLE_RESOLVE_DEFAULT chooses the default implementation-defined filtering method, 
 * EGL_MULTISAMPLE_RESOLVE_BOX chooses a one-pixel wide box filter placing equal weighting on all multisample values(the EGL_SURFACE_TYPE attribute of the EGLConfig used to create surface must contain EGL_MULTISAMPLE_RESOLVE_BOX_BIT)
 * 
 * EGL_SWAP_BEHAVIOR
 * EGL_BUFFER_PRESERVED(1.4) indicates that color buffer contents are unaffected(the EGL_SURFACE_TYPE attribute of the EGLConfig used to create surface must contain EGL_SWAP_BEHAVIOR_PRESERVED_BIT)
 * EGL_BUFFER_DESTROYED indicates that color buffer contents may be destroyed or changed by the operation.
*/
EGLAPI EGLBoolean EGLAPIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
/**
 * Bind the buffer of pbuffer surface to the gles texture.
 * 
 * buffer must be EGL_BACK_BUFFER
*/
EGLAPI EGLBoolean EGLAPIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint buffer);
/**
 * To release a buffer that is being used as a texture to the pbuffer surface.
 * 
 * The contents of the color buffer are undefined when it is first released.
 * the contents of the depth and stencil buffers are not affected by eglBindTexImage and eglReleaseTexImage
*/
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint buffer);
/**
 * Swap Interval is a means of synchronizing the swapping of the front and back frame buffers with vertical blanks (v-blank): 
 * the hardware event where the screen image is updated with data from the front framebuffer . It is a very common means of preventing frame "tearing".
 * 
 * The term "swap interval" itself refers to the number of v-blanks that must occur before the front and back frame buffers are swapped. 
 * A swap interval of 1 tells the GPU to wait for one v-blank before swapping the front and back buffers. 
 * A swap interval of 0 specifies that the GPU should never wait for v-blanks, thus performing buffer swaps as soon as possible when rendering for a frame is finished.
 * 
 * 如果swap interval大于1，则表示GPU可能会强制CPU等待v-sync信号。如果double buffering的情况下, 假设v-sync信号16.6ms发出一次(即display会使用该buffer16.6ms)
 * 如果渲染4ms就完成了， 此时CPU会阻塞在eglSwapBuffers, 等待v-sync到来(即dispaly使用完back buffer)再进行渲染。
 * 如果渲染18ms才能完成，此时display会显示两帧同样的image到屏幕上, 导致app从60fps变成30fps. 而且 GPU 需要等待 15.2ms every other v-blank interval for a buffer swap. 
 * 
 * triple buffering
 * 使用三个buffer交替渲染，当display使用back buffer时，即使GPU在很快的时间渲染完成front buffer，也可以继续渲染到middle buffer, 而不用等待back buffer.
 * 即使GPU在大于16ms的时间才能渲染完成front buffer，此时display完成了back buffer的显示，也可以去显示middle buffer，而不用等front buffer.
 * 
*/
EGLAPI EGLBoolean EGLAPIENTRY eglSwapInterval (EGLDisplay dpy, EGLint interval);
#endif
#endif /* EGL_VERSION_1_1 */

#pragma endregion

#pragma region 1.2

/**
 * 1_2主要加入了多client api的支持
*/
#ifndef EGL_VERSION_1_2
#define EGL_VERSION_1_2 1
typedef unsigned int EGLenum;
typedef void *EGLClientBuffer;
#define EGL_UNKNOWN                       EGL_CAST(EGLint,-1)
#define EGL_ALPHA_FORMAT                  0x3088 // OpenVG
#define EGL_ALPHA_FORMAT_NONPRE           0x308B // OpenVG
#define EGL_ALPHA_FORMAT_PRE              0x308C // OpenVG
#define EGL_ALPHA_MASK_SIZE               0x303E // OpenVG

#define EGL_COLORSPACE                    0x3087 // OpenVG
#define EGL_COLORSPACE_sRGB               0x3089 // OpenVG
#define EGL_COLORSPACE_LINEAR             0x308A // OpenVG
#define EGL_OPENVG_IMAGE                  0x3096 // OpenVG, used in eglCreatePbufferFromClientBuffer
/**
 * EGL_LUMINANCE_BUFFER
 * EGL_RGB_BUFFER
*/
#define EGL_COLOR_BUFFER_TYPE             0x303F
#define EGL_LUMINANCE_BUFFER              0x308F
#define EGL_LUMINANCE_SIZE                0x303D
#define EGL_RGB_BUFFER                    0x308E
/**
 * used in eglQueryContext(EGLint attribute, EGLint* value)
 * 
 * the type of client API this context supports (the value of the api parameter to eglBindAPI)
*/
#define EGL_CONTEXT_CLIENT_TYPE           0x3097
#define EGL_OPENVG_API                    0x30A1 // OpenVG
#define EGL_OPENGL_ES_API                 0x30A0
// used in eglQueryString
#define EGL_CLIENT_APIS                   0x308D
/**
 * Configs
 * 
 * a mask indicating which client APIs can render into a surface created with respect to an EGLConfig
*/
#define EGL_RENDERABLE_TYPE               0x3040
#define EGL_OPENGL_ES_BIT                 0x0001
#define EGL_OPENVG_BIT                    0x0002 // OpenVG
/**
 * used in eglQueryContext(EGLint attribute, EGLint* value)
 * 
 * EGL_SINGLE_BUFFER
 * EGL_BACK_BUFFER
*/
#define EGL_RENDER_BUFFER                 0x3086
#define EGL_SINGLE_BUFFER                 0x3085

#define EGL_SWAP_BEHAVIOR                 0x3093
#define EGL_BUFFER_PRESERVED              0x3094
#define EGL_BUFFER_DESTROYED              0x3095


#define EGL_DISPLAY_SCALING               10000
#define EGL_PIXEL_ASPECT_RATIO            0x3092
#define EGL_HORIZONTAL_RESOLUTION         0x3090
#define EGL_VERTICAL_RESOLUTION           0x3091
typedef EGLBoolean (EGLAPIENTRYP PFNEGLBINDAPIPROC) (EGLenum api);
typedef EGLenum    (EGLAPIENTRYP PFNEGLQUERYAPIPROC) (void);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC) (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLRELEASETHREADPROC) (void);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLWAITCLIENTPROC) (void);
#if EGL_EGL_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBindAPI (EGLenum api);
EGLAPI EGLenum    EGLAPIENTRY eglQueryAPI (void);
/**
 * wait the current bound api
*/
EGLAPI EGLBoolean EGLAPIENTRY eglWaitClient (void);
/**
 * EGL maintains a small amount of per-thread state, including the error status returned by eglGetError, the currently bound rendering API defined by eglBindAPI, 
 * and the current contexts for each supported client API
 * 
 * Return EGL to its state at thread initialization, only per-thread state is affected
 * 
 * Resources explicitly allocated by calls to EGL, such as contexts, surfaces, and configuration lists, are not affected by eglReleaseThread
*/
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread (void);
// Only for OpenVG
EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferFromClientBuffer (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
#endif
#endif /* EGL_VERSION_1_2 */

#pragma endregion

#pragma region 1.3

/**
 * 加入OpenGL ES2
*/
#ifndef EGL_VERSION_1_3
#define EGL_VERSION_1_3 1

#define EGL_OPENGL_ES2_BIT                0x0004

/**
 *  a mask indicating if a client API context created with the config will pass the required conformance tests for that API.
*/
#define EGL_CONFORMANT                    0x3042
/**
 * used in eglQueryContext(EGLint attribute, EGLint* value)
 * 
 * returns the version of the client API this context actually supports. Only for OpenGL ES
*/
#define EGL_CONTEXT_CLIENT_VERSION        0x3098
/**
 * used in eglChooseConfig(EGLint *attrib_list)
 * 
 * must be followed by an attribute value which is the handle of a valid native pixmap. Only EGLConfigs which support rendering to that pixmap will match this attribute
*/
#define EGL_MATCH_NATIVE_PIXMAP           0x3041

#define EGL_VG_ALPHA_FORMAT               0x3088 // OpenVG
#define EGL_VG_ALPHA_FORMAT_NONPRE        0x308B // OpenVG
#define EGL_VG_ALPHA_FORMAT_PRE           0x308C // OpenVG
#define EGL_VG_ALPHA_FORMAT_PRE_BIT       0x0040 // OpenVG
#define EGL_VG_COLORSPACE                 0x3087 // OpenVG
#define EGL_VG_COLORSPACE_sRGB            0x3089 // OpenVG
#define EGL_VG_COLORSPACE_LINEAR          0x308A // OpenVG
#define EGL_VG_COLORSPACE_LINEAR_BIT      0x0020 // OpenVG
#endif /* EGL_VERSION_1_3 */

#pragma endregion

#pragma region 1.4

/**
 * 加入OpenGL api
*/
#ifndef EGL_VERSION_1_4
#define EGL_VERSION_1_4 1
#define EGL_DEFAULT_DISPLAY               EGL_CAST(EGLNativeDisplayType,0) // 可以认为是全屏窗口
#define EGL_MULTISAMPLE_RESOLVE_BOX_BIT   0x0200
#define EGL_MULTISAMPLE_RESOLVE           0x3099
#define EGL_MULTISAMPLE_RESOLVE_DEFAULT   0x309A
#define EGL_MULTISAMPLE_RESOLVE_BOX       0x309B
#define EGL_OPENGL_API                    0x30A2
#define EGL_OPENGL_BIT                    0x0008
#define EGL_SWAP_BEHAVIOR_PRESERVED_BIT   0x0400
typedef EGLContext (EGLAPIENTRYP PFNEGLGETCURRENTCONTEXTPROC) (void);
#if EGL_EGL_PROTOTYPES
EGLAPI EGLContext EGLAPIENTRY eglGetCurrentContext (void);
#endif
#endif /* EGL_VERSION_1_4 */

#pragma endregion

#pragma region 1.5

/**
 * 1_5加入sync对象和EGLImage, OPENGL_ES3
*/
#ifndef EGL_VERSION_1_5
#define EGL_VERSION_1_5 1
typedef void *EGLSync;
typedef intptr_t EGLAttrib;
typedef khronos_utime_nanoseconds_t EGLTime;
typedef void *EGLImage;

/**
 * OpenGL ES3
*/
#define EGL_OPENGL_ES3_BIT                0x00000040

/**
 * OpenGL
*/
#define EGL_CONTEXT_MAJOR_VERSION         0x3098
#define EGL_CONTEXT_MINOR_VERSION         0x30FB
#define EGL_CONTEXT_OPENGL_PROFILE_MASK   0x30FD
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#define EGL_CONTEXT_OPENGL_DEBUG          0x31B0
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS  0x31B2
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#define EGL_NO_RESET_NOTIFICATION         0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET         0x31BF

/**
 * EGLSync
*/
#define EGL_NO_SYNC                       EGL_CAST(EGLSync,0)
#define EGL_CL_EVENT_HANDLE               0x309C
#define EGL_SYNC_CL_EVENT                 0x30FE
#define EGL_SYNC_CL_EVENT_COMPLETE        0x30FF
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE  0x30F0
#define EGL_SYNC_TYPE                     0x30F7
#define EGL_SYNC_STATUS                   0x30F1
#define EGL_SYNC_CONDITION                0x30F8
#define EGL_SYNC_FENCE                    0x30F9
#define EGL_SIGNALED                      0x30F2
#define EGL_UNSIGNALED                    0x30F3
#define EGL_SYNC_FLUSH_COMMANDS_BIT       0x0001
#define EGL_FOREVER                       0xFFFFFFFFFFFFFFFFull
#define EGL_TIMEOUT_EXPIRED               0x30F5
#define EGL_CONDITION_SATISFIED           0x30F6

/**
 * EGLImage
*/
#define EGL_GL_COLORSPACE                 0x309D
#define EGL_GL_COLORSPACE_SRGB            0x3089
#define EGL_GL_COLORSPACE_LINEAR          0x308A
#define EGL_GL_RENDERBUFFER               0x30B9
#define EGL_GL_TEXTURE_2D                 0x30B1
#define EGL_GL_TEXTURE_LEVEL              0x30BC
#define EGL_GL_TEXTURE_3D                 0x30B2
#define EGL_GL_TEXTURE_ZOFFSET            0x30BD
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x30B3
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x30B5
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x30B7
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#define EGL_IMAGE_PRESERVED               0x30D2
#define EGL_NO_IMAGE                      EGL_CAST(EGLImage,0)
typedef EGLSync    (EGLAPIENTRYP PFNEGLCREATESYNCPROC)      (EGLDisplay dpy, EGLenum type, const EGLAttrib *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYSYNCPROC)     (EGLDisplay dpy, EGLSync sync);
typedef EGLint     (EGLAPIENTRYP PFNEGLCLIENTWAITSYNCPROC)  (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETSYNCATTRIBPROC)   (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLWAITSYNCPROC)        (EGLDisplay dpy, EGLSync sync, EGLint flags);
typedef EGLImage   (EGLAPIENTRYP PFNEGLCREATEIMAGEPROC)     (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEPROC)    (EGLDisplay dpy, EGLImage image);
typedef EGLDisplay (EGLAPIENTRYP PFNEGLGETPLATFORMDISPLAYPROC)          (EGLenum platform, void *native_display, const EGLAttrib *attrib_list);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMWINDOWSURFACEPROC) (EGLDisplay dpy, EGLConfig config, void *native_window, const EGLAttrib *attrib_list);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC) (EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLAttrib *attrib_list);
#if EGL_EGL_PROTOTYPES
/**
 * @brief creates a sync object of the specified type
 * Creation of fence sync objects requires support from the bound client API(OpenGL ES 3.0+ or GL_OES_EGL_sync/ OpenGL3.2+ or GL_ARB_sync)
 * 
 * 
 * @param type
 * EGL_SYNC_FENCE
 *      Attributes
 *      EGL_SYNC_TYPE, EGL_SYNC_FENCE by default
 *      EGL_SYNC_STATUS, EGL_UNSIGNALED by default
 *      EGL_SYNC_CONDITION, EGL_SYNC_PRIOR_COMMANDS_COMPLETE only
 * 
 * EGL_SYNC_CL_EVENT
 *      Attributes
 *      EGL_SYNC_TYPE, EGL_SYNC_CL_EVENT by default
 *      EGL_SYNC_STATUS, Depends on status of event(CL_QUEUED, CL_SUBMITTED, CL_RUNNING, orCL_COMPLETE)
 *      EGL_SYNC_CONDITION, EGL_SYNC_CL_EVENT_COMPLETE only
 * 
 * @param attrib_list
 * attrib list is an attribute-value list specifying other attributes of the sync object
 * 
 * attrib_list must be NULL or empty for EGL_SYNC_FENCE.
 * attrib_list must contain the attribute EGL_CL_EVENT_HANDLE, set to a valid OpenCL event handle returned by a call to 
 * clEnqueueReleaseGLObjects or clEnqueueReleaseEGLObjects for EGL_SYNC_CL_EVENT.
*/
EGLAPI EGLSync    EGLAPIENTRY eglCreateSync     (EGLDisplay dpy, EGLenum type, const EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroySync    (EGLDisplay dpy, EGLSync sync);
/**
 * @brief blocks the calling thread until the specified sync object sync is signaled, or until timeout nanoseconds have passed.
 * 
 * @param flags
 * EGL_SYNC_FLUSH_COMMANDS_BIT
 * if the sync is unsignaled when eglClientWaitSync is called, then the equivalent of Flush() will be performed for the current API context before blocking on sync.
 * 
*/
EGLAPI EGLint     EGLAPIENTRY eglClientWaitSync (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
/**
 * @brief similar to eglClientWaitSync, but instead of blocking and not returning to the application until sync is signaled, eglWaitSync returns immediately
 * 
 * @param flags
 * flags must be 0.
*/
EGLAPI EGLBoolean EGLAPIENTRY eglWaitSync       (EGLDisplay dpy, EGLSync sync, EGLint flags);
EGLAPI EGLBoolean EGLAPIENTRY eglGetSyncAttrib  (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib *value);

/**
 * @brief create an EGLImage from an existing image resource buffer.
 * 1.5之前由扩展EGL_KHR_image_base提供该功能
 * 
 * @param target
 * target specifies the type of resource being used as the EGLImage source
 * 
 * EGL_GL_TEXTURE_2D
 * buffer must be the GL_TEXTURE_2D target texture object
 * 
 * EGL_GL_TEXTURE_CUBE_MAP_*
 * buffer must be the GL_TEXTURE_CUBE_MAP target texture object
 * 
 * EGL_GL_TEXTURE_3D
 * buffer must be the GL_TEXTURE_3D target texture object
 * 
 * EGL_GL_RENDERBUFFER
 * buffer must be the GL_RENDER_BUFFER target object
 * 
 * @param attrib list
 * EGL_GL_TEXTURE_LEVEL
 * Specifies the mipmap level used as the EGLImage source. Must be part of the complete texture object buffer
 * 
 * EGL_GL_TEXTURE_ZOFFSET
 * Specifies the depth offset of the image to use as the EGLImage source.
 * 
 * EGL_IMAGE_PRESERVED
 * Whether to preserve buffer pixel data
*/
EGLAPI EGLImage   EGLAPIENTRY eglCreateImage    (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImage   (EGLDisplay dpy, EGLImage image);

/**
 * Compared to 
 * eglGetDisplay          (                                  EGLNativeDisplayType display                               ); // HDC
 * eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType  pixmap,     const EGLint *attrib_list ); // HPIXELMAP
 * eglCreateWindowSurface (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType  win,        const EGLint *attrib_list ); // HWND
 * 
 * 使用下面的函数需要由platform相关的扩展提供(X11, gbm, win32 ...)
 * eglExtensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
 * 
 * // 如果定义了X11 Platform扩展
 * if (eglExtensions && containsExtension("EGL_EXT_platform_x11", eglExtensions)) {
 *      Attributes<EGLint> attribs;
 *      attribs.add(EGL_PLATFORM_X11_SCREEN_EXT, screen);
 *      attribs.add(EGL_NONE);
 *      
 *      // 获取X11的Display
 *      eglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_X11_EXT, display, attribs);
 * }
 * 
 * // 如果定义了MESA gbm扩展
 * if (eglExtensions && containsExtension("EGL_MESA_platform_gbm", eglExtensions)) {
 *      int fd = open("/dev/dri/renderD128", O_RDWR);
 *      struct gbm_device *gbm = gbm_create_device(fd);
 *      
 *      // 获取GBM_MESA的Display
 *      eglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_GBM_MESA,gbm, NULL);
 * }
*/
EGLAPI EGLDisplay EGLAPIENTRY eglGetPlatformDisplay          (EGLenum platform, void *native_display, const EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformWindowSurface (EGLDisplay dpy, EGLConfig config, void *native_window, const EGLAttrib *attrib_list);
EGLAPI EGLSurface EGLAPIENTRY eglCreatePlatformPixmapSurface (EGLDisplay dpy, EGLConfig config, void *native_pixmap, const EGLAttrib *attrib_list);
#endif
#endif /* EGL_VERSION_1_5 */

#pragma endregion

#ifdef __cplusplus
}
#endif

#endif