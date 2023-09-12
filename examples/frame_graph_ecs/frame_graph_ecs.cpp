
/*
 * doc:  https://austinmorlan.com/posts/entity_component_system/
 * code: https://code.austinmorlan.com/austin/2019-ecs
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include "Components/Camera.hpp"
#include "Components/Gravity.hpp"
#include "Components/Player.hpp"
#include "Components/Renderable.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Thrust.hpp"
#include "Components/Transform.hpp"
#include "base/ecs/Coordinator.hpp"
#include "Systems/CameraControlSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/PlayerControlSystem.hpp"
#include "Systems/RenderSystem.h"

#include <random>


#include "base/utils.h"



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::bitset<8> mButtons;
Coordinator gCoordinator;

std::shared_ptr<PhysicsSystem> physicsSystem;
std::shared_ptr<CameraControlSystem> cameraControlSystem;
std::shared_ptr<PlayerControlSystem> playerControlSystem;
std::shared_ptr<RenderSystem> renderSystem;

// callbacks
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	bool statusChanged = true;
    if (glfwGetKey(window, GLFW_KEY_W))
	{
		mButtons.set(static_cast<std::size_t>(InputButtons::W));
	}
	else if (glfwGetKey(window, GLFW_KEY_A))
	{
		mButtons.set(static_cast<std::size_t>(InputButtons::A));
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{
		mButtons.set(static_cast<std::size_t>(InputButtons::S));
	}
	else if (glfwGetKey(window, GLFW_KEY_D))
	{
		mButtons.set(static_cast<std::size_t>(InputButtons::D));
	}
	else
	{
		statusChanged = false;
	}

	if(statusChanged){
		Event event(Events::Window::INPUT);
		event.SetParam(Events::Window::Input::INPUT, mButtons);
		gCoordinator.SendEvent(event);
	}

	mButtons.reset();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void init()
{
	gCoordinator.Init();

	gCoordinator.RegisterComponent<Camera>();
	gCoordinator.RegisterComponent<Gravity>();
	gCoordinator.RegisterComponent<Player>();
	gCoordinator.RegisterComponent<Renderable>();
	gCoordinator.RegisterComponent<RigidBody>();
	gCoordinator.RegisterComponent<Thrust>();
	gCoordinator.RegisterComponent<Transform>();


	cameraControlSystem = gCoordinator.RegisterSystem<CameraControlSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Camera>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<CameraControlSystem>(signature);
	}

	cameraControlSystem->Init();


	physicsSystem = gCoordinator.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Gravity>());
		signature.set(gCoordinator.GetComponentType<RigidBody>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<PhysicsSystem>(signature);
	}

	physicsSystem->Init();


	playerControlSystem = gCoordinator.RegisterSystem<PlayerControlSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Player>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<PlayerControlSystem>(signature);
	}

	playerControlSystem->Init();


	renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Renderable>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSystem->Init(SCR_WIDTH,SCR_HEIGHT);

	// TextureQuad
	Entity entity = gCoordinator.CreateEntity();
	gCoordinator.AddComponent<Transform>(
		entity,
		{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		}
	);

	gCoordinator.AddComponent<Renderable>(
		entity,
		{RenderableType::TextureQuad}
	);

	// Triangle
	entity = gCoordinator.CreateEntity();
	gCoordinator.AddComponent<Transform>(
		entity,
		{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		}
	);

	gCoordinator.AddComponent<Player>(
		entity, 
		{}
	);

	// gCoordinator.AddComponent<Gravity>(
	// 	entity,
	// 	{ glm::vec3(0.0f, 2.0f, 0.0f) }
	// );

	// gCoordinator.AddComponent<RigidBody>(
	// 	entity,
	// 	{ 
	// 		glm::vec3(0.0f, 0.0f, 0.0f), 
	// 		glm::vec3(0.0f, 0.0f, 0.0f) 
	// 	}
	// );

	gCoordinator.AddComponent<Renderable>(
		entity,
		{RenderableType::Triangle}
	);

	// Blur
	entity = gCoordinator.CreateEntity();
	gCoordinator.AddComponent<Transform>(
		entity,
		{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		}
	);

	gCoordinator.AddComponent<Renderable>(
		entity,
		{RenderableType::GaussianBlur}
	);

	// Present
	entity = gCoordinator.CreateEntity();
	gCoordinator.AddComponent<Transform>(
		entity,
		{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		}
	);

	gCoordinator.AddComponent<Renderable>(
		entity,
		{RenderableType::Present}
	);
}


void render()
{
	static float dt = 0.0f;
	static Timer timer;
	
	timer.Start();

	playerControlSystem->Update(dt);

	cameraControlSystem->Update(dt);

	physicsSystem->Update(dt);

	renderSystem->Update(dt);


	timer.End();

	dt = timer.Duration();
}

void clean()
{

}

ExamleMain("frame_graph_ecs", SCR_WIDTH, SCR_HEIGHT)