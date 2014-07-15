#include "light_node.h"
#include "../../renderer/renderer.h"
#include "../entities/canvas.h"

namespace Ness
{
	LightNode::LightNode(Renderer* renderer, NodeAPI* parent) : Node(renderer, parent) 
	{
		// create the canvas.
		// we will render everything on the canvas as additive, and then render the canvas itself with mod blend
		// note: canvas clear color will represent the ambient color, i.e. the color of light when there's no lighting.
		static unsigned int uniqueId = 0;
		m_canvas = create_canvas(std::string("light_node_") + std::to_string((long long)uniqueId));
		remove(m_canvas); // <-- we render it seperatly we don't want it inside the entities list
		uniqueId++;
		set_blend_mode(BLEND_MODE_ADD);
		m_render_target = m_canvas->get_texture();
		m_canvas->set_auto_clean(true);
		m_canvas->set_static(true);
		m_canvas->set_blend_mode(BLEND_MODE_MOD);
		set_ambient_color(Ness::Color::BLACK);
	}

	void LightNode::add(const RenderablePtr& object)
	{
		Node::add(object);
		object->set_blend_mode(BLEND_MODE_ADD);
	}

	LightPtr LightNode::create_light(const std::string& lightTexture, const Color& color)
	{
		LightPtr NewSprite = NESS_MAKE_PTR<Light>(this->m_renderer, this, lightTexture, color);
		add(NewSprite);
		return NewSprite;
	}

	void LightNode::render(const CameraPtr& camera)
	{
		// if invisible skip
		if (!m_visible)
			return;

		// render all lights
		m_renderer->set_render_target(m_canvas->get_texture());
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->render(camera);
		}
		m_renderer->reset_render_target();

		// render self (the canvas)
		m_canvas->render(camera);
	}
};