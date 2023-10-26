#pragma once

#include "base/ecs/System.hpp"
#include "Components/Transform.hpp"
#include "base/ecs/Coordinator.hpp"

class Event;


class CameraControlSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:
	std::bitset<8> mButtons;

	void InputListener(Event& event);
};


extern Coordinator gCoordinator;


void CameraControlSystem::Init()
{
	gCoordinator.AddEventListener(METHOD_LISTENER(Events::Window::INPUT, CameraControlSystem::InputListener));
}

void CameraControlSystem::InputListener(Event& event)
{
	mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}

void CameraControlSystem::Update(float dt)
{
	for (auto& entity : mEntities)
	{
		auto& camera = gCoordinator.GetComponent<Camera>(entity);
	}
}