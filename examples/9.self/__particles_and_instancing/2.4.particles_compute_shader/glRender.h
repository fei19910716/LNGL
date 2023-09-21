/*
This code is licensed under the Mozilla Public License Version 2.0 (http://opensource.org/licenses/MPL-2.0)
© 2014 by Sascha Willems - http://www.saschawillems.de

This compute shader implements a very basic attraction based particle system that changes velocities
to move the particles towards the target position
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"

class glRenderer
{
private:
	Shader *baseshader, *computeshader;
	GLuint SSBOPos, SSBOVel;

	GLuint particleTex;
	float frameDelta = 0.0f;
	float speedMultiplier = 0.15f;
	bool borderEnabled = true;
	bool colorFade = false;
	bool pause = false;
	float color[3];
	float colVec[3];
	float colorChangeTimer;
	float colorChangeLength;


	void resetPositionSSBO();
	void resetVelocitySSBO();
public:
	GLFWwindow* window;
	int particleCount = 1024 * 2;

	glRenderer();
	~glRenderer() = default;
	void generateShaders();
	void generateBuffers();
	void resetBuffers();
	void generateTextures();
	void renderScene();
	void keyCallback(int key, int scancode, int action, int mods);
};
