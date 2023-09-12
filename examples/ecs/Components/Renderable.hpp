#pragma once

#include <glm/glm.hpp>

enum RenderableType
{
	Triangle,
	TextureQuad,
	Present,
	GaussianBlur
};
struct Renderable
{
	RenderableType renderableType;
};
