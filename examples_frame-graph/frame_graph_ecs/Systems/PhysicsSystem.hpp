#pragma once

#include "base/ecs/System.hpp"
#include "Components/Gravity.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Thrust.hpp"
#include "Components/Transform.hpp"
#include "base/ecs/Coordinator.hpp"

class PhysicsSystem : public System
{
public:
	void Init();

	void Update(float dt);
};

extern Coordinator gCoordinator;


void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

		// Forces
		auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

		transform.position -= rigidBody.velocity * dt;

		rigidBody.velocity += gravity.force * dt;
	}
}
