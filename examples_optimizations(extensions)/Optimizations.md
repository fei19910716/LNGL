/** 1, set damage region 只更新部分区域
 * 
 *      the general way to use OpenGL is to draw everything you need to draw, then show this image with a platform-dependent buffer 
 * swapping command. If you need to update the image, you draw everything again, even if you only need to update part of the image. 
 * If you want to animate objects moving on the screen, you need a loop that constantly clears and redraws the screen.
 * 
 *      There are techniques for only updating a portion of the screen. And you can use OpenGL with these techniques. But OpenGL itself doesn't 
 * do it internally; you must remember where you drew everything. You must figure out what needs updating and clear only that part of the 
 * screen.
*/



/** 2, GL_MAP_WRITE_BIT来更新buffer数据
 * 
 * avoid use glBufferData(NULL), which will reallocate the buffer storage.
 * 
 * mapping a buffer and writing to it will be equally as efficient as glBufferSubData. And in most cases, it will be much faster, 
 * particularly if invalidation and other Buffer Object Streaming techniques are employed.
 * 
 * To cover this, flags​ should be set to GL_MAP_WRITE_BIT. This lets the implementation know that you will not be using glBufferSubData at all.
*/



/** Buffer Object Streaming https://www.khronos.org/opengl/wiki/Buffer_Object_Streaming
 * 
 * Streaming is a modify/use cycle.
 * 
 * the OpenGL specification requires that the thread halt until all drawing commands that could be affected by your 
 * update of the buffer object complete.
 * 
 * This implicit synchronization is the primary enemy when streaming vertex data.
 * 
 *  1, Explicit multiple buffering(创建多个buffer进行swap per frame, 会有state change harm)
 *  2, Buffer re-specification(重新创建一个内存)
 *      glBufferData(NULL)
 *      glInvalidateBufferData()
 *  3, Persistent mapped streaming(创建一个3 sections的buffer, 每帧更新其中一个section)
*/


/** PBOs are primarily a performance optimization. 
 * 
 * In particular, PBOs are a way to improve asynchronous behavior between the application and OpenGL.
 * 
*/


/** 1, Culling
 * 
*/
    /** 1.1, frustrum culling
     * + AABB
    */

    /** 2.1, occlusion culling
     *  + AABB + conditional rendering
    */

    /** 1.3, early-z, pre-z, lrz
     * 
    */

/***/


/** 3, LOD(model,texture,shader)
 * 
 *  + quad tree
*/


/** 5，Avoid context state change
 *      
*/
    /** 5.1, instancing
     * 
    */

    /** 5.2, batch
     * 
    */

/***/


/**
 *  4, GPU driven pipeline
    /** 4.1, transform feedback buffer
     * 
    */

    /** 4.2, compute shader
     * 
    */

    /** 4.3, opencl
     * 
    */


static const CHAR ExtensionStrings[EsxExtensionCount][MaxExtStringLength] =
{
    "GL_OES_EGL_image",
    "GL_OES_EGL_image_external",
    "GL_OES_EGL_sync",
    "GL_OES_vertex_half_float",
    "GL_OES_framebuffer_object",
    "GL_OES_rgb8_rgba8",
    "GL_OES_compressed_ETC1_RGB8_texture",
    "GL_AMD_compressed_ATC_texture",
    "GL_KHR_texture_compression_astc_sliced_3d",
    "GL_KHR_texture_compression_astc_ldr",
    "GL_KHR_texture_compression_astc_hdr",
    "GL_OES_texture_compression_astc",
    "GL_EXT_texture_compression_s3tc",
    "GL_EXT_texture_compression_s3tc_srgb",
    "GL_EXT_texture_compression_rgtc",
    "GL_EXT_texture_compression_bptc",
    "GL_OES_texture_npot",
    "GL_EXT_texture_filter_anisotropic",
    "GL_EXT_texture_format_BGRA8888",
    "GL_EXT_read_format_bgra",
    "GL_OES_texture_3D",
    "GL_EXT_color_buffer_float",
    "GL_EXT_color_buffer_half_float",
    "GL_EXT_float_blend",
    "GL_QCOM_alpha_test",
    "GL_OES_depth24",
    "GL_OES_packed_depth_stencil",
    "GL_OES_depth_texture",
    "GL_OES_depth_texture_cube_map",
    "GL_EXT_sRGB",
    "GL_OES_texture_float",
    "GL_OES_texture_float_linear",
    "GL_OES_texture_half_float",
    "GL_OES_texture_half_float_linear",
    "GL_EXT_texture_type_2_10_10_10_REV",
    "GL_QCOM_rg_texture_support",
    "GL_EXT_texture_sRGB_decode",
    "GL_EXT_texture_compression_astc_decode_mode",
    "GL_EXT_texture_mirror_clamp_to_edge",
    "GL_EXT_texture_format_sRGB_override",
    "GL_OES_element_index_uint",
    "GL_EXT_copy_image",
    "GL_EXT_geometry_shader",
    "GL_EXT_tessellation_shader",
    "GL_EXT_geometry_shader_point_size",
    "GL_EXT_tessellation_shader_point_size",
    "GL_OES_texture_stencil8",
    "GL_EXT_shader_io_blocks",
    "GL_OES_shader_image_atomic",
    "GL_OES_sample_variables",
    "GL_EXT_texture_border_clamp",
    "GL_EXT_EGL_image_external_wrap_modes",
    "GL_EXT_multisampled_render_to_texture",
    "GL_EXT_multisampled_render_to_texture2",
    "GL_OES_shader_multisample_interpolation",
    "GL_EXT_texture_cube_map_array",
    "GL_EXT_draw_buffers_indexed",
    "GL_EXT_gpu_shader5",
    "GL_EXT_robustness",
    "GL_KHR_robust_gpu_timeout",
    "GL_EXT_texture_buffer",
    "GL_EXT_shader_framebuffer_fetch",
    "GL_ARM_shader_framebuffer_fetch_depth_stencil",
    "GL_OES_texture_storage_multisample_2d_array",
    "GL_OES_sample_shading",
    "GL_OES_get_program_binary",
    "GL_EXT_debug_label",
    "GL_KHR_blend_equation_advanced",
    "GL_KHR_blend_equation_advanced_coherent",
    "GL_QCOM_tiled_rendering",
    "GL_ANDROID_extension_pack_es31a",
    "GL_EXT_primitive_bounding_box",
    "GL_OES_standard_derivatives",
    "GL_OES_vertex_array_object",
    "GL_EXT_disjoint_timer_query",
    "GL_KHR_debug",
    "GL_EXT_YUV_target",
    "GL_EXT_sRGB_write_control",
    "GL_EXT_texture_norm16",
    "GL_EXT_discard_framebuffer",
    "GL_OES_surfaceless_context",
    "GL_OVR_multiview",
    "GL_OVR_multiview2",
    "GL_EXT_texture_sRGB_R8",
    "GL_KHR_no_error",
    "GL_EXT_debug_marker",
    "GL_OES_EGL_image_external_essl3",
    "GL_OVR_multiview_multisampled_render_to_texture",
    "GL_EXT_buffer_storage",
    "GL_EXT_external_buffer",
    "GL_EXT_blit_framebuffer_params",
    "GL_EXT_clip_cull_distance",
    "GL_EXT_protected_textures",
    "GL_EXT_shader_non_constant_global_initializers",
    "GL_QCOM_texture_foveated",
    "GL_QCOM_texture_foveated2",
    "GL_QCOM_texture_foveated_subsampled_layout",
    "GL_QCOM_shader_framebuffer_fetch_noncoherent",
    "GL_QCOM_shader_framebuffer_fetch_rate",
    "GL_EXT_memory_object",
    "GL_EXT_memory_object_fd",
    "GL_EXT_EGL_image_array",
    "GL_NV_shader_noperspective_interpolation",
    "GL_KHR_robust_buffer_access_behavior",
    "GL_EXT_EGL_image_storage",
    "GL_EXT_blend_func_extended",
    "GL_EXT_clip_control",
    "GL_OES_texture_view",
    "GL_EXT_fragment_invocation_density",
    "GL_QCOM_motion_estimation",
    "GL_QCOM_validate_shader_binary",
    "GL_QCOM_YUV_texture_gather",
    "GL_QCOM_shading_rate",
    "GL_QCOM_frame_extrapolation",
    "GL_IMG_texture_filter_cubic",
    "GL_QCOM_render_shared_exponent",
    "GL_EXT_polygon_offset_clamp",
    "GL_EXT_texture_sRGB_RG8",
    "GL_EXT_depth_clamp",
    "GL_EXT_fragment_shading_rate",
    "GL_EXT_fragment_shading_rate_primitive",
    "GL_EXT_fragment_shading_rate_attachment",
    "GL_EXT_shader_implicit_conversions",
    "GL_EXT_texture_storage_compression",
    "GL_EXT_render_snorm",
};


static const CHAR EglExtensionStrings[EglExtensionCount][MaxEglExtStringLength] =
{
    "EGL_KHR_image",
    "EGL_KHR_image_base",
    "EGL_QCOM_create_image",
    "EGL_KHR_lock_surface",
    "EGL_KHR_lock_surface2",
    "EGL_KHR_lock_surface3",
    "EGL_KHR_gl_texture_2D_image",
    "EGL_KHR_gl_texture_cubemap_image",
    "EGL_KHR_gl_texture_3D_image",
    "EGL_KHR_gl_renderbuffer_image",
    "EGL_ANDROID_blob_cache",
    "EGL_KHR_create_context",
    "EGL_KHR_surfaceless_context",
    "EGL_KHR_create_context_no_error",
    "EGL_EXT_buffer_age",
    "EGL_KHR_get_all_proc_addresses",
    "EGL_QCOM_lock_image2",
    "EGL_EXT_protected_content",
    "EGL_KHR_no_config_context",
    "EGL_EXT_surface_SMPTE2086_metadata",
    "EGL_QCOM_swap_buffers_with_CRC_region",
};