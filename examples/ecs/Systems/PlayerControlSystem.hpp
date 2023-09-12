#pragma once

#include "base/ecs/System.hpp"
#include "Components/Player.hpp"
#include "Components/Thrust.hpp"
#include "Components/Transform.hpp"
#include "base/ecs/Coordinator.hpp"

class PlayerControlSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:
	std::bitset<8> mButtons;

	void InputListener(Event& event);
};


extern Coordinator gCoordinator;


void PlayerControlSystem::Init()
{
	gCoordinator.AddEventListener(METHOD_LISTENER(Events::Window::INPUT, PlayerControlSystem::InputListener));
}

void PlayerControlSystem::InputListener(Event& event)
{
	mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}

void PlayerControlSystem::Update(float dt)
{
	for (auto& entity : mEntities)
	{
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

		float speed = 1.0f;


		if (mButtons.test(static_cast<std::size_t>(InputButtons::S)))
		{
			transform.position.y -= (dt * speed);
		}

		else if (mButtons.test(static_cast<std::size_t>(InputButtons::W)))
		{
			transform.position.y += (dt * speed);
		}


		if (mButtons.test(static_cast<std::size_t>(InputButtons::A)))
		{
			transform.position.x -= (dt * speed);
		}

		else if (mButtons.test(static_cast<std::size_t>(InputButtons::D)))
		{
			transform.position.x += (dt * speed);
		}

		mButtons.reset();
	}
}


