/*
 * http://www.songho.ca/opengl/gl_pbo.html
*/


/*
The main advantage of PBO is fast pixel data transfer to and from a graphics card through DMA (Direct Memory Access) without involing CPU cycles.

 And, the other advantage of PBO is asynchronous DMA transfer.

 There are 2 major PBO approaches to improve the performance of the pixel data transfer: streaming texture update and asynchronous read-back from the framebuffer.
*/


/*
GL_PIXEL_PACK_BUFFER is for transferring pixel data from OpenGL to your application, and GL_PIXEL_UNPACK_BUFFER means transferring pixel data from an application to OpenGL

OpenGL refers to these tokens to determine the best memory space of a PBO, for example, a video memory for uploading (unpacking) textures, or system memory for reading (packing) the framebuffer.

GL_STREAM_DRAW is for streaming texture upload and GL_STREAM_READ is for asynchronous framebuffer read-back.
*/