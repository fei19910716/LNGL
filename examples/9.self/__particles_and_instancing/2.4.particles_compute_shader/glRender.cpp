/*
This code is licensed under the Mozilla Public License Version 2.0 (http://opensource.org/licenses/MPL-2.0)
© 2014 by Sascha Willems - http://www.saschawillems.de

This compute shader implements a very basic attraction based particle system that changes velocities
to move the particles towards the target position
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "glRender.h"
#include "base/utils.h"

using namespace std;

struct vertex4f {
	GLfloat x, y, z, w;
};

GLuint loadBMPTexture(const char * fileName) 
{
	FILE * bmpFile = fopen(fileName, "rb");
	if (!bmpFile)
	{ 
		printf("Could not load bitmap from %s\n", fileName); 
		return 0;
	}

	unsigned char* bmpHeader = new unsigned char[54];
	if (fread(bmpHeader, 1, 54, bmpFile) != 54){
		printf("Headersize does not fit BMP!\n");
		return 0;
	}

	unsigned int width = *(int*)&(bmpHeader[0x12]);
	unsigned int height = *(int*)&(bmpHeader[0x16]);
	unsigned int dataPos = *(int*)&(bmpHeader[0x0A]) != 0 ? *(int*)&(bmpHeader[0x0A]) : 54;
	unsigned int imageSize = *(int*)&(bmpHeader[0x22]) != 0 ? *(int*)&(bmpHeader[0x22]) : width * height * 3;

	unsigned char* bmpData = new unsigned char[imageSize];
	fread(bmpData, 1, imageSize, bmpFile);
	fclose(bmpFile);

	// Generate OpenGL texture (and generate mipmaps
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bmpData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return textureID;
}

float random(float fMin, float fMax)
{
	float fRandNum = (float)rand() / RAND_MAX;
	return fMin + (fMax - fMin) * fRandNum;
}

glRenderer::glRenderer()
{
	srand((unsigned int)time(NULL));
	color[0] = random(64, 255);
	color[1] = random(64, 255);
	color[2] = random(64, 255);
	colorChangeTimer = 1000.0f;
}

void glRenderer::generateShaders()
{
	baseshader = new Shader;
	baseshader->LoadShaderStage("vertex.vs",GL_VERTEX_SHADER);
	baseshader->LoadShaderStage("fragment.fs",GL_FRAGMENT_SHADER);
	baseshader->Link();

	computeshader = new Shader;
	computeshader->LoadShaderStage("compute.cs",GL_COMPUTE_SHADER);
	computeshader->Link();
}

void glRenderer::resetPositionSSBO()
{

	// Reset to mouse cursor pos
	double cursorX, cursorY;
	int windowWidth, windowHeight;
	glfwPollEvents();
	glfwGetCursorPos(window, &cursorX, &cursorY);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	float destPosX = (float)(cursorX / (windowWidth)-0.5f) * 2.0f;
	float destPosY = (float)((windowHeight - cursorY) / windowHeight - 0.5f) * 2.0f;

	struct vertex4f* verticesPos = (struct vertex4f*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particleCount * sizeof(vertex4f), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	for (int i = 0; i < particleCount; i++) {
		float rnd = (float)rand() / (float)(RAND_MAX);
		float rndVal = (float)rand() / (float)(RAND_MAX / (360.0f * 3.14f * 2.0f));
		float rndRad = (float)rand() / (float)(RAND_MAX)* 0.2f; // TODO : Change multiplier to get cool effects (e.g. wider range)
		verticesPos[i].x = destPosX + cos(rndVal) * rndRad;
		verticesPos[i].y = destPosY + sin(rndVal) * rndRad;
		verticesPos[i].z = 0.0f;
		verticesPos[i].w = 1.0f;
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void glRenderer::resetVelocitySSBO()
{
	struct vertex4f* verticesVel = (struct vertex4f*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particleCount * sizeof(vertex4f), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	for (int i = 0; i < particleCount; i++) {
		verticesVel[i].x = 0.0f;
		verticesVel[i].y = 0.0f;
		verticesVel[i].z = 0.0f;
		verticesVel[i].w = 1.0f;
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void glRenderer::resetBuffers()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOPos);
	resetPositionSSBO();
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOVel);
	resetVelocitySSBO();
}

void glRenderer::generateBuffers()
{
	// No more default VAO with OpenGL 3.3+ core profile context,
	// so in order to make our SSBOs render create and bind a VAO
	// that's never used again
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Position SSBO
	if (glIsBuffer(SSBOPos)) {
		glDeleteBuffers(1, &SSBOPos);
	};
	glGenBuffers(1, &SSBOPos);
	// Bind to SSBO
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOPos);
	// Generate empty storage for the SSBO
	glBufferData(GL_SHADER_STORAGE_BUFFER, particleCount * sizeof(vertex4f), NULL, GL_STATIC_DRAW);
	// Fill
	resetPositionSSBO();
	// Bind buffer to target index 0
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBOPos);

	// Velocity SSBO
	if (glIsBuffer(SSBOVel)) {
		glDeleteBuffers(1, &SSBOVel);
	};
	glGenBuffers(1, &SSBOVel);
	// Bind to SSBO
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOVel);
	// Generate empty storage for the SSBO
	glBufferData(GL_SHADER_STORAGE_BUFFER, particleCount * sizeof(vertex4f), NULL, GL_STATIC_DRAW);
	// Fill
	resetVelocitySSBO();
	// Bind buffer to target index 1
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBOVel);

}

void glRenderer::generateTextures()
{
	particleTex = loadBMPTexture(FileSystem::getPath("resources/textures/particle.bmp").c_str());
}

void glRenderer::renderScene()
{

	if (colorFade)
	{

		colorChangeTimer -= frameDelta * 25.0f;

		if ((colorChangeTimer <= 0.0f) & (colorChangeLength <= 0.0f)) {
			if (random(0.0f, 100.0f) < 50.0f)
			{
				colVec[0] = (int)random(0.0f, 8.0f) * 32.0f - color[0];
				colVec[1] = (int)random(0.0f, 8.0f) * 32.0f - color[1];
				colVec[2] = (int)random(0.0f, 8.0f) * 32.0f - color[2];

				float vlength = sqrt(colVec[0] * colVec[0] + colVec[1] * colVec[1] + colVec[2] * colVec[2]);
				colorChangeLength = vlength * 2.0f;

				colVec[0] = colVec[0] / vlength;
				colVec[1] = colVec[2] / vlength;
				colVec[2] = colVec[2] / vlength;

			};
			colorChangeTimer = 1000.0f;
		}

		if (colorChangeLength > 0.0f)
		{
			color[0] += colVec[0] * frameDelta;
			color[1] += colVec[1] * frameDelta;
			color[2] += colVec[2] * frameDelta;

			colorChangeLength -= frameDelta;
		}

	}
	else 
	{
		color[0] = 255.0f;
		color[1] = 64.0f;
		color[2] = 0.0f;
	}


	double frameTimeStart = glfwGetTime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// Run compute shader

	double cursorX, cursorY;
	int windowWidth, windowHeight;
	glfwGetCursorPos(window, &cursorX, &cursorY);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	float destPosX = (float)(cursorX / (windowWidth) - 0.5f) * 2.0f;
	float destPosY = (float)((windowHeight - cursorY) / windowHeight - 0.5f) * 2.0f;

	computeshader->use();
	computeshader->SetUniform("deltaT", frameDelta * speedMultiplier * (pause ? 0.0f : 1.0f));
	computeshader->SetUniform("destPos",glm::vec3(destPosX, destPosY, 0));
	computeshader->SetUniform("vpDim", glm::vec2(1, 1));
	computeshader->SetUniform("borderClamp", (int)borderEnabled);

	int workingGroups = particleCount / 16;

	glDispatchCompute(workingGroups, 1, 1);

	glUseProgram(0);

	// Set memory barrier on per vertex base to make sure we get what was written by the compute shaders
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	// Render scene

	baseshader->use();

	baseshader->SetUniform("inColor",glm::vec4(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, 1.0f));

	glGetError();

	glBindTexture(GL_TEXTURE_2D, particleTex);

	GLuint posAttrib = glGetAttribLocation(baseshader->ID, "pos");

	glBindBuffer(GL_ARRAY_BUFFER, SSBOPos);
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	glPointSize(16);
	glDrawArrays(GL_POINTS, 0, particleCount);

	glfwSwapBuffers(window);

	frameDelta = (float)(glfwGetTime() - frameTimeStart) * 100.0f;

}

void glRenderer::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		resetBuffers();
	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
		speedMultiplier += 0.025f;
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
		speedMultiplier -= 0.025f;
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
		borderEnabled = !borderEnabled;
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		colorFade = !colorFade;
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		pause = !pause;
	if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
	{
		particleCount += 1024;
		printf("particle count : %d\nRegenerating SSBOs...\n", particleCount);
		generateBuffers();
	}
	if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && particleCount > 1024)
	{
		particleCount -= 1024;
		printf("particle count : %d\nRegenerating SSBOs...\n", particleCount);
		generateBuffers();
	}
}