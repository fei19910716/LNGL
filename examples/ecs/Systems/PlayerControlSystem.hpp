#pragma once

#include "base/ecs/System.hpp"


class Event;


class PlayerControlSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:
	std::bitset<8> mButtons;

	void InputListener(Event& event);
};



#include "Components/Player.hpp"
#include "Components/Thrust.hpp"
#include "Components/Transform.hpp"
#include "base/ecs/Coordinator.hpp"


extern Coordinator gCoordinator;


void PlayerControlSystem::Init()
{
	gCoordinator.AddEventListener(METHOD_LISTENER(Events::Window::INPUT, PlayerControlSystem::InputListener));
}

void PlayerControlSystem::Update(float dt)
{
	//for (auto& entity : mEntities)
	//{
	//	auto& transform = gCoordinator.Get<Transform>(entity);


	//	if (mButtons.test(static_cast<std::size_t>(InputButtons::W)))
	//	{
	//		transform.position.z += (dt * 10.0f);
	//	}
}

void PlayerControlSystem::InputListener(Event& event)
{
	mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}
