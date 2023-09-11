#pragma once

#include "base/ecs/System.hpp"


class PhysicsSystem : public System
{
public:
	void Init();

	void Update(float dt);
};
