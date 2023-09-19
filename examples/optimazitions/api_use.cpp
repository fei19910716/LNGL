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