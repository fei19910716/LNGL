#pragma once

#include "base/utils.h"

#define NUM_PARTICLE_ATTRIBUTES 6
#define MAX_PARTICLES_ON_SCENE 100000

#define PARTICLE_TYPE_GENERATOR 0
#define PARTICLE_TYPE_NORMAL 1


class Texture2D;

/*****************************************************

Class:		CParticle

Purpose:	Encapsulates particle and its properties.

*****************************************************/

class CParticle
{
public:
	glm::vec3 vPosition;
	glm::vec3 vVelocity;
	glm::vec3 vColor;
	float fLifeTime;
	float fSize;
	int iType;

	void toString()
    {
        std::cout << "vPosition: (" << vPosition.x << "," << vPosition.y << ")" << ", "
                  << "vVelocity: (" << vVelocity.x << "," << vVelocity.y << ")" << ", "
                  << "vColor: (" << vColor.x << "," << vColor.y << "," << vColor.z << ")" << ", "
				  << "iType: " << iType << ", "
				  << "fSize: " << fSize << ", "
                  << "fLifeTime: " << fLifeTime << std::endl;
    }
};

/**********************************************************************

Class:		CParticleSystemTransformFeedback

Purpose:	Particle system class that uses transform feedback feature.

***********************************************************************/

class CParticleSystemTransformFeedback
{
public:
    using UINT = unsigned int;
	bool InitalizeParticleSystem();

	void RenderParticles();
	void UpdateParticles(float fTimePassed);

	void SetGeneratorProperties(glm::vec3 a_vGenPosition, 
								glm::vec3 a_vGenVelocityMin, 
								glm::vec3 a_vGenVelocityMax, 
								glm::vec3 a_vGenGravityVector, 
								glm::vec3 a_vGenColor, 
								float a_fGenLifeMin, 
								float a_fGenLifeMax, 
								float a_fGenSize, 
								float fEvery, 
								int a_iNumToGenerate);

	void ClearAllParticles();
	bool ReleaseParticleSystem();

	int GetNumParticles();

	void SetMatrices(glm::mat4* a_matProjection, glm::vec3 vEye, glm::vec3 vView, glm::vec3 vUpVector);

	CParticleSystemTransformFeedback();

private:
	bool bInitialized;
	
	UINT uiTransformFeedbackBuffer;

	UINT uiParticleBuffer[2];
	UINT uiVAO[2];

	UINT uiQuery;
	UINT uiTexture;

	int iCurReadBuffer;
	int iNumParticles = 1;

	glm::mat4 matProjection, matView;
	glm::vec3 vQuad1, vQuad2;
	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);

	float fElapsedTime;
	float fNextGenerationTime;

	glm::vec3 vGenPosition;
	glm::vec3 vGenVelocityMin, vGenVelocityRange;
	glm::vec3 vGenGravityVector;
	glm::vec3 vGenColor;

	float fGenLifeMin, fGenLifeRange;
	float fGenSize;

	int iNumToGenerate;

	Texture2D* renderTexture;

	Shader* spRenderParticles;
	Shader* spUpdateParticles;
};