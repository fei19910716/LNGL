
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void init(GLFWwindow *window)
{

}

void clean(){}

/**
 * 一般的实现，迭代次数N, 每次迭代保存其color和depth，并用于下次迭代，最后使用从后向前的正向混合
 * glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
*/
void basicDepthPeeling()
{
    
}


/**
 * 进阶实现，是否进一步迭代使用query查询, 仅创建两个color和depth进行ping-pong，使用从前向后的反向混合
 * glBlendEquation(GL_FUNC_ADD); 
 * glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE,  GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
 * 
 * 
 *  GLuint queryId;
    glBeginQuery(GL_SAMPLES_PASSED, queryId);

    //depth peeling

    glEndQuery(GL_SAMPLES_PASSED);

    GLuint queryReady = GL_FALSE;
    glGetQueryObjectuiv(queryId, GL_QUERY_RESULT_AVAILABLE, &queryReady);
    
    GLuint samples = 0;
    glGetQueryObjectuiv(mOITQueryId, GL_QUERY_RESULT, &samples);

    samples为0时就剥离完成了，不能0则继续剥离。
*/

void advancedDepthPeeling()
{

}


void dualDepthPeeling()
{

}

void render()
{
    basicDepthPeeling();
    // advancedDepthPeeling();
    // dualDepthPeeling();
}

ExamleMain("oit_depth_peeling", SCR_WIDTH, SCR_HEIGHT)