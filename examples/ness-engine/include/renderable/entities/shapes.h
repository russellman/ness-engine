/**
* renderable basic shapes
* Author: Ronen Ness
* Since: 07/1014
*/

#pragma once
#include "entity.h"

namespace Ness
{

	// the renderable sprite class
	class RectangleShape: public Entity
	{
	private:
		bool m_is_filled;

	public:
		// create the rectangle shape
		NESSENGINE_API RectangleShape(Renderer* renderer, NodeAPI* parent);

		// set if this rectangle is filled or just outlines
		inline void set_filled(bool filled) {m_is_filled = filled;}

	protected:
		// the actual rendering function
		NESSENGINE_API virtual void do_render(const Rectangle& target, const SRenderTransformations& transformations);
	};

	// rectangle shape pointer
	NESSENGINE_API typedef std::shared_ptr<RectangleShape> RectangleShapePtr;
};