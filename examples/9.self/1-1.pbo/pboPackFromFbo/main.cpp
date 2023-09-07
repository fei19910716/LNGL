///////////////////////////////////////////////////////////////////////////////
// main.cpp
// ========
// testing Frame Buffer Object (FBO) and Pixel Buffer Object (PBO) together
//
// GL_EXT_framebuffer_object extension is promoted to a core feature of OpenGL
// version 3.0 (GL_ARB_framebuffer_object)
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2008-05-16
// UPDATED: 2023-04-06
///////////////////////////////////////////////////////////////////////////////

// in order to get function prototypes from glext.h, define GL_GLEXT_PROTOTYPES before including glext.h
#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "glext.h"
#include "glExtension.h"                // OpenGL extension helper
#include "Timer.h"
#include "teapot.h"                     // contains teapot geom and drawTeapot()
#include "Bmp.h"

using std::stringstream;
using std::string;
using std::cout;
using std::endl;
using std::ends;


// GLUT CALLBACK functions ////////////////////////////////////////////////////
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
void idleCB();
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);

// CALLBACK function when exit() called ///////////////////////////////////////
void exitCB();

// function declearations /////////////////////////////////////////////////////
void initGL();
int  initGLUT(int argc, char **argv);
bool initSharedMem();
void clearSharedMem();
void initLights();
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void drawString(const char *str, int x, int y, float color[4], void *font);
void drawString3D(const char *str, float pos[3], float color[4], void *font);
void showInfo();
void showTransferRate();
void printTransferRate();
void add(unsigned char* src, int width, int height, int shift, unsigned char* dst);
void toOrtho();
void toPerspective();

// FBO utils
bool checkFramebufferStatus(GLuint fbo);
void printFramebufferInfo(GLuint fbo);
std::string convertInternalFormatToString(GLenum format);
std::string getTextureParameters(GLuint id);
std::string getRenderbufferParameters(GLuint id);


// constants
const int   TEXTURE_WIDTH    = 512;
const int   TEXTURE_HEIGHT   = 512;
const float CAMERA_DISTANCE = 6.0f;
const int   TEXT_WIDTH      = 8;
const int   TEXT_HEIGHT     = 13;
const int   CHANNEL_COUNT = 4;
const int   DATA_SIZE = TEXTURE_WIDTH * TEXTURE_HEIGHT * CHANNEL_COUNT;
const GLenum PIXEL_FORMAT = GL_RGBA;

// global variables
GLuint fboId;                       // ID of FBO
GLuint pboIds[2];                   // IDs of PBOs
GLuint texId;                   // ID of texture
GLuint rboColorId, rboDepthId;      // IDs of Renderbuffer objects
void *font = GLUT_BITMAP_8_BY_13;
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;
bool fboSupported;
bool fboUsed;
int fboSampleCount;
bool pboSupported;
bool pboUsed;
int drawMode;
Timer timer, t1, t2;
GLubyte* colorBuffer = 0;           // to store frame data
float readTime, processTime;



///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    // init global vars
    initSharedMem();

    // register exit callback
    atexit(exitCB);

    // init GLUT and GL
    initGLUT(argc, argv);
    initGL();

    // create a texture object
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // check OpenGL extensions
    glExtension& ext = glExtension::getInstance();
    if(ext.isSupported("GL_ARB_framebuffer_object"))
    {
        fboSupported = fboUsed = true;
        std::cout << "Video card supports GL_ARB_framebuffer_object." << std::endl;
    }
    else
    {
        fboSupported = fboUsed = false;
        std::cout << "Video card does NOT support GL_ARB_framebuffer_object." << std::endl;
    }

    if(ext.isSupported("GL_ARB_multisample"))
    {
        std::cout << "Video card supports GL_ARB_multisample." << std::endl;
    }
    else
    {
        std::cout << "Video card does NOT support GL_ARB_multisample." << std::endl;
    }

    if(ext.isSupported("GL_ARB_texture_multisample"))
    {
        std::cout << "Video card supports GL_ARB_texture_multisample." << std::endl;
    }
    else
    {
        std::cout << "Video card does NOT support GL_ARB_texture_multisample." << std::endl;
    }

    if(ext.isSupported("GL_ARB_pixel_buffer_object"))
    {
        pboSupported = pboUsed = true;
        std::cout << "Video card supports GL_ARB_pixel_buffer_object." << std::endl;
    }
    else
    {
        pboSupported = pboUsed = false;
        std::cout << "Video card does NOT supports GL_ARB_pixel_buffer_object." << std::endl;
    }

#ifdef _WIN32
    if(ext.isSupported("WGL_EXT_swap_control"))
    {
        // disable v-sync
        wglSwapIntervalEXT(0);
        std::cout << "Video card supports WGL_EXT_swap_control." << std::endl;
    }
#endif

    if(fboSupported)
    {
        // create a framebuffer object, you need to delete them when program exits.
        glGenFramebuffers(1, &fboId);
        glBindFramebuffer(GL_FRAMEBUFFER, fboId);

        // create a renderbuffer object to store depth info
        // NOTE: A depth renderable image should be attached the FBO for depth test.
        // If we don't attach a depth renderable image to the FBO, then
        // the rendering output will be corrupted because of missing depth test.
        // If you also need stencil test for your rendering, then you must
        // attach additional image to the stencil attachement point, too.
        glGenRenderbuffers(1, &rboDepthId);

        glBindRenderbuffer(GL_RENDERBUFFER, rboDepthId);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, TEXTURE_WIDTH, TEXTURE_HEIGHT);
        //glRenderbufferStorageMultisample(GL_RENDERBUFFER, fboSampleCount, GL_DEPTH_COMPONENT, TEXTURE_WIDTH, TEXTURE_HEIGHT);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // attach a texture to FBO color attachement point
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);

        // attach a renderbuffer to depth attachment point
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepthId);

        //@@ disable color buffer if you don't attach any color buffer image,
        //@@ for example, rendering the depth buffer only to a texture.
        //@@ Otherwise, glCheckFramebufferStatus will not be complete.
        //glDrawBuffer(GL_NONE);
        //glReadBuffer(GL_NONE);

        // check FBO status
        printFramebufferInfo(fboId);
        bool status = checkFramebufferStatus(fboId);
        if(!status)
            fboUsed = false;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else
    {
        std::cout << "Termination program due to FBO is NOT supported" << std::endl;
        return 0;
    }


    if(pboSupported)
    {
        // create 1 PBO, you need to delete them when program exits.
        glGenBuffers(2, pboIds);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[0]);
        glBufferData(GL_PIXEL_PACK_BUFFER, DATA_SIZE, 0, GL_STREAM_READ);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[1]);
        glBufferData(GL_PIXEL_PACK_BUFFER, DATA_SIZE, 0, GL_STREAM_READ);

        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    }
    else
    {
        std::cout << "Termination program due to PBO is NOT supported" << std::endl;
        return 0;
    }


    // start timer, the elapsed time will be used for rotating the teapot
    timer.start();

    // the last GLUT call (LOOP)
    // window will be shown and display callback is triggered by events
    // NOTE: this call never return main().
    glutMainLoop(); /* Start GLUT event-processing loop */

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv)
{
    // GLUT stuff for windowing
    // initialization openGL window.
    // It must be called before any other GLUT routine.
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

    glutInitWindowSize(TEXTURE_WIDTH*2, TEXTURE_HEIGHT);    // window size

    glutInitWindowPosition(100, 100);                           // window location

    // finally, create a window with openGL context
    // Window will not displayed until glutMainLoop() is called
    // It returns a unique ID.
    int handle = glutCreateWindow(argv[0]);     // param is the title of window

    // register GLUT callback functions
    glutDisplayFunc(displayCB);
    //glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
    glutIdleFunc(idleCB);                       // redraw whenever system is idle
    glutReshapeFunc(reshapeCB);
    glutKeyboardFunc(keyboardCB);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);

    return handle;
}



///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();
}



///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char *str, float pos[3], float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);          // set text color
    glRasterPos3fv(pos);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
    mouseLeftDown = mouseRightDown = false;
    mouseX = mouseY = 0;

    cameraAngleX = cameraAngleY = 0;
    cameraDistance = 3;

    drawMode = 0; // 0:fill, 1: wireframe, 2:points

    fboId = rboColorId = rboDepthId = texId = 0;
    pboIds[0] = pboIds[1] = 0;
    fboSupported = fboUsed = false;
    pboSupported = pboUsed = false;
    readTime = processTime = 0;

    // allocate buffers to store frames
    colorBuffer = new GLubyte[DATA_SIZE];
    memset(colorBuffer, 255, DATA_SIZE);

    return true;
}



///////////////////////////////////////////////////////////////////////////////
// clean up global variables
///////////////////////////////////////////////////////////////////////////////
void clearSharedMem()
{
    glDeleteTextures(1, &texId);
    texId = 0;

    // clean up FBO, RBO
    if(fboSupported)
    {
        glDeleteFramebuffers(1, &fboId);
        fboId = 0;
        glDeleteRenderbuffers(1, &rboDepthId);
        rboDepthId = 0;
    }

    // deallocate frame buffer
    delete [] colorBuffer;
    colorBuffer = 0;

    // clean up PBOs
    if(pboSupported)
    {
        glDeleteBuffers(2, pboIds);
        pboIds[0] = pboIds[1] = 0;
    }
}



///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void initLights()
{
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}



///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}



///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void showInfo()
{
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
    gluOrtho2D(0, TEXTURE_WIDTH, 0, TEXTURE_HEIGHT);  // set to orthogonal projection

    float color[4] = {1, 1, 1, 1};

    std::stringstream ss;
    ss << "FBO: " << (fboUsed ? "on" : "off") << std::ends;
    drawString(ss.str().c_str(), 1, TEXTURE_HEIGHT-TEXT_HEIGHT, color, font);
    ss.str(""); // clear buffer

    ss << "PBO: " << (pboUsed ? "on" : "off") << std::ends;
    drawString(ss.str().c_str(), 1, TEXTURE_HEIGHT-(2*TEXT_HEIGHT), color, font);
    ss.str(""); // clear buffer

    ss << "Read Time: " << readTime << " ms" << std::ends;
    drawString(ss.str().c_str(), 1, TEXTURE_HEIGHT-(3*TEXT_HEIGHT), color, font);
    ss.str("");

    ss << std::fixed << std::setprecision(3);
    ss << "Process Time: " << processTime << " ms" << std::ends;
    drawString(ss.str().c_str(), 1, TEXTURE_HEIGHT-(4*TEXT_HEIGHT), color, font);
    ss.str("");

    ss << "Press S key to save screenshot." << std::ends;
    drawString(ss.str().c_str(), 1, TEXT_HEIGHT+1, color, font);
    ss.str("");

    ss << "Press SPACE to toggle PBO." << std::ends;
    drawString(ss.str().c_str(), 1, 1, color, font);

    // unset floating format
    ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}



///////////////////////////////////////////////////////////////////////////////
// display transfer rates
///////////////////////////////////////////////////////////////////////////////
void showTransferRate()
{
    static Timer timer;
    static int count = 0;
    static std::stringstream ss;

    // update fps every second
    ++count;
    double elapsedTime = timer.getElapsedTime();
    if(elapsedTime > 1.0)
    {
        ss.str("");
        ss << std::fixed << std::setprecision(1);
        ss << "Transfer Rate: " << (count / elapsedTime) * (TEXTURE_WIDTH * TEXTURE_HEIGHT) / (1024 * 1024) << " Mp" << std::ends; // update fps string
        ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
        count = 0;                      // reset counter
        timer.start();                  // restart timer
    }

    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
    gluOrtho2D(0, TEXTURE_WIDTH, 0, TEXTURE_HEIGHT); // set to orthogonal projection

    float color[4] = {1, 1, 0, 1};
    drawString(ss.str().c_str(), 200, 286, color, font);

    // restore projection matrix
    glPopMatrix();                      // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);         // switch to modelview matrix
    glPopMatrix();                      // restore to previous modelview matrix
}



///////////////////////////////////////////////////////////////////////////////
// print transfer rates
///////////////////////////////////////////////////////////////////////////////
void printTransferRate()
{
    const double INV_MEGA = 1.0 / (1024 * 1024);
    static Timer timer;
    static int count = 0;
    static std::stringstream ss;
    double elapsedTime;

    // loop until 1 sec passed
    elapsedTime = timer.getElapsedTime();
    if(elapsedTime < 1.0)
    {
        ++count;
    }
    else
    {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "Transfer Rate: " << (count / elapsedTime) * (TEXTURE_WIDTH * TEXTURE_HEIGHT) * INV_MEGA << " Mpixels/s. (" << count / elapsedTime << " FPS)\n";
        std::cout << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
        count = 0;                      // reset counter
        timer.start();                  // restart timer
    }
}


///////////////////////////////////////////////////////////////////////////////
// change the brightness
///////////////////////////////////////////////////////////////////////////////
void add(unsigned char* src, int width, int height, int shift, unsigned char* dst)
{
    if(!src || !dst)
        return;

    int value;
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            value = *src + shift;
            if(value > 255) *dst = (unsigned char)255;
            else            *dst = (unsigned char)value;
            ++src;
            ++dst;

            value = *src + shift;
            if(value > 255) *dst = (unsigned char)255;
            else            *dst = (unsigned char)value;
            ++src;
            ++dst;

            value = *src + shift;
            if(value > 255) *dst = (unsigned char)255;
            else            *dst = (unsigned char)value;
            ++src;
            ++dst;

            ++src;    // skip alpha
            ++dst;
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// check FBO completeness
///////////////////////////////////////////////////////////////////////////////
bool checkFramebufferStatus(GLuint fbo)
{
    // check FBO status
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); // bind
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE:
        std::cout << "Framebuffer complete." << std::endl;
        return true;

    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        std::cout << "[ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        std::cout << "[ERROR] Framebuffer incomplete: No image is attached to FBO." << std::endl;
        return false;
/*
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
        std::cout << "[ERROR] Framebuffer incomplete: Attached images have different dimensions." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
        std::cout << "[ERROR] Framebuffer incomplete: Color attached images have different internal formats." << std::endl;
        return false;
*/
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        std::cout << "[ERROR] Framebuffer incomplete: Draw buffer." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        std::cout << "[ERROR] Framebuffer incomplete: Read buffer." << std::endl;
        return false;

    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        std::cout << "[ERROR] Framebuffer incomplete: Multisample." << std::endl;
        return false;

    case GL_FRAMEBUFFER_UNSUPPORTED:
        std::cout << "[ERROR] Framebuffer incomplete: Unsupported by FBO implementation." << std::endl;
        return false;

    default:
        std::cout << "[ERROR] Framebuffer incomplete: Unknown error." << std::endl;
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // unbind
}



///////////////////////////////////////////////////////////////////////////////
// print out the FBO infos
///////////////////////////////////////////////////////////////////////////////
void printFramebufferInfo(GLuint fbo)
{
    // bind fbo
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    std::cout << "\n===== FBO STATUS =====\n";

    // print max # of colorbuffers supported by FBO
    int colorBufferCount = 0;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &colorBufferCount);
    std::cout << "Max Number of Color Buffer Attachment Points: " << colorBufferCount << std::endl;

    // get max # of multi samples
    int multiSampleCount = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &multiSampleCount);
    std::cout << "Max Number of Samples for MSAA: " << multiSampleCount << std::endl;

    int objectType;
    int objectId;

    // print info of the colorbuffer attachable image
    for(int i = 0; i < colorBufferCount; ++i)
    {
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                              GL_COLOR_ATTACHMENT0+i,
                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                              &objectType);
        if(objectType != GL_NONE)
        {
            glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                                  GL_COLOR_ATTACHMENT0+i,
                                                  GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                                  &objectId);

            std::string formatName;

            std::cout << "Color Attachment " << i << ": ";
            if(objectType == GL_TEXTURE)
            {
                std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
            }
            else if(objectType == GL_RENDERBUFFER)
            {
                std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
            }
        }
    }

    // print info of the depthbuffer attachable image
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                          GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                          &objectType);
    if(objectType != GL_NONE)
    {
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                              GL_DEPTH_ATTACHMENT,
                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                              &objectId);

        std::cout << "Depth Attachment: ";
        switch(objectType)
        {
        case GL_TEXTURE:
            std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
            break;
        case GL_RENDERBUFFER:
            std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
            break;
        }
    }

    // print info of the stencilbuffer attachable image
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                          GL_STENCIL_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                          &objectType);
    if(objectType != GL_NONE)
    {
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
                                              GL_STENCIL_ATTACHMENT,
                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                              &objectId);

        std::cout << "Stencil Attachment: ";
        switch(objectType)
        {
        case GL_TEXTURE:
            std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
            break;
        case GL_RENDERBUFFER:
            std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
            break;
        }
    }

    std::cout << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



///////////////////////////////////////////////////////////////////////////////
// return texture parameters as string using glGetTexLevelParameteriv()
///////////////////////////////////////////////////////////////////////////////
std::string getTextureParameters(GLuint id)
{
    if(glIsTexture(id) == GL_FALSE)
        return "Not texture object";

    int width, height, format;
    std::string formatName;
    glBindTexture(GL_TEXTURE_2D, id);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);            // get texture width
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);          // get texture height
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format); // get texture internal format
    glBindTexture(GL_TEXTURE_2D, 0);

    formatName = convertInternalFormatToString(format);

    std::stringstream ss;
    ss << width << "x" << height << ", " << formatName;
    return ss.str();
}



///////////////////////////////////////////////////////////////////////////////
// return renderbuffer parameters as string using glGetRenderbufferParameteriv
///////////////////////////////////////////////////////////////////////////////
std::string getRenderbufferParameters(GLuint id)
{
    if(glIsRenderbuffer(id) == GL_FALSE)
        return "Not Renderbuffer object";

    int width, height, format, samples;
    std::string formatName;
    glBindRenderbuffer(GL_RENDERBUFFER, id);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);       // get renderbuffer width
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);     // get renderbuffer height
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &format); // get renderbuffer internal format
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &samples);   // get multisample count
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    formatName = convertInternalFormatToString(format);

    std::stringstream ss;
    ss << width << "x" << height << ", " << formatName << ", MSAA(" << samples << ")";
    return ss.str();
}



///////////////////////////////////////////////////////////////////////////////
// convert OpenGL internal format enum to string
///////////////////////////////////////////////////////////////////////////////
std::string convertInternalFormatToString(GLenum format)
{
    std::string formatName;

    switch(format)
    {
    case GL_STENCIL_INDEX:      // 0x1901
        formatName = "GL_STENCIL_INDEX";
        break;
    case GL_DEPTH_COMPONENT:    // 0x1902
        formatName = "GL_DEPTH_COMPONENT";
        break;
    case GL_ALPHA:              // 0x1906
        formatName = "GL_ALPHA";
        break;
    case GL_RGB:                // 0x1907
        formatName = "GL_RGB";
        break;
    case GL_RGBA:               // 0x1908
        formatName = "GL_RGBA";
        break;
    case GL_LUMINANCE:          // 0x1909
        formatName = "GL_LUMINANCE";
        break;
    case GL_LUMINANCE_ALPHA:    // 0x190A
        formatName = "GL_LUMINANCE_ALPHA";
        break;
    case GL_R3_G3_B2:           // 0x2A10
        formatName = "GL_R3_G3_B2";
        break;
    case GL_ALPHA4:             // 0x803B
        formatName = "GL_ALPHA4";
        break;
    case GL_ALPHA8:             // 0x803C
        formatName = "GL_ALPHA8";
        break;
    case GL_ALPHA12:            // 0x803D
        formatName = "GL_ALPHA12";
        break;
    case GL_ALPHA16:            // 0x803E
        formatName = "GL_ALPHA16";
        break;
    case GL_LUMINANCE4:         // 0x803F
        formatName = "GL_LUMINANCE4";
        break;
    case GL_LUMINANCE8:         // 0x8040
        formatName = "GL_LUMINANCE8";
        break;
    case GL_LUMINANCE12:        // 0x8041
        formatName = "GL_LUMINANCE12";
        break;
    case GL_LUMINANCE16:        // 0x8042
        formatName = "GL_LUMINANCE16";
        break;
    case GL_LUMINANCE4_ALPHA4:  // 0x8043
        formatName = "GL_LUMINANCE4_ALPHA4";
        break;
    case GL_LUMINANCE6_ALPHA2:  // 0x8044
        formatName = "GL_LUMINANCE6_ALPHA2";
        break;
    case GL_LUMINANCE8_ALPHA8:  // 0x8045
        formatName = "GL_LUMINANCE8_ALPHA8";
        break;
    case GL_LUMINANCE12_ALPHA4: // 0x8046
        formatName = "GL_LUMINANCE12_ALPHA4";
        break;
    case GL_LUMINANCE12_ALPHA12:// 0x8047
        formatName = "GL_LUMINANCE12_ALPHA12";
        break;
    case GL_LUMINANCE16_ALPHA16:// 0x8048
        formatName = "GL_LUMINANCE16_ALPHA16";
        break;
    case GL_INTENSITY:          // 0x8049
        formatName = "GL_INTENSITY";
        break;
    case GL_INTENSITY4:         // 0x804A
        formatName = "GL_INTENSITY4";
        break;
    case GL_INTENSITY8:         // 0x804B
        formatName = "GL_INTENSITY8";
        break;
    case GL_INTENSITY12:        // 0x804C
        formatName = "GL_INTENSITY12";
        break;
    case GL_INTENSITY16:        // 0x804D
        formatName = "GL_INTENSITY16";
        break;
    case GL_RGB4:               // 0x804F
        formatName = "GL_RGB4";
        break;
    case GL_RGB5:               // 0x8050
        formatName = "GL_RGB5";
        break;
    case GL_RGB8:               // 0x8051
        formatName = "GL_RGB8";
        break;
    case GL_RGB10:              // 0x8052
        formatName = "GL_RGB10";
        break;
    case GL_RGB12:              // 0x8053
        formatName = "GL_RGB12";
        break;
    case GL_RGB16:              // 0x8054
        formatName = "GL_RGB16";
        break;
    case GL_RGBA2:              // 0x8055
        formatName = "GL_RGBA2";
        break;
    case GL_RGBA4:              // 0x8056
        formatName = "GL_RGBA4";
        break;
    case GL_RGB5_A1:            // 0x8057
        formatName = "GL_RGB5_A1";
        break;
    case GL_RGBA8:              // 0x8058
        formatName = "GL_RGBA8";
        break;
    case GL_RGB10_A2:           // 0x8059
        formatName = "GL_RGB10_A2";
        break;
    case GL_RGBA12:             // 0x805A
        formatName = "GL_RGBA12";
        break;
    case GL_RGBA16:             // 0x805B
        formatName = "GL_RGBA16";
        break;
    case GL_DEPTH_COMPONENT16:  // 0x81A5
        formatName = "GL_DEPTH_COMPONENT16";
        break;
    case GL_DEPTH_COMPONENT24:  // 0x81A6
        formatName = "GL_DEPTH_COMPONENT24";
        break;
    case GL_DEPTH_COMPONENT32:  // 0x81A7
        formatName = "GL_DEPTH_COMPONENT32";
        break;
    case GL_DEPTH_STENCIL:      // 0x84F9
        formatName = "GL_DEPTH_STENCIL";
        break;
    case GL_RGBA32F:            // 0x8814
        formatName = "GL_RGBA32F";
        break;
    case GL_RGB32F:             // 0x8815
        formatName = "GL_RGB32F";
        break;
    case GL_RGBA16F:            // 0x881A
        formatName = "GL_RGBA16F";
        break;
    case GL_RGB16F:             // 0x881B
        formatName = "GL_RGB16F";
        break;
    case GL_DEPTH24_STENCIL8:   // 0x88F0
        formatName = "GL_DEPTH24_STENCIL8";
        break;
    default:
        std::stringstream ss;
        ss << "Unknown Format(0x" << std::hex << format << ")" << std::ends;
        formatName = ss.str();
    }

    return formatName;
}



///////////////////////////////////////////////////////////////////////////////
// set projection matrix as orthogonal
///////////////////////////////////////////////////////////////////////////////
void toOrtho()
{
    // set viewport to be the entire window
    glViewport((GLsizei)TEXTURE_WIDTH, 0, (GLsizei)TEXTURE_WIDTH, (GLsizei)TEXTURE_HEIGHT);

    // set orthographic viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, TEXTURE_WIDTH, 0, TEXTURE_HEIGHT, -1, 1);

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



///////////////////////////////////////////////////////////////////////////////
// set the projection matrix as perspective
///////////////////////////////////////////////////////////////////////////////
void toPerspective()
{
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)TEXTURE_WIDTH, (GLsizei)TEXTURE_HEIGHT);

    // set perspective viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)(TEXTURE_WIDTH)/TEXTURE_HEIGHT, 0.1f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}







//=============================================================================
// CALLBACKS
//=============================================================================

void displayCB()
{
    static int shift = 0;
    static int index = 0;               // pbo index to alternate every frame
    int nextIndex = 1;                  // pbo index used for next frame

    // brightness shift amount
    ++shift;
    shift %= 200;

    // increment current index first then get the next index
    // "index" is used to read pixels from a framebuffer to a PBO
    // "nextIndex" is used to process pixels in the other PBO
    index = (index + 1) % 2;
    nextIndex = (index + 1) % 2;

    // compute rotation angle
    const float ANGLE_SPEED = 20;   // degree/s
    float angle = ANGLE_SPEED * (float)timer.getElapsedTime();

    // clear whole screen
    glViewport(0, 0, (GLsizei)TEXTURE_WIDTH*2, (GLsizei)TEXTURE_HEIGHT);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // LEFT VIEW //////////////////////////////////////////////////////////////
    // render directly to a FBO, then copy the frame to left view
    glViewport(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)(TEXTURE_WIDTH)/TEXTURE_HEIGHT, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    // camera transform
    glLoadIdentity();
    glTranslatef(0, 0, -CAMERA_DISTANCE);
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading

    // set the rendering destination to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    // clear buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw a rotating teapot at the origin
    glPushMatrix();
    glRotatef(angle*0.5f, 1, 0, 0);
    glRotatef(angle, 0, 1, 0);
    glRotatef(angle*0.7f, 0, 0, 1);
    glTranslatef(0, -1.575f, 0);
    drawTeapot();
    glPopMatrix();

    // back to normal window-system-provided framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind

    // trigger mipmaps generation explicitly
    // NOTE: If GL_GENERATE_MIPMAP is set to GL_TRUE, then glCopyTexSubImage2D()
    // triggers mipmap generation automatically. However, the texture attached
    // onto a FBO should generate mipmaps manually via glGenerateMipmap().
    glBindTexture(GL_TEXTURE_2D, texId);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // copy (blit) fbo to window-system-provided framebuffer
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fboId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT,
                      0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT,
                      GL_COLOR_BUFFER_BIT,
                      GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    ///////////////////////////////////////////////////////////////////////////


    // copy (pack) FBO to PBO /////////////////////////////////////////////////
    if(pboUsed)
    {
        // read frame from FBO to PBO
        // NOTE: glReadPixels() should returns immediately without stall
        t1.start();
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fboId);
        glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[index]);
        glReadPixels(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        readTime = t1.getElapsedTimeInMilliSec();

        // map the PBO that contain framebuffer pixels before processing it
        t1.start();
        glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[nextIndex]);
        GLubyte* src = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
        if(src)
        {
            // change brightness
            add(src, TEXTURE_WIDTH, TEXTURE_HEIGHT, shift, colorBuffer);
            glUnmapBuffer(GL_PIXEL_PACK_BUFFER);        // release pointer to the mapped buffer
        }
        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);      // unbind
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        processTime = t1.getElapsedTimeInMilliSec();
    }
    else
    {
        // read frame from FBO to array directly
        t1.start();
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fboId);
        glReadPixels(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, colorBuffer);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        readTime = t1.getElapsedTimeInMilliSec();

        // change brightness
        t1.start();
        add(colorBuffer, TEXTURE_WIDTH, TEXTURE_HEIGHT, shift, colorBuffer);
        processTime = t1.getElapsedTimeInMilliSec();
    }
    ///////////////////////////////////////////////////////////////////////////


    // RIGHT VIEW /////////////////////////////////////////////////////////////
    // draw the buffer to the right side of the window using glDrawPixels()
    glViewport((GLsizei)TEXTURE_WIDTH, 0, (GLsizei)TEXTURE_WIDTH, (GLsizei)TEXTURE_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, TEXTURE_WIDTH, 0, TEXTURE_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRasterPos2i(0, 0);
    glDrawPixels(TEXTURE_WIDTH, TEXTURE_HEIGHT, PIXEL_FORMAT, GL_UNSIGNED_BYTE, colorBuffer);

    // draw info messages
    showInfo();
    printTransferRate();
    ///////////////////////////////////////////////////////////////////////////

    glutSwapBuffers();
}


void reshapeCB(int width, int height)
{
    toPerspective();
}


void timerCB(int millisec)
{
    glutTimerFunc(millisec, timerCB, millisec);
    glutPostRedisplay();
}


void idleCB()
{
    glutPostRedisplay();
}


void keyboardCB(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27: // ESCAPE
        exit(0);
        break;

    case ' ':
        if(pboSupported)
            pboUsed = !pboUsed;
        std::cout << "PBO mode: " << (pboUsed ? "on" : "off") << std::endl;
         break;

    case 'd': // switch rendering modes (fill -> wire -> point)
    case 'D':
        drawMode = ++drawMode % 3;
        if(drawMode == 0)        // fill mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }
        else if(drawMode == 1)  // wireframe mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        else                    // point mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        break;

    case 's':
    {
        t1.start();
        Image::Bmp bmp;
        bmp.save("screenshot.bmp", TEXTURE_WIDTH, TEXTURE_HEIGHT, 4, colorBuffer);
        t1.stop();
        std::cout << "Saved screenshot.bmp (Elapsed " << t1.getElapsedTimeInMilliSec() << " ms)" << std::endl;
        break;
    }

    default:
        ;
    }
}


void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}


void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance -= (y - mouseY) * 0.2f;
        mouseY = y;
    }
}


void exitCB()
{
    clearSharedMem();
}
