#pragma once

#include "base/ecs/System.hpp"
#include "base/utils.h"
#include "Components/Renderable.hpp"
#include "Components/Transform.hpp"
#include "base/ecs/Coordinator.hpp"


#include "base/frame_graph/framegraph.hpp"
#include "base/renderer/texture_quad_renderer.h"
#include "base/renderer/triangle_renderer.h"
#include "base/renderer/gaussian_blur_renderer.h"
#include "base/renderer/present_renderer.h"

#include <memory>
#include <cmath>


class RenderSystem : public System
{
public:
	void Init(unsigned int w, unsigned int h);

	void Update(float dt);

private:

	fg::framegraph framegraph;

	unsigned int width, height;
};


extern Coordinator gCoordinator;


void RenderSystem::Init(unsigned int w, unsigned int h)
{
	this->width  = w;
	this->height = h;
    
}


void RenderSystem::Update(float dt)
{
	
    struct clear_pass_data
    {
      fbo_resource* output;
    };
    auto clear_pass_task = framegraph.add_render_task<clear_pass_data>(
    "Clear Pass",
    [&] (clear_pass_data& data, fg::render_task_builder& builder)
    {
      FrameBuffer::Description desc;
      {
        desc.width = width;
        desc.height = height;
        desc.color_format = GL_RGBA;
        desc.depth_format = GL_DEPTH24_STENCIL8;
      }

      data.output = builder.create<fbo_resource>("FBO",desc);
    },
    [=] (const clear_pass_data& data)
    {
      data.output->actual()->Bind();

      glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

    });
    auto pass_out_data = clear_pass_task->data().output;
    
    
	for (auto const& entity : mEntities)
	{
		auto const& transform  = gCoordinator.GetComponent<Transform>(entity);
		auto const& renderable = gCoordinator.GetComponent<Renderable>(entity);


		switch (renderable.renderableType)
		{
		case RenderableType::TextureQuad:
			{
			auto texture_renderer = new TextureQuadRenderer("texture.vs","texture.fs","resources/textures/awesomeface.png");
			struct texture_pass_data
			{
				fbo_resource* output;
			};
			auto texture_pass_task = framegraph.add_render_task<texture_pass_data>(
			"Texture Pass",
			[&] (texture_pass_data& data, fg::render_task_builder& builder)
			{
				data.output = builder.write<fbo_resource>(pass_out_data);
			},
			[=] (const texture_pass_data& data)
			{
				data.output->actual()->Bind();

				texture_renderer->render();

			});

			pass_out_data = texture_pass_task->data().output;
			}
			break;
		case RenderableType::Triangle:
			{
			auto triagnle_renderer = new TriangleRenderer("triangle.vs","triangle.fs");
			struct triangle_pass_data
			{
			fbo_resource* output;
			};
			auto triangle_pass_task = framegraph.add_render_task<triangle_pass_data>(
			"Triangle Pass",
			[&] (triangle_pass_data& data, fg::render_task_builder& builder)
			{
			data.output = builder.write<fbo_resource>(pass_out_data);
			},
			[=] (const triangle_pass_data& data)
			{
			data.output->actual()->Bind();
			triagnle_renderer->setMat4("model",glm::mat4(1.0f));
			triagnle_renderer->render();

			});

			pass_out_data = triangle_pass_task->data().output;
			}
			break;

		
		case RenderableType::GaussianBlur:
			{
			auto blur_renderer = new GuassianBlurRenderer("gaussian_blur.vs","gaussian_blur.fs");
			struct blur_pass_data
			{
			fbo_resource* input;
			fbo_resource* output;
			};
			auto blur_pass_task = framegraph.add_render_task<blur_pass_data>(
			"Blur Pass",
			[&] (blur_pass_data& data, fg::render_task_builder& builder)
			{
			data.input = builder.read<fbo_resource>(pass_out_data);
			data.output = builder.write<fbo_resource>(pass_out_data);
			},
			[=] (const blur_pass_data& data)
			{
			
			data.output->actual()->Bind();
			data.input->actual()->BindColor(GL_TEXTURE0);
			blur_renderer->render();

			});

			pass_out_data = blur_pass_task->data().output;
			}
			break;

		case RenderableType::Present:
			{
			auto back_buffer = framegraph.add_retained_resource("Backbuffer", 
                                                        FrameBuffer::Description(), 
                                                        new FrameBuffer);

			auto present_renderer = new PresentRenderer("present.vs","present.fs");
			struct present_pass_data
			{
			fbo_resource* input;
			fbo_resource* output;
			};
			auto present_pass_task = framegraph.add_render_task<present_pass_data>(
			"Present Pass",
			[&] (present_pass_data& data, fg::render_task_builder& builder)
			{
			data.input = builder.read<fbo_resource>(pass_out_data);
			data.output = builder.write<fbo_resource>(back_buffer);
			},
			[=] (const present_pass_data& data)
			{
			
			data.output->actual()->Bind();
			
			data.input->actual()->BindColor(GL_TEXTURE0);
			present_renderer->render();

			});
			}
			break;

		}
	}

	framegraph.compile();
	framegraph.execute();
	framegraph.clear();
}
