
#ifndef EGL_ANDROID_image_native_buffer
#define EGL_ANDROID_image_native_buffer 1
#define EGL_NATIVE_BUFFER_ANDROID         0x3140
#endif /* EGL_ANDROID_image_native_buffer */

/**
 * @brief EGL_ANDROID_image_native_buffer
 * This extension enables using an Android window buffer (struct ANativeWindowBuffer), or an Android hardware buffer (struct AHardwareBuffer) as an EGLImage source.
 * 
 * 为了在andoird上实现跨进程纹理共享，可以使用AHB作为共享内存，利用该扩展，可以将该AHB绑定EGLImage，然后绑定到GLES进行渲染。
 * 
*/
void main()
{
    // Create AHardwareBuffer
    AHardwareBuffer_Desc buffDesc;
    AHardwareBuffer* hardwareBuffer;
    AHardwareBuffer_allocate(&buffDesc, &hardwareBuffer);

    // Create EGLClientBuffer
    EGLClientBuffer clientBuffer = eglGetNativeClientBufferANDROID(hardwareBuffer);

    // Create EGLImageKHR
    EGLImageKHR eglImageKHR = eglCreateImageKHR(mEGLDisplay, mEGLContext, EGL_NATIVE_BUFFER_ANDROID, clientBuffer, 0);

    // Bind the EGLImage to GLES texture
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, textureId);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, (GLeglImageOES)eglImageKHR);

    // Attach the GLES texture to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

    // Call OpenGL Draw
    glDrawArrays();

    // Call finish to make sure the content is render to HardwareBuffer.
    glFinish();
}