#include "texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define __STDC_LIB_EXT1__
#include "stb/stb_image_write.h"

#include "filesystem.h"


void Texture2D::FromPBO(const char* path, bool flip)
    {
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;

        stbi_set_flip_vertically_on_load(flip); // tell stb_image.h to flip loaded texture's on the y-axis.

        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {   
            int imgByteSize = width * height * nrChannels;

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            unsigned int uploadPboId;
            glGenBuffers(1, &uploadPboId);
            // 绑定pbo
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, uploadPboId);
            // 设置pbo内存大小
            // 这一步十分重要，第2个参数指定了这个缓冲区的大小，单位是字节，一定要注意
            //  然后第3个参数是初始化用的数据，如果你传个内存指针进去，这个函数就会把你的
            //  数据复制到缓冲区里，我们这里一开始并不需要什么数据，所以传个nullptr就行了
            glBufferData(GL_PIXEL_UNPACK_BUFFER, imgByteSize, nullptr, GL_STREAM_DRAW);

            // 将纹理数据拷贝进入缓冲区
            GLubyte *bufPtr = (GLubyte *) glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0,
                                                        imgByteSize,
                                                        GL_MAP_WRITE_BIT);
            if (bufPtr) {
                memcpy(bufPtr, data, static_cast<size_t>(imgByteSize));
                glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
            }


            switch (nrChannels)
            {
            case 4:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                glGenerateMipmap(GL_TEXTURE_2D);

                // 将pbo缓冲区中的数据拷贝到纹理，调用 glTexSubImage2D 后立即返回，不影响 CPU 时钟周期
                // 这个函数会判断 GL_PIXEL_UNPACK_BUFFER 这个地方有没有绑定一个缓冲区
                //   如果有，就从这个缓冲区读取数据，而不是data参数指定的那个内存
                // 这样glTexSubImage2D就会从我们的缓冲区中读取数据了
                // 这里为什么要用glTexSubImage2D呢，因为如果用glTexImage2D，glTexImage2D会销毁纹理内存重新申请，glTexSubImage2D就仅仅只是更新纹理中的数据，这就提高了速度，并且优化了显存的利用率
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

                break;
            case 3:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
                break;
            
            default:
                break;
            }

            // Pbo解除
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
            // 解绑定
            glBindTexture(GL_TEXTURE_2D, 0);


            { // 纹理数据每帧变化时，可以使用两个PBO交替上传不同的纹理渲染
                // if(pboMode == 1)
                // {
                //     // In single PBO mode, the index and nextIndex are set to 0
                //     index = nextIndex = 0;
                // }
                // else if(pboMode == 2)
                // {
                //     // In dual PBO mode, increment current index first then get the next index
                //     index = (index + 1) % 2;
                //     nextIndex = (index + 1) % 2;
                // }

                // // start to modify pixel values ///////////////////
                // t1.start();

                // // bind PBO to update pixel values
                // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[index]);

                // // map the buffer object into client's memory
                // // Note that glMapBuffer() causes sync issue.
                // // If GPU is working with this buffer, glMapBuffer() will wait(stall)
                // // for GPU to finish its job. To avoid waiting (stall), you can call
                // // first glBufferData() with NULL pointer before glMapBuffer().
                // // If you do that, the previous data in PBO will be discarded and
                // // glMapBuffer() returns a new allocated pointer immediately
                // // even if GPU is still working with the previous data.
                // glBufferData(GL_PIXEL_UNPACK_BUFFER, DATA_SIZE, 0, GL_STREAM_DRAW);
                // GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
                // if(ptr)
                // {
                //     // update data directly on the mapped buffer
                //     updatePixels(ptr, DATA_SIZE);
                //     glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
                // }

                // // measure the time modifying the mapped buffer
                // t1.stop();
                // ///////////////////////////////////////////////////

                // // start to copy from PBO to texture object ///////
                // t1.start();

                // // bind the texture and PBO
                // glBindTexture(GL_TEXTURE_2D, textureId);
                // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[nextIndex]);

                // // copy pixels from PBO to texture object
                // // Use offset instead of ponter.
                // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, PIXEL_FORMAT, GL_UNSIGNED_BYTE, 0);

                // // measure the time copying data from PBO to texture object
                // t1.stop();
                // ///////////////////////////////////////////////////

                // // it is good idea to release PBOs with ID 0 after use.
                // // Once bound with 0, all pixel operations behave normal ways.
                // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
            }
                
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    
    
    void Texture2D::FromImage(const char* path, bool flip)
    {
        // load and create a texture 
        // -------------------------
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;

        stbi_set_flip_vertically_on_load(flip); // tell stb_image.h to flip loaded texture's on the y-axis.

        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            switch (nrChannels)
            {
            case 3:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            default:
                break;
            }
            
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void Texture2D::Bind(GLenum textureUnit)
    {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture);
    }