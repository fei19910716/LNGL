#pragma once

#include "base/ecs/System.hpp"
#include "base/utils.h"

#include <memory>


class Event;


class RenderSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:

	std::unique_ptr<Shader> shader;

	GLuint mVao{};
};



#include "Components/Renderable.hpp"
#include "Components/Transform.hpp"
#include "base/ecs/Coordinator.hpp"

#include <cmath>


extern Coordinator gCoordinator;


void RenderSystem::Init()
{
	shader = std::make_unique<Shader>();
	shader->LoadShaderStage("ecs.vs", GL_VERTEX_SHADER);
    shader->LoadShaderStage("ecs.fs", GL_FRAGMENT_SHADER);
    shader->Link();

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	// Vertices
	glGenBuffers(1, &mVboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);
	glEnableVertexAttribArray(0);

	// Surface normal
	glGenBuffers(1, &mVboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}


void RenderSystem::Update(float dt)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT (hicpp-signed-bitwise)

	shader->use();
	glBindVertexArray(mVao);


	for (auto const& entity : mEntities)
	{
		auto const& transform = gCoordinator.GetComponent<Transform>(entity);
		auto const& renderable = gCoordinator.GetComponent<Renderable>(entity);


		glm::mat4 translate;
		translate[0][3] = transform.position.x;
		translate[1][3] = transform.position.y;
		translate[2][3] = transform.position.z;

		glm::mat4 scaleMat;
		scaleMat[0][0] = transform.scale.x;
		scaleMat[1][1] = transform.scale.y;
		scaleMat[2][2] = transform.scale.z;

		glm::mat4 model = translate * scaleMat;

		shader->SetUniform<glm::mat4>("uModel", model);
		shader->SetUniform<glm::vec3>("uColor", renderable.color);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);
}
